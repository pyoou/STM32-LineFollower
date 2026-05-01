//
// Created by pyoou on 22.03.2026.
//

#include "pid.h"

void PID_Init(PID_Controller *pid, const float kp, const float ki, const float kd, const float min_out,
              const float max_out)
{
    pid->Kp = kp;
    pid->Ki = ki;
    pid->Kd = kd;

    pid->out_min = min_out;
    pid->out_max = max_out;

    PID_Reset(pid);
}

void PID_Reset(PID_Controller *pid)
{
    pid->prev_error = 0.0f;
    pid->integral = 0.0f;
}

float PID_Calculate(PID_Controller *pid, float error)
{
    /* Proportional */
    const float P_out = pid->Kp * error;

    /* Integral */
    pid->integral += error;
    const float I_out = pid->Ki * pid->integral;

    /* Derivative */
    const float derivative = error - pid->prev_error;
    const float D_out = pid->Kd * derivative;

    pid->prev_error = error;

    /* Sum of PID */
    float output = P_out + I_out + D_out;

    /* Anti-Windup */
    if (output > pid->out_max)
    {
        output = pid->out_max;
    } else if (output < pid->out_min)
    {
        output = pid->out_min;
    }

    return output;
}
