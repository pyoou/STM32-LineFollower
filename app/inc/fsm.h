/**
 * @file fsm.h
 * @author pyoou (https://github.com/pyoou)
 * @brief Finite-State Machine logic and settings
 * @version 0.1
 * @date 2026-03-29
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef LINEFOLLOWER_FSM_H
#define LINEFOLLOWER_FSM_H

#include "blink.h"
#include "motor.h"
#include "pid.h"
#include "sensor.h"

/* List of machine states */
typedef enum
{
  STATE_IDLE,        // Waiting for start
  STATE_CALIBRATION, // Sensor Calibration
  STATE_RUNNING,     // Running
  STATE_LOST,        // Lost line
  STATE_STOP         // End of the run
} RobotState_t;

/**
 * @brief Initialize robot state
 * @retval HAL_StatusTypeDef: Status operacji (HAL_OK, HAL_ERROR)
 *
 */
void FSM_Init(void);

/**
 * @brief Safe state change
 *
 * @param new_state -> setup a new state @ref RobotState_t
 */
void FSM_SetState(RobotState_t new_state);

/**
 * @brief Get current robot state
 *
 * @return RobotState_t -> current state @ref RobotState_t
 */
RobotState_t FSM_GetState(void);

/**
 * @brief
 *
 * @param pid -> pid controller pointer
 * @param left_motor -> left motor pointer
 * @param right_motor -> right motor pointer
 */
void FSM_Update(PID_Controller *pid, Motor_t *left_motor, Motor_t *right_motor);

#endif /* LINEFOLLOWER_FSM_H */