
#include "main.h"
#include "motor.h"
#include "tim.h"

extern TIM_HandleTypeDef htim4;

static void motor_set_speed(uint16_t speed_left, uint16_t speed_right)
{
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, speed_left);  // 왼쪽 모터 속도
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, speed_right);  // 오른쪽 모터 속도
}

static void motor_set_direction(GPIO_PinState l_in1, GPIO_PinState l_in2, GPIO_PinState r_in3, GPIO_PinState r_in4)
{
	HAL_GPIO_WritePin(MOTOR_LEFT_IN1_PORT, MOTOR_LEFT_IN1, l_in1);
	HAL_GPIO_WritePin(MOTOR_LEFT_IN2_PORT, MOTOR_LEFT_IN2, l_in2);
	HAL_GPIO_WritePin(MOTOR_RIGHT_IN3_PORT, MOTOR_RIGHT_IN3, r_in3);
	HAL_GPIO_WritePin(MOTOR_RIGHT_IN4_PORT, MOTOR_RIGHT_IN4, r_in4);
}


// Right Turn // 왼쪽이 정방향, 오른쪽이 역방향
void Motor_right_control(int speed_left, int speed_right)
{
	motor_set_speed(speed_left, speed_right);
	motor_set_direction(GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_SET);
}

// Left Turn // 왼쪽이 역방향, 오른쪽이 정방향
void Motor_left_control(int speed_left, int speed_right)
{
	motor_set_speed(speed_left, speed_right);
	motor_set_direction(GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_RESET);
}

// Drive
void Motor_front_control(int speed_left, int speed_right)
{
	motor_set_speed(speed_left, speed_right);
	motor_set_direction(GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_RESET);
}

// Reverse
void Motor_back_control(int speed_left, int speed_right)
{
	motor_set_speed(speed_left, speed_right);
	motor_set_direction(GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_SET);
}

// Break
void Motor_break_control(int speed_left, int speed_right)
{
	motor_set_speed(speed_left, speed_right);
	motor_set_direction(GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_SET);
}

// 전진하면서 우회전 H
void Drive_Forward_Turn_Right(int speed_left, int speed_right)
{
	motor_set_speed(speed_left, speed_right);
	motor_set_direction(GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_SET);
}

// 전진화면서 좌히전 G
void Drive_Forward_Turn_Left(int speed_left, int speed_right)
{
	motor_set_speed(speed_left, speed_right);
	motor_set_direction(GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_RESET);
}

// 후진하면서 우회전 J,  왼쪽은 정회전, 오른쪽은 역회전
void Drive_Backward_Turn_Right(int speed_left, int speed_right)
{
	motor_set_speed(speed_left, speed_right);
	motor_set_direction(GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_SET);

}

// 후진하면서 좌희전 I 왼쪽은 역회전, 오른쪽은 정회전
void Drive_Backward_Turn_Left(int speed_left, int speed_right)
{
	motor_set_speed(speed_left, speed_right);
	motor_set_direction(GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_RESET);

}
