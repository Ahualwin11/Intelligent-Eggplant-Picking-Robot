#ifndef __DUOJI_H_
#define __DUOJI_H_
#include "main.h"
#include "tim.h"

void Axis_angle(uint16_t axis,uint16_t angle);
void arm_init(void);
void arm_control(uint16_t a1,uint16_t a2,uint16_t a3,uint16_t a4,uint16_t a5);
void pro_ni(void);
//void pro_jd(void);
void move_x(int jl,int dif);
void move_y(int jl,int dif);
void move_z(int jl,int dif);
void move_axie0(int jl,int dif);
void wait_mode(void);
void move_x_mode(void);
void extremity_set(int flag);
void glab_place_mode(void);
void duoji_pwmstart(void);
void duoji_pwmstop(void);
#endif
