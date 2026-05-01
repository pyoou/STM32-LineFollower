@echo off
echo =======================================
echo DOCKER COMPILE (CMAKE)
echo =======================================
docker run --rm -v "%cd%:/workspace" stm32-builder sh -c "cmake -B build -DCMAKE_TOOLCHAIN_FILE=cmake/gcc-arm-none-eabi.cmake -G 'Unix Makefiles' && cmake --build build"

:: if compile -> break
if %errorlevel% neq 0 (
    echo.
    echo [BŁĄD] Kompilacja zakonczona niepowodzeniem. Przerywam wgrywanie!
    exit /b %errorlevel%
)

echo.
echo =======================================
echo FLASHING (OPENOCD)
echo =======================================
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program build/LineFollower.elf verify reset exit"

echo.
echo =======================================
echo FINISH!
echo =======================================