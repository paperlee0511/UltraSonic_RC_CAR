
#include "ultrasonic.h"
#include "stdio.h"

static uint16_t IC_left_Value1 = 0;		// 에코핀이 하이엣지일때
static uint16_t IC_left_Value2 = 0;		// 에코핀이 로우엣지일때
static uint16_t left_echoTime = 0;		// 에코핀의 하이엣지와 로우엣지 사이의 시간(카운트갯수)
static uint8_t left_captureFlag = 0;	// 엣지됬음을 확인
uint8_t left_distance = 0;				// 각 초음파별 거리


static uint16_t IC_front_Value1 = 0;
static uint16_t IC_front_Value2 = 0;
static uint16_t front_echoTime = 0;
static uint8_t front_captureFlag = 0;
uint8_t front_distance = 0;


static uint16_t IC_right_Value1 = 0;
static uint16_t IC_right_Value2 = 0;
static uint16_t right_echoTime = 0;
static uint8_t right_captureFlag = 0;
uint8_t right_distance = 0;


// static을 걸면 다른 C,H에서 접근을 하지 못한다.

//tim3, ch1 사용, left, gpio PB5 사용
void HCSR04_Trigger_left(void)
{
	HAL_GPIO_WritePin(sonic_left_port, sonic_left_pin, 0);
	delay_us_front(1);

	HAL_GPIO_WritePin(sonic_left_port, sonic_left_pin, 1);	// 데이터시트 참고
	delay_us_front(10);	// 펄스 내보내기 위해 10us동안 딜레이
	HAL_GPIO_WritePin(sonic_left_port, sonic_left_pin, 0);

	__HAL_TIM_ENABLE_IT(&htim3, TIM_IT_CC1);	// 타이머의 인터럽트를 활성화 할껀데 누구를 ? -> 타이머3번의 타이머 인터럽트 채널 1번

}

//tim1, ch1 사용, front, gpio PB4 사용
void HCSR04_Trigger_front(void)
{
	HAL_GPIO_WritePin(sonic_front_port, sonic_front_pin, 0);
	delay_us_left(1);

	HAL_GPIO_WritePin(sonic_front_port, sonic_front_pin, 1);	// 데이터시트 참고
	delay_us_left(10);	// 펄스 내보내기 위해 10us동안 딜레이
	HAL_GPIO_WritePin(sonic_front_port, sonic_front_pin, 0);

	__HAL_TIM_ENABLE_IT(&htim1, TIM_IT_CC1);	// 타이머의 인터럽트를 활성화 할껀데 누구를 ? -> 타이머3번의 타이머 인터럽트 채널 1번
}

//tim2, ch1 사용, right, gpio PB3 사용
void HCSR04_Trigger_right(void)
{
	HAL_GPIO_WritePin(sonic_right_port, sonic_right_pin, 0);
	delay_us_right(1);

	HAL_GPIO_WritePin(sonic_right_port, sonic_right_pin, 1);	// 데이터시트 참고
	delay_us_right(10);	// 펄스 내보내기 위해 10us동안 딜레이
	HAL_GPIO_WritePin(sonic_right_port, sonic_right_pin, 0);

	__HAL_TIM_ENABLE_IT(&htim2, TIM_IT_CC1);	// 타이머의 인터럽트를 활성화 할껀데 누구를 ? -> 타이머3번의 타이머 인터럽트 채널 1번

}

// 현재 tim3의 ch1을 사용한 inputchapture callback 함수
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{	// tim3의 ch1 사용할떄 // left, gpio PB5 사용
	if(htim->Instance == TIM3 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
	{
		if(left_captureFlag == 0)	// 아직 캡쳐 안했으면
		{
			// 첫번째 밸류에 캡처인터럽트가 발생하면 카운트값을 가져옴
			IC_left_Value1 = HAL_TIM_ReadCapturedValue(&htim3, TIM_CHANNEL_1);
			left_captureFlag=1;	// 캡처 했다고 플래그 세움

			__HAL_TIM_SET_CAPTUREPOLARITY(&htim3, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING);

		}
		else if(left_captureFlag == 1)	// 한번 캡쳐 했으면
		{
			IC_left_Value2 = HAL_TIM_ReadCapturedValue(&htim3, TIM_CHANNEL_1);
			__HAL_TIM_SET_COUNTER(&htim3,0);

			if(IC_left_Value2 > IC_left_Value1)
			{
				left_echoTime = IC_left_Value2 - IC_left_Value1;
			}
			else if(IC_left_Value1 > IC_left_Value2)
			{
				left_echoTime = (0xFFFF - IC_left_Value1) + IC_left_Value2;
			}

			left_distance = left_echoTime / 58;	// 거리가 나옴 데이터시트 참고

			left_captureFlag = 0;
			__HAL_TIM_SET_CAPTUREPOLARITY(&htim3, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
			__HAL_TIM_DISABLE_IT(&htim3, TIM_IT_CC1);

		}
	}

	// tim1의 ch1 사용할떄 // front, gpio PB4 사용
	if(htim->Instance == TIM1 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
	{
		if(front_captureFlag == 0)	// 아직 캡쳐 안했으면
		{
			// 첫번째 밸류에 캡처인터럽트가 발생하면 카운트값을 가져옴
			IC_front_Value1 = HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_1);
			front_captureFlag=1;	// 캡처 했다고 플래그 세움

			__HAL_TIM_SET_CAPTUREPOLARITY(&htim1, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING);
		}
		else if(front_captureFlag == 1)	// 한번 캡쳐 했으면
		{
			IC_front_Value2 = HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_1);
			__HAL_TIM_SET_COUNTER(&htim1,0);

			if(IC_front_Value2 > IC_front_Value1)
			{
				front_echoTime = IC_front_Value2 - IC_front_Value1;
			}
			else if(IC_front_Value1 > IC_front_Value2)
			{
				front_echoTime = (0xFFFF - IC_front_Value1) + IC_front_Value2;
			}

			front_distance = front_echoTime / 58;	// 거리가 나옴 데이터시트 참고

			front_captureFlag = 0;
			__HAL_TIM_SET_CAPTUREPOLARITY(&htim1, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
			__HAL_TIM_DISABLE_IT(&htim1, TIM_IT_CC1);

		}
	}

	// tim2의 ch1 사용할떄 // right, gpio PB3 사용
	if(htim->Instance == TIM2 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
	{
		if(right_captureFlag == 0)	// 아직 캡쳐 안했으면
		{
			// 첫번째 밸류에 캡처인터럽트가 발생하면 카운트값을 가져옴
			IC_right_Value1 = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_1);
			right_captureFlag=1;	// 캡처 했다고 플래그 세움

			__HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING);

		}
		else if(right_captureFlag == 1)	// 한번 캡쳐 했으면
		{
			IC_right_Value2 = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_1);
			__HAL_TIM_SET_COUNTER(&htim2,0);

			if(IC_right_Value2 > IC_right_Value1)
			{
				right_echoTime = IC_right_Value2 - IC_right_Value1;
			}
			else if(IC_right_Value1 > IC_right_Value2)
			{
				right_echoTime = (0xFFFF - IC_right_Value1) + IC_right_Value2;
			}

			right_distance = right_echoTime / 58;	// 거리가 나옴 데이터시트 참고

			right_captureFlag = 0;
			__HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
			__HAL_TIM_DISABLE_IT(&htim2, TIM_IT_CC1);

		}
	}
}


void Update_left_ultrasonic(void)
{
	static uint32_t sonic_left_time =0;

	if(HAL_GetTick() - sonic_left_time >= TRIGGER_SECOND)
	{
		HCSR04_Trigger_left();
		printf("sonic_left : %d cm\r\n", left_distance);
		sonic_left_time = HAL_GetTick();
	}
}
void Update_front_ultrasonic(void)
{
	static uint32_t sonic_front_time = 0;

	if(HAL_GetTick() - sonic_front_time >= TRIGGER_SECOND)
	{
		HCSR04_Trigger_front();
		printf("sonic_front : %d cm\r\n", front_distance);
		sonic_front_time = HAL_GetTick();
	}

}
void Update_right_ultrasonic(void)
{
	static uint32_t sonic_right_time =0;

	if(HAL_GetTick() - sonic_right_time >= TRIGGER_SECOND)
	{
		HCSR04_Trigger_right();
		printf("sonic_right : %d cm\r\n", right_distance);
		sonic_right_time = HAL_GetTick();
	}

}








