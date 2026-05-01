/**
 * @file gpio.h
 * @author pyoou (https://github.com/pyoou)
 * @brief Board initialization GPIO
 * @version 0.1
 * @date 2026-03-13
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef LINEFOLLOWER_GPIO_H
#define LINEFOLLOWER_GPIO_H

// Include STM32 HAL
#include "stm32f4xx_hal.h"

/**
 * @brief Simplified initialization for GPIOs, included with RCC
 *
 * @param port Speficies the group of GPIOx as a pointer.
 *          This parameter can be a value of @ref GPIOx
 * @param pin Specifies the GPIO pins to be configured.
 *          This parameter can be a value of @ref GPIO_mode_define
 * @param mode Specifies the operating mode for the selected pins.
 *          @ref GPIO_mode_define
 * @param pull Specifies the Pull-up or Pull-Down activation for the selected
 *          pins. This parameter can be a value of @ref GPIO_pull_define
 * @param speed Specifies the speed for the selected pins.
 *          This parameter can be a value of @ref GPIO_speed_define
 */
void BSP_GPIO_Init(GPIO_TypeDef *port, uint16_t pin, uint32_t mode,
                   uint32_t pull, uint32_t speed);

/**
 * @brief Automated RCC Clock initialization for GPIOs
 *
 * @param port Speficies the group of GPIOx as a pointer.
 *          This parameter can be a value of @ref GPIOx
 */
void BSP_RCC_CLK_ENABLE(GPIO_TypeDef *port);

#endif // LINEFOLLOWER_GPIO_H