//
// Created by pyoou on 15.03.2026.
//

#include "gpio.h"
#include "stm32f4xx_hal.h"

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