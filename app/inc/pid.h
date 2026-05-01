/**
 * @file pid.h
 * @author pyoou (https://github.com/pyoou)
 * @brief PID logic for motion
 * @version 0.1
 * @date 2026-03-29
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef LINEFOLLOWER_PID_H
#define LINEFOLLOWER_PID_H

typedef struct
{
  float Kp; // proportional value
  float Ki; // integral value
  float Kd; // derivative value

  float prev_error; // previous error
  float integral;

  float out_max; // max out value (antiwindup)
  float out_min; // min out value (antiwindup)
} PID_Controller;

/**
 * @brief
 *
 * @param pid
 * @param kp
 * @param ki
 * @param kd
 * @param min_out
 * @param max_out
 */
void PID_Init(PID_Controller *pid, float kp, float ki, float kd, float min_out,
              float max_out);

/**
 * @brief Calculate pid based on sensor values
 *
 * @param pid -> pid controller pointer @ref PID_Controller
 * @param error -> error value
 * @return float -> movement correction value
 */
float PID_Calculate(PID_Controller *pid, float error);

/**
 * @brief Restart previously saved pid values
 *
 * @param pid -> pointer for pid @ref PID_Controller
 */
void PID_Reset(PID_Controller *pid);

#endif // LINEFOLLOWER_PID_H