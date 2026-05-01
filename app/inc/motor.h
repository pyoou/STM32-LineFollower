/**
 * @file motor.h
 * @author pyoou (https://github.com/pyoou)
 * @brief settings and initialization for motor
 * @version 0.1
 * @date 2026-03-29
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef LINEFOLLOWER_MOTOR_H
#define LINEFOLLOWER_MOTOR_H

#include "pwm.h"

typedef struct
{
  /* PWM */
  TIM_HandleTypeDef *htim; // TIM rail pointer
  uint32_t channel_fwd;    // Channel Forward
  uint32_t channel_rev;    // Channel Reverse
  int16_t max_speed;       // Max speed (antiwindup)
} Motor_t;

/**
 * @brief Initialize motor periferials
 *
 * @param motor // TODO: Fillup
 * @param htim
 * @param channel_fwd
 * @param channel_rev
 * @param max_speed
 */
void Motor_Init(Motor_t *motor, TIM_HandleTypeDef *htim, uint32_t channel_fwd,
                uint32_t channel_rev, uint16_t max_speed);

/**
 * @brief Set motor speed
 *
 * @param motor -> pointer for motor @ref Motor_t
 * @param speed -> new speed value
 */
void Motor_SetSpeed(Motor_t *motor, int16_t speed);

/**
 * @brief Current motor stop
 *
 * @param motor -> motor pointer @ref Motor_t
 */
void Motor_Stop(Motor_t *motor);

#endif // LINEFOLLOWER_MOTOR_H
