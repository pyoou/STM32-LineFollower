cmake_minimum_required(VERSION 3.22)

if(NOT CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/gcc-arm-none-eabi.cmake)
endif()

project(LineFollower LANGUAGES C ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(MCU_FLAGS "-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${MCU_FLAGS} -Wall -Wextra -Wpedantic -fdata-sections -ffunction-sections")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${MCU_FLAGS} -x assembler-with-cpp")

set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/bsp/STM32F411XX_FLASH.ld)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${MCU_FLAGS} -T${LINKER_SCRIPT} -Wl,--gc-sections -Wl,-Map=${PROJECT_NAME}.map --specs=nano.specs --specs=nosys.specs")

add_compile_definitions(
        USE_HAL_DRIVER
        STM32F411xE
)

file(GLOB_RECURSE APP_SOURCES "app/src/*.c")
file(GLOB_RECURSE BSP_SOURCES "bsp/src/*.c")

set(STARTUP_SCRIPT "bsp/startup_stm32f411xe.s")

set_source_files_properties(${STARTUP_SCRIPT} PROPERTIES LANGUAGE ASM)

file(GLOB HAL_SOURCES "drivers/STM32F4xx_HAL_Driver/Src/*.c")
list(FILTER HAL_SOURCES EXCLUDE REGEX ".*_template\\.c$")

add_executable(${PROJECT_NAME}
        ${APP_SOURCES}
        ${BSP_SOURCES}
        ${HAL_SOURCES}
        ${STARTUP_SCRIPT}
)

target_include_directories(${PROJECT_NAME} PRIVATE
        app/inc
        bsp/inc
        drivers/STM32F4xx_HAL_Driver/Inc
        drivers/CMSIS_Device/Include
        drivers/CMSIS_Core/CMSIS/Core/Include
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}> ${PROJECT_NAME}.hex
        COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}> ${PROJECT_NAME}.bin
        COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${PROJECT_NAME}>
)