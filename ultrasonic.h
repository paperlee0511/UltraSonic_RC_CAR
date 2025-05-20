
#ifndef INC_ULTRASONIC_H_
#define INC_ULTRASONIC_H_


#include "main.h"
#include "tim.h"
#include "delay.h"

#define sonic_left_port GPIOB
#define sonic_front_port GPIOB
#define sonic_right_port GPIOB

#define sonic_left_pin GPIO_PIN_5
#define sonic_front_pin GPIO_PIN_4
#define sonic_right_pin GPIO_PIN_3
#define TRIGGER_SECOND 50



void HCSR04_Trigger_front(void);
void HCSR04_Trigger_left(void);
void HCSR04_Trigger_right(void);

void Update_left_ultrasonic(void);
void Update_front_ultrasonic(void);
void Update_right_ultrasonic(void);

// 필터





#endif /* INC_ULTRASONIC_H_ */
