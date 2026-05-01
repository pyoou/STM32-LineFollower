//
// Created by pyoou on 23.03.2026.
//

#include "motor.h"
#include <stdlib.h>

void Motor_Init(Motor_t *motor, TIM_HandleTypeDef *htim, uint32_t channel_fwd,
                uint32_t channel_rev, uint16_t max_speed)
{
  motor->htim = htim;
  motor->channel_fwd = channel_fwd;
  motor->channel_rev = channel_rev;
  motor->max_speed = max_speed;

  BSP_PWM_Init();

  Motor_Stop(motor);
}

void Motor_SetSpeed(Motor_t *motor, int16_t speed)
{
  if (speed > motor->max_speed)
    speed = motor->max_speed;

  uint32_t pwm_val = (uint32_t)abs(speed);

  if (speed > 0)
  { // Jedziemy do przodu: PWM na kanale Forward, 0 na kanale Reverse
    __HAL_TIM_SET_COMPARE(motor->htim, motor->channel_fwd, pwm_val);
    __HAL_TIM_SET_COMPARE(motor->htim, motor->channel_rev, 0);
  }
  else
  {
    // Zatrzymanie
    __HAL_TIM_SET_COMPARE(motor->htim, motor->channel_fwd, 0);
    __HAL_TIM_SET_COMPARE(motor->htim, motor->channel_rev, 0);
  }
}

void Motor_Stop(Motor_t *motor) { Motor_SetSpeed(motor, 0); }
