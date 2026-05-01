#include "fsm.h"

#define BASE_SPEED 4000

static RobotState_t current_state = STATE_RUNNING;

void FSM_Init(void) { current_state = STATE_RUNNING; }

void FSM_SetState(RobotState_t new_state) { current_state = new_state; }

RobotState_t FSM_GetState(void) { return current_state; }

void FSM_Update(PID_Controller *pid, Motor_t *left_motor, Motor_t *right_motor)
{
  switch (current_state)
  {
  case STATE_IDLE:
    // Pit stop motors
    Motor_Stop(left_motor);
    Motor_Stop(right_motor);

    Blink_Process(500);
    // HAL_Delay(50);

    // Waiting for button press PA0 [KEY]
    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
    {
      HAL_Delay(50); // Debouncing

      if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
      {
        while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
          ;
        HAL_Delay(50);

        PID_Reset(pid);

        HAL_Delay(500);

        FSM_SetState(STATE_RUNNING);
      }
    }
    break;

  case STATE_CALIBRATION:
    // TODO: in future calibration
    FSM_SetState(STATE_RUNNING);
    break;

  case STATE_RUNNING:
  {
    // float current_error = Sensor_CalculateError();

    // if (current_error == 9999.0f)
    // {
    //   FSM_SetState(STATE_LOST);
    //   break;
    // }

    // float correction = PID_Calculate(pid, current_error);
    Blink_Process(1000);

    const int correction = 0;
    Motor_SetSpeed(left_motor, BASE_SPEED + correction);
    Motor_SetSpeed(right_motor, BASE_SPEED + correction);
    break;
  }

  case STATE_LOST:
    Motor_Stop(left_motor);
    Motor_Stop(right_motor);

    FSM_SetState(STATE_IDLE);
    break;

  case STATE_STOP:
    Motor_Stop(left_motor);
    Motor_Stop(right_motor);
    break;

  default:
    FSM_SetState(STATE_RUNNING);
    break;
  }
}