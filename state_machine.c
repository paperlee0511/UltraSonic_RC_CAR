/*
 * state_machine.c
 *
 *  Created on: May 13, 2025
 *      Author: USER1
 */
#include "state_machine.h"
#include "auto_pilot.h"
#include "motor.h"
#include "main.h"


CarState Current_state = Break;


// 상태 실행
void HandleCarState(void)
{
	switch(Current_state)
	{
	case Drive :
		Motor_front_control(MOTOR_SPEED_90, MOTOR_SPEED_90);
		break;

	case Reverse:
		Motor_back_control(MOTOR_SPEED_90, MOTOR_SPEED_90);
		break;

	case Right: // 왼쪽이 정방향, 오른쪽이 역방향
		Motor_right_control(MOTOR_SPEED_80, MOTOR_SPEED_50);
		break;

	case Left: // Left Turn // 왼쪽이 역방향, 오른쪽이 정방향
		Motor_left_control(MOTOR_SPEED_50, MOTOR_SPEED_80);
		break;

		// 전진하면서 우회전 H
	case Forward_Turn_Right:
		Drive_Forward_Turn_Right(MOTOR_SPEED_80, MOTOR_SPEED_50);
		break;
		// 전진화면서 좌히전 G
	case Forward_Turn_Left:
		Drive_Forward_Turn_Left(MOTOR_SPEED_50, MOTOR_SPEED_80);
		break;
		// 후진하면서 우회전 왼쪽은 정회전, 오른쪽은 역회전
	case Back_Turn_Right:
		Drive_Backward_Turn_Right(MOTOR_SPEED_80, MOTOR_SPEED_50);
		break;
		// 후진하면서 좌희전 I 왼쪽은 역회전, 오른쪽은 정회전
	case Back_Turn_Left :
		Drive_Backward_Turn_Left(MOTOR_SPEED_50, MOTOR_SPEED_80);
		break;

	case Auto_Pilot:
		Auto_Pilot_Update();
		break;

	case Break:
		Motor_break_control(MOTOR_SPEED_0, MOTOR_SPEED_0);
		break;
	}
	if (Current_state != Auto_Pilot && (HAL_GetTick() - last_user_input_time > 8000))
	{
		SetCarState(Auto_Pilot);
	}
}


//상태 전환
void SetCarState(CarState state)
{
	Current_state = state;
}

