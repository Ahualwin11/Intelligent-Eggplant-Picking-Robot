#ifndef _BSP_I2C_GPIO_H
#define _BSP_I2C_GPIO_H

#include "main.h"
#include <inttypes.h>






void Start_I2c(void);
void Stop_I2c(void);
void  I2C_SendByte(unsigned char  c);
unsigned char I2C_RcvByte(void);
void Ack_I2c(uint8_t a);

uint8_t IIC_Servo(unsigned char servonum,unsigned char angle);

void delay(int z);

#endif

