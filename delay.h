
#ifndef INC_DELAY_H_
#define INC_DELAY_H_

#include "main.h"
#include "tim.h"


void delay_us_front(uint16_t us); 	//16비트를 사용하는 이유가 우리가 사용하는 타이머가 16비트이기 떄문
void delay_us_left(uint16_t us);
void delay_us_right(uint16_t us);




#endif /* INC_DELAY_H_ */
