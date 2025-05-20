#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include "main.h"

#define MOTOR_LEFT_IN1 GPIO_PIN_8 // PB8포트
#define MOTOR_LEFT_IN2 GPIO_PIN_9 // PB9포트

#define MOTOR_RIGHT_IN3 GPIO_PIN_10 // PC10포트
#define MOTOR_RIGHT_IN4 GPIO_PIN_11 // PC11포트


#define MOTOR_LEFT_IN1_PORT GPIOB 	// PB8
#define MOTOR_LEFT_IN2_PORT GPIOB	// PB9

#define MOTOR_RIGHT_IN3_PORT GPIOC
#define MOTOR_RIGHT_IN4_PORT GPIOC

#define MOTOR_SPEED_100 1000
#define MOTOR_SPEED_99 990
#define MOTOR_SPEED_90 900
#define MOTOR_SPEED_80 800
#define MOTOR_SPEED_70 700
#define MOTOR_SPEED_60 600
#define MOTOR_SPEED_50 500
#define MOTOR_SPEED_40 400
#define MOTOR_SPEED_30 300
#define MOTOR_SPEED_20 200
#define MOTOR_SPEED_10 100
#define MOTOR_SPEED_0 0

void Motor_right_control(int speed_left, int speed_right);
void Motor_left_control(int speed_left, int speed_right);
void Motor_front_control(int speed_left, int speed_right);
void Motor_back_control(int speed_left, int speed_right);
void Motor_break_control(int speed_left, int speed_right);


// 전진하면서 우회전 H
void Drive_Forward_Turn_Right(int speed_left, int speed_right);
// 전진화면서 좌히전 G
void Drive_Forward_Turn_Left(int speed_left, int speed_right);
// 후진하면서 우회전 J
void Drive_Backward_Turn_Right(int speed_left, int speed_right);
// 후진하면서 좌희전 I
void Drive_Backward_Turn_Left(int speed_left, int speed_right);



#endif /* INC_MOTOR_H_ */
