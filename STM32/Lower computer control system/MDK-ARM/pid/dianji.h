#ifndef __DIANJI_H
#define __DIANJI_H

#include "main.h"
#include "tim.h"
#define IN_SET HAL_GPIO_WritePin
#define SET GPIO_PIN_SET
#define RESET GPIO_PIN_RESET
#define PWM_SET __HAL_TIM_SetCompare

#define A1_PORT GPIOB
#define A2_PORT GPIOB
#define B1_PORT GPIOB
#define B2_PORT GPIOB
#define C1_PORT GPIOD
#define C2_PORT GPIOB
#define D1_PORT GPIOD
#define D2_PORT GPIOD

#define A1_PIN GPIO_PIN_6
#define A2_PIN GPIO_PIN_7
#define B1_PIN GPIO_PIN_4
#define B2_PIN GPIO_PIN_5
#define C1_PIN GPIO_PIN_7
#define C2_PIN GPIO_PIN_3
#define D1_PIN GPIO_PIN_5
#define D2_PIN GPIO_PIN_6

#define A_HANDLE &htim8
#define B_HANDLE &htim8
#define C_HANDLE &htim4
#define D_HANDLE &htim4
#define A_CHANNLE TIM_CHANNEL_2
#define B_CHANNLE TIM_CHANNEL_3
#define C_CHANNLE TIM_CHANNEL_2
#define D_CHANNLE TIM_CHANNEL_3

void go(int i);
void back(int x);
void Left_set(int i,int e,int speed);
void Right_set(int i,int e,int speed);
void Stop(void);

#endif
