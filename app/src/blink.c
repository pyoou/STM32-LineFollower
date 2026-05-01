//
// Created by pyoou on 15.03.2026.
//

#include "blink.h"
#include "gpio.h"
#include "stm32f4xx_hal.h"

#define LED_PORT GPIOC
#define LED_PIN GPIO_PIN_13
#define LED_MODE GPIO_MODE_OUTPUT_PP
#define LED_PULL GPIO_NOPULL
#define LED_SPEED GPIO_SPEED_FREQ_LOW

static uint32_t prev_time = 0;

void Blink_Init(void)
{
  // Initialize BSP module for GPIO led
  BSP_GPIO_Init(LED_PORT, LED_PIN, LED_MODE, LED_PULL, LED_SPEED);
}

void Key_Init(void)
{
  BSP_GPIO_Init(GPIOA, GPIO_PIN_0, GPIO_MODE_INPUT, GPIO_PULLUP,
                GPIO_SPEED_LOW);
}

void Blink_Process(uint32_t blink_interval)
{
  // TogglePin when time's passed
  if (HAL_GetTick() - prev_time >= (uint32_t)blink_interval)
  {
    prev_time = HAL_GetTick();
    HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
  }
}
