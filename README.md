LineFollower/
├── app/                     # WARSTWA APLIKACJI (Czysty kod)
│   ├── inc/                 # Pliki nagłówkowe (.h) np. motor.h, pid.h, sensor.h
│   └── src/                 # Pliki źródłowe (.c) np. main.c, motor.c, pid.c
│
├── bsp/                     # BOARD SUPPORT PACKAGE (Warstwa sprzętowa)
│   ├── inc/                 # np. board.h (tu definiujesz np. #define MOTOR_LEFT_PIN GPIO_PIN_4)
│   ├── src/                 # np. board.c (tu ląduje konfiguracja zegarów i pinów)
│   ├── startup_stm32f411xe.s # Twój plik startowy Assemblera (ten z Flash)
│   └── stm32f411retx.ld     # Twój plik linkera (ten z rozszerzeniem .ld)
│
├── drivers/                 # ZEWNĘTRZNE BIBLIOTEKI (Tego nie tykasz)
│   ├── CMSIS/               # Pliki nagłówkowe rdzenia ARM (core_cm4.h itd.)
│   └── STM32F4xx_HAL_Driver/# Pełna paczka HAL od ST (foldery Inc i Src)
│
├── cmake/                   # PLIKI KONFIGURACYJNE
│   └── gcc-arm-none-eabi.cmake # Twój plik toolchaina z poprzedniego projektu
│
├── scripts/                 # AUTOMATYZACJA
│   └── flash.bat            # Twój skrypt do OpenOCD
│
├── .gitignore               # Ignorowanie śmieci w Gicie (Niezbędne w CV!)
├── CMakeLists.txt           # Serce projektu - instrukcje kompilacji
└── README.md                # Wizytówka projektu na GitHuba