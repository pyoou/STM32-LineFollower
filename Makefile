# Nazwa projektu
TARGET = STM32F411_Project

# Kompilatory i narzędzia
CC = arm-none-eabi-gcc
CXX = arm-none-eabi-g++
AS = arm-none-eabi-gcc -x assembler-with-cpp
CP = arm-none-eabi-objcopy
SZ = arm-none-eabi-size

# Flagi mikrokontrolera (Cortex-M4 z FPU)
MCU = -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard

# Makra
C_DEFS = -DUSE_HAL_DRIVER -DSTM32F411xE -D__FPU_USED=1

# Foldery z nagłówkami
C_INCLUDES = \
-ICore/Inc \
-IDrivers/STM32F4xx_HAL_Driver/Inc \
-IDrivers/STM32F4xx_HAL_Driver/Inc/Legacy \
-IDrivers/CMSIS_Device/Include \
-IDrivers/CMSIS_Core/CMSIS/Core/Include \
-IMiddlewares/FreeRTOS/include \
-IMiddlewares/FreeRTOS/portable/GCC/ARM_CM4F

# Pliki źródłowe C (HAL i FreeRTOS)
# Core/Src/system_stm32f4xx.c 
C_SOURCES = \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c \
Middlewares/FreeRTOS/tasks.c \
Middlewares/FreeRTOS/queue.c \
Middlewares/FreeRTOS/list.c \
Middlewares/FreeRTOS/timers.c \
Middlewares/FreeRTOS/portable/GCC/ARM_CM4F/port.c \
Middlewares/FreeRTOS/portable/MemMang/heap_4.c

# Pliki źródłowe C++
CPP_SOURCES = \
Core/Src/main.cpp \
Core/Src/led_controller.cpp

# Plik startowy ASM
ASM_SOURCES = \
startup_stm32f411xe.s

# Flagi kompilatora C
CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) -O2 -Wall -fdata-sections -ffunction-sections

# Flagi kompilatora C++ (dziedziczą z C, dodatkowo wyłączają wyjątki dla oszczędności pamięci)
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti -std=c++14

# Flagi linkera
LDFLAGS = $(MCU) -specs=nano.specs -Tstm32f411xe_flash.ld -Wl,-Map=$(TARGET).map,--cref -Wl,--gc-sections

# --- Reguły budowania ---
BUILD_DIR = build
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CPP_SOURCES)))

OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin $(BUILD_DIR)/$(TARGET).hex

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.cpp Makefile | $(BUILD_DIR)
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(CP) -O ihex $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(CP) -O binary $< $@

$(BUILD_DIR):
	mkdir $@

clean:
	rmdir /S /Q $(BUILD_DIR)