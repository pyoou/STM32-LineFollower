//
// Created by pyoou on 15.03.2026.
//

#include "gpio.h"

void BSP_GPIO_Init(GPIO_TypeDef *port, uint16_t pin, uint32_t mode,
                   uint32_t pull, uint32_t speed)
{
  BSP_RCC_CLK_ENABLE(port);
  HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  GPIO_InitStruct.Pin = pin;
  GPIO_InitStruct.Mode = mode;
  GPIO_InitStruct.Pull = pull;
  GPIO_InitStruct.Speed = speed;
  HAL_GPIO_Init(port, &GPIO_InitStruct);
}

bool IsButtonPressed(void)
{
  static uint32_t last_press_time = 0;
  static bool is_handed = false;
  uint32_t current_time = HAL_GetTick();

  if (HAL_GPIO_ReadPin(BUTTON_GPIO, BUTTON_PIN) == GPIO_PIN_RESET)
  {
    if (!is_handed && (current_time - last_press_time > 50))
    {
      is_handed = true;
      last_press_time = current_time;
      return true;
    }
  }
  else
  {
    is_handed = false;
    last_press_time = current_time;
  }

  return false;
}

void BSP_RCC_CLK_ENABLE(GPIO_TypeDef *port)
{
  if (port == GPIOA)
  {
    __HAL_RCC_GPIOA_CLK_ENABLE();
  }
  else if (port == GPIOB)
  {
    __HAL_RCC_GPIOB_CLK_ENABLE();
  }
  else if (port == GPIOC)
  {
    __HAL_RCC_GPIOC_CLK_ENABLE();
  }
  else if (port == GPIOH)
  {
    __HAL_RCC_GPIOH_CLK_ENABLE();
  }
}