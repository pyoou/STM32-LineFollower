/**
 * @file adc.h
 * @author pyoou (https://github.com/pyoou)
 * @brief Board Support Package ADC logic prepared for light sensors.
 * @version 0.1
 * @date 2026-03-13
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef LINEFOLLOWER_ADC_H
#define LINEFOLLOWER_ADC_H

#include "stm32f4xx_hal.h"

// Count of light sensors included to project
#define SENSOR_COUNT 6

/**
 * @brief Initialize ADC, Timers, and GPIO.
 */
void BSP_ADC_Init(void);

/**
 * @brief Get value from current sensor.
 *
 * @param sensor_index: index of current sensor [example: ADC1_1 = 1]
 * @return uint16_t -> sensor_value [0-4095]
 */
uint16_t BSP_ADC_GetValue(uint8_t sensor_index);

/**
 * @brief Get all values from included sensors based on SENSOR_COUNT
 *
 * @return uint16_t* -> struct of sensors
 */
uint16_t *BSP_ADC_GetAllValues(void);

#endif // LINEFOLLOWER_ADC_H