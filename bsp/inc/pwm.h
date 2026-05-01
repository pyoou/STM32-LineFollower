/**
 * @file pwm.h
 * @author pyoou (https://github.com/pyoou)
 * @brief pwm signals for motors
 * @version 0.1
 * @date 2026-03-15
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef LINEFOLLOWER_PWM_H
#define LINEFOLLOWER_PWM_H

#include "stm32f4xx.h"

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

/**
 * @brief setted up PWM parameters. @ref TIM_Base_InitTypeDef
 *
 */
#define PWM_PRESCALLER 0    // start counting from PWM_PRESCALLER
#define PWM_AUTORELOAD 4999 // reload counter after value of PWM_AUTORELOAD
#define PWM_MAX_SPEED 4999  // max speed for PWM

/**
 * @brief Initialize PWM signal for ADC1_x
 *
 */
void BSP_PWM_Init(void);

#endif // LINEFOLLOWER_PWM_H