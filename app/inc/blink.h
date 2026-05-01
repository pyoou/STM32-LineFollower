/**
 * @file blink.h
 * @author pyoou (https://github.com/pyoou)
 * @brief Led blinking module for functionality test
 * @version 0.1
 * @date 2026-03-13
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef LINEFOLLOWER_BLINK_H
#define LINEFOLLOWER_BLINK_H

#include "gpio.h"
#include "stm32f4xx_hal.h"


/**
 * @brief Initialize led blinking periferials for PC13
 */
void Blink_Init(void);

void Key_Init(void);

/**
 * @brief Led blinking process
 * @param blink_interval: Value of interval blink [ms]
 */
void Blink_Process(uint32_t blink_interval);

#endif // LINEFOLLOWER_BLINK_H