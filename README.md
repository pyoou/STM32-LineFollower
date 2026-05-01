# 🏎️ STM32 Micro Robot Base (Line Follower / Minisumo)

Projekt solidnej i bezpiecznej bazy jezdnej dla małego robota, opartej na mikrokontrolerze **STM32 Black Pill (F411/F401)**. Kod został napisany w języku C z wykorzystaniem biblioteki **HAL** i środowiska **VS Code**. 

Architektura opiera się na nieblokującej Maszynie Stanów (FSM), co zapewnia płynne działanie robota i natychmiastową reakcję na czujniki.

## 🛠️ Architektura Sprzętowa (Hardware)

*   **Mikrokontroler:** STM32 Black Pill (zasilany stabilnym 3.3V przez wbudowany LDO z pinu 5V).
*   **Napęd:** 2x Mikrosilniki N20 z przekładnią (docelowo 9V).
*   **Zasilanie:** Pojedyncze ogniwo Li-Ion / Li-Po (3.7V).
*   **Zarządzanie energią:** 
    *   Przetwornica Step-Up (np. Pololu 9V) do zasilania silników.
    *   Kondensatory filtrujące (odsprzęgające) na linii zasilania logiki i silników zapobiegające resetom procesora.
*   **Sterownik silników:** Mostek H sterowany w pełni sprzętowym PWM.
*   **Czujniki (Planowane):** Transoptory odbiciowe SMD KTIR0711S do śledzenia linii.

## 🔌 Pinout i Połączenia

Aby uniknąć konfliktów sprzętowych (np. z domyślnie aktywnym interfejsem JTAG na pinie PB4), cały napęd robota został zintegrowany na jednym, dedykowanym **Timerze 4 (TIM4)**.

| Element robota | Funkcja | Pin STM32 | Peryferium sprzętowe |
| :--- | :--- | :--- | :--- |
| **Silnik Prawy** | Do przodu (IN1) | `PB6` | TIM4_CH1 |
| **Silnik Prawy** | Do tyłu (IN2) | `PB7` | TIM4_CH2 |
| **Silnik Lewy** | Do przodu (IN3) | `PB8` | TIM4_CH3 |
| **Silnik Lewy** | Do tyłu (IN4) | `PB9` | TIM4_CH4 |
| **Przycisk (User)** | Zmiana stanu | `PA0` | GPIO Input (z debouncingiem) |
| **Dioda (User)** | Status robota | `PC13`| GPIO Output |
| **Czujniki linii** | Odczyt ADC |`PA0`, `PA5`, `PA6` `PA7`, `PA8`, `PA9`| ADC1 (Rezerwacja) |

> ⚠️ **Ważna uwaga projektowa:** Masy (GND) baterii, przetwornicy Step-Up, sterownika silników oraz samej płytki Black Pill **muszą być ze sobą połączone** w jednym wspólnym punkcie referencyjnym (Topologia Gwiazdy).

## 💻 Architektura Oprogramowania (Software)

Projekt stawia na czystość kodu i dobre praktyki inżynierskie w systemach wbudowanych:

1.  **Finite State Machine (FSM):** Logika robota jest podzielona na dyskretne stany (`IDLE`, `CALIBRATION`, `RUNNING`, `LOST`, `STOP`). Przejścia między stanami są w 100% nieblokujące.
2.  **Bezpieczny PWM (Brake Prevention):** Moduł `pwm.c` posiada wbudowane zabezpieczenia logiczne. Funkcja sterująca gwarantuje, że przy ruchu w danym kierunku, przeciwne wejście mostka H dostaje twarde wypełnienie `0%`. Całkowicie eliminuje to ryzyko zwarcia sprzętowego (tzw. "twardego hamulca" podającego napięcie na obie fazy silnika).
3.  **Software Debouncing:** Przycisk użytkownika (PA0) jest odczytywany asynchronicznie za pomocą funkcji bazującej na `HAL_GetTick()`. Brak użycia `HAL_Delay()`, dzięki czemu pętla główna wykonuje się z maksymalną częstotliwością.

## 🚀 Jak rozpocząć pracę z kodem

1.  Sklonuj to repozytorium: `git clone <link_do_repo>`
2.  Otwórz folder w programie **Visual Studio Code**.
3.  Upewnij się, że masz zainstalowane narzędzia do budowania projektów STM32 (np. rozszerzenie *PlatformIO* lub *STM32 VS Code Extension*).
4.  W pliku konfiguracyjnym wymuś wgrywanie kodu przez interfejs SWD, np. (dla PlatformIO):
    ```ini
    upload_protocol = stlink
    debug_tool = stlink
    ```
5.  Zbuduj projekt i wgraj na płytkę. Po resecie robot domyślnie wejdzie w tryb `STATE_IDLE` (sygnalizowane miganiem wbudowanej diody). Aby wprawić go w ruch, wciśnij przycisk "KEY" (PA0).

---
*Stworzone z pasją do robotyki i mikrokontrolerów.* 🤖