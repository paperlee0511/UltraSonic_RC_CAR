/*
 * auto_pilot.h
 *
 *  Created on: May 13, 2025
 *      Author: USER1
 */

#ifndef INC_AUTO_PILOT_H_
#define INC_AUTO_PILOT_H_

#include "ultrasonic.h"
#include "main.h"
#include "state_machine.h"
#include "delay.h"
#include "motor.h"

extern uint8_t front_distance;
extern uint8_t left_distance;
extern uint8_t right_distance;

#define ACTION_INTERVAL 5  // 모터 동작 간 최소 간격
#define TURN_INTERVAL 5  // 모터 동작 간 최소 간격
#define BACK_INTERVAL 100

//초음파 거리 기반 경로 판단
void Auto_Pilot_Update(void);
void Update_Distance_Filter(void);

// 추가 함수.
void do_back_and_turn(uint32_t now, int side_diff);






#endif /* INC_AUTO_PILOT_H_ */
