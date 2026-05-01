/**
 * @file sensor.h
 * @author pyoou (https://github.com/pyoou)
 * @brief initialization and reading the deviation from the sensors
 * @version 0.1
 * @date 2026-03-29
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef LINEFOLLOWER_SENSOR_H
#define LINEFOLLOWER_SENSOR_H

#include "adc.h"
#include <stdint.h>

#define THRESHOLD 2000
#define SENSOR_CENTER_VALUE 3500.0f

/**
 * @brief Initialize sensor
 *
 */
void Sensor_Init(void);

/**
 * @brief Calculate Sensor Deviation Error
 *
 * @return float -> Deviation Error
 */
float Sensor_CalculateError(void);

#endif // LINEFOLLOWER_SENSOR_H
