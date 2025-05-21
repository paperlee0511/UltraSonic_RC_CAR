/*
 * auto_pilot.c
 *
 *  Created on: May 13, 2025
 *      Author: USER1
 */
#include "auto_pilot.h"

/*
 * auto_pilot.c
 *
 *  Created on: May 13, 2025
 *      Author: USER1
 */
#include "auto_pilot.h"

static float filtered_left = 0;
static float filtered_right = 0;
static float filtered_front = 0;

void Update_Distance_Filter(void)
{
    float alpha = 0.4f;

    filtered_left = alpha * (float)left_distance + (1 - alpha) * filtered_left;
    filtered_right = alpha * (float)right_distance + (1 - alpha) * filtered_right;
    filtered_front = alpha * (float)front_distance + (1 - alpha) * filtered_front;

    // 튀는 값 무시 (100cm 이상 값은 비정상으로 간주)
    if (left_distance >= 50) left_distance = (int)filtered_left;
    if (right_distance >= 50) right_distance = (int)filtered_right;
//    if (front_distance >= 120) front_distance = (int)filtered_front;
}

void Auto_Pilot_Update(void)
{
	Update_Distance_Filter();

	static uint32_t last_action_time = 0;
	static uint32_t last_turn_action_time = 0;



	uint32_t now = HAL_GetTick();  // ✅ HAL_GetTick() 한 번만 호출

	int side_diff = left_distance - right_distance;

	// 0. 세 방향 모두 막힘 → 후진 후 좌우 비교
	if(front_distance <= 15 && left_distance <= 15 && right_distance <= 15)

	{
		if(now - last_action_time >= BACK_INTERVAL)
		{
			Motor_back_control(MOTOR_SPEED_80, MOTOR_SPEED_80);
			if(now - last_turn_action_time >= TURN_INTERVAL)
			{
				if(side_diff > 0)
					Motor_left_control(MOTOR_SPEED_50, MOTOR_SPEED_70);
				else if(side_diff < 0)
					Motor_right_control(MOTOR_SPEED_70, MOTOR_SPEED_50);

				last_turn_action_time = now;
			}
			last_action_time = now;
		}
		return;
	}

	// 1. 전방 + 우측 막힘 → 좌회전
	else if(front_distance <= 20 && right_distance <=15)
	{
		if(now - last_action_time >= ACTION_INTERVAL)
		{
			Motor_back_control(MOTOR_SPEED_80, MOTOR_SPEED_80);
			if(now - last_turn_action_time >= TURN_INTERVAL)
			{
				if(right_distance <= 28)
					Motor_left_control(MOTOR_SPEED_70, MOTOR_SPEED_50);

				last_turn_action_time = now;
			}
			last_action_time = now;
		}
		return;
	}

	// 2. 전방 + 좌측 막힘 → 우회전
	else if(front_distance <= 20 && left_distance <= 15)
	{
		if(now - last_action_time >= ACTION_INTERVAL)
		{
			Motor_back_control(MOTOR_SPEED_80, MOTOR_SPEED_80);
			if(now - last_turn_action_time >= TURN_INTERVAL)
			{
				if(left_distance <= 28)
					Motor_right_control(MOTOR_SPEED_50, MOTOR_SPEED_70);

				last_turn_action_time = now;
			}
			last_action_time = now;
		}
		return;
	}

	// 3. 대각선 벽 접근 (측면 가까움) → side_diff 기반 회피
	else if(front_distance >= 3 && (left_distance <= 18 || right_distance <= 18))
	{
		if(now - last_action_time >= ACTION_INTERVAL)
		{
			Motor_back_control(MOTOR_SPEED_80, MOTOR_SPEED_80);
			if(now - last_turn_action_time >= TURN_INTERVAL)
			{
				if(side_diff > 0)
					Motor_left_control(MOTOR_SPEED_70, MOTOR_SPEED_50);
				else if(side_diff<0)
				{
					Motor_right_control(MOTOR_SPEED_50, MOTOR_SPEED_70);
				}
				last_turn_action_time = now;
			}
			last_action_time = now;
		}
		return;
	}

	// 4. 전방만 막힘 → 후진 + side_diff 회피
	else if(front_distance <= 23)
	{
		if(now - last_action_time >= ACTION_INTERVAL)
		{
			Motor_back_control(MOTOR_SPEED_80, MOTOR_SPEED_80);
			if(now - last_turn_action_time >= TURN_INTERVAL)
			{
				if(side_diff > 0)
					Motor_left_control(MOTOR_SPEED_70, MOTOR_SPEED_50);
				else if(side_diff < 0)

					Motor_right_control(MOTOR_SPEED_50, MOTOR_SPEED_70);

				last_turn_action_time = now;
			}
			last_action_time = now;
		}
		return;
	}
	// 5. 세 방향 모두 여유 → 전진
	else if(front_distance >= 21 && left_distance >= 17 && right_distance >= 17)

	{
		if(now - last_action_time >= ACTION_INTERVAL)
		{
			Motor_front_control(MOTOR_SPEED_80, MOTOR_SPEED_80);
			last_action_time = now;
		}
		return;
	}
}


