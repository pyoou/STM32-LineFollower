//
// Created by pyoou on 22.03.2026.
//

#include "sensor.h"

void Sensor_Init(void)
{
    BSP_ADC_Init();
}

float Sensor_CalculateError(void)
{
    uint32_t numerator = 0;
    uint32_t denominator = 0;

    uint16_t weights[6] = {1000, 2000, 3000, 4000, 5000, 6000};

    uint8_t sensors_on_line = 0;

    for (int i = 0; i < 6; i++)
    {
        const uint16_t raw_value = BSP_ADC_GetValue(i);

        if (raw_value > THRESHOLD)
        {
            numerator += (raw_value * weights[i]);
            denominator += raw_value;
            sensors_on_line++;
        }
    }

    if (sensors_on_line == 0)
    {
        return 0.0f;
    }

    const float position = (float)numerator / (float) denominator;

    const float error = position - SENSOR_CENTER_VALUE;

    return error;
}