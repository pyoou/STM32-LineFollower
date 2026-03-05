# Project:     Line Follower 
## Board:      STM32F411 Black Pill 
<b>Project is adjusted to ROBOCOMP competition rules. I've decided to use black pill board, because of the size, performence and features included to this small beast.</b>
## OS:         FreeRTOS
## Code:       C, CPP & Registers
## Additional: datasheet, user manual & IoT.



## Commands:
```cmd
make

openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program build/STM32F411_Project.elf verify reset exit"

```