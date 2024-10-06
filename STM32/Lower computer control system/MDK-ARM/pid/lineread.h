#ifndef _LINEREAD_H_
#define _LINEREAD_H_

#include "main.h"
void sj_read(void);
int motor_pid(void);
void motor_run(int speed,int x,int y);
void _run(int speed);
void find_mid_mode(int dif);

#endif
