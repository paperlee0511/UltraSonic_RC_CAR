/*
 * state_machine.h
 *
 *  Created on: May 13, 2025
 *      Author: USER1
 */

#ifndef INC_STATE_MACHINE_H_
#define INC_STATE_MACHINE_H_

#include "main.h"

typedef enum {
    Drive, Reverse, Right, Left,
    Forward_Turn_Right, Forward_Turn_Left,
    Back_Turn_Right, Back_Turn_Left,
    Break, Auto_Pilot
} CarState ;

extern CarState  Current_state;
extern uint32_t last_user_input_time;

void HandleCarState(void);	// 상태 실행
void SetCarState(CarState state);	//상태 전



#endif /* INC_STATE_MACHINE_H_ */
