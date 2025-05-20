

#include "delay.h"

// 같은 타이머를 사용하기떄문에 초음파를 여러개 사용하면 꼬임... 타이머 변경해야함

void delay_us_left(uint16_t us)
{
	// 현재 나는 tim3의 ch1,
	__HAL_TIM_SET_COUNTER(&htim3, 0); 	// 카운터값을 셋 하는 함수
	while((__HAL_TIM_GET_COUNTER(&htim3)) < us);	// 카운터... 뭘 하는거였지 // 이것이 딜레이 만드는 함수
}

void delay_us_front(uint16_t us)
{
	// 현재 나는 tim1의 ch1,
	__HAL_TIM_SET_COUNTER(&htim1, 0); 	// 카운터값을 셋 하는 함수
	while((__HAL_TIM_GET_COUNTER(&htim1)) < us);	// 카운터... 뭘 하는거였지 // 이것이 딜레이 만드는 함수
}

void delay_us_right(uint16_t us)
{
	// 현재 나는 tim2의 ch1,
	__HAL_TIM_SET_COUNTER(&htim2, 0); 	// 카운터값을 셋 하는 함수
	while((__HAL_TIM_GET_COUNTER(&htim2)) < us);	// 카운터... 뭘 하는거였지 // 이것이 딜레이 만드는 함수
}



