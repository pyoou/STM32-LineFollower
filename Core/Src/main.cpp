#include "FreeRTOS.h"
#include "led_controller.h"
#include "stm32f411xe.h"
#include "task.h"

LedController systemLed(13);

extern "C" {

// start FPU procesor
void SystemInit(void) { SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2)); }
void HardFault_Handler(void) {
  while (1)
    ;
}
void Error_Handler(void) {
  while (1)
    ;
}
}

void vBlinkTask(void *pvParameters) {
  while (1) {
    systemLed.toggle();
    vTaskDelay(pdMS_TO_TICKS(50)); // time [ms]
  }
}

int main(void) {
  // RTOS blink task
  xTaskCreate(vBlinkTask, "BlinkTask", configMINIMAL_STACK_SIZE, NULL,
              tskIDLE_PRIORITY + 1, NULL);

  vTaskStartScheduler();

  while (1) {
  }
  return 0;
}