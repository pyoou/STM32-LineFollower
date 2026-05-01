//
// Created by pyoou on 23.03.2026.
//

#include "pwm.h"

TIM_HandleTypeDef htim3 = {0};
TIM_HandleTypeDef htim4 = {0};

void BSP_PWM_Init(void)
{
  /* Clocks Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_TIM3_CLK_ENABLE();
  __HAL_RCC_TIM4_CLK_ENABLE();

  /* PINs config */
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;            // Alternate function
  GPIO_InitStruct.Pull = GPIO_NOPULL;                // No pull
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH; // Very high frequency

  // GPIO_InitStruct.Pin = GPIO_PIN_4 | GPIO_PIN_5;
  // GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
  // HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;
  GPIO_InitStruct.Alternate = GPIO_AF2_TIM4;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* TIM3 config */
  // htim3.Instance = TIM3;
  // htim3.Init.Prescaler = PWM_PRESCALLER;
  // htim3.Init.Period = PWM_AUTORELOAD;
  // htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  // htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  // HAL_TIM_PWM_Init(&htim3);

  /* TIM4 config */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = PWM_PRESCALLER;
  htim4.Init.Period = PWM_AUTORELOAD;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_PWM_Init(&htim4);

  /* PWM channel config */
  TIM_OC_InitTypeDef sConfigOC = {0};
  sConfigOC.OCMode = TIM_OCMODE_PWM1;         // PWM Mode 1
  sConfigOC.Pulse = 0;                        // Initial value = 0
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH; // Active state = HIGH
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

  // HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1);
  // HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2);

  HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1);
  HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_2);
  HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3);
  HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_4);

  /* PWM Counters (CR1_CEN) */
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);

  // HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
  // HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
}