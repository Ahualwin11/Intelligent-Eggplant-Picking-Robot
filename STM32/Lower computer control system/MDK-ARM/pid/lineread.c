#include "lineread.h"
#include "dianji.h"
#include "stdio.h"
int sj[4]={0,0,0,0};
/*
对应4路循迹模块从左到右
E0--------X2
E1--------X1
B8--------X3
B9--------X4
*/

float err,last_err;

//读取循迹模块的4路电压值
void sj_read(void)
{
	sj[0] = HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_0);
	sj[1] = HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_1);
	sj[2] = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8);
	sj[3] = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9);
	
	//将4个电压值转为偏差

	if(sj[0]==1 && sj[1]==1 && sj[2]==0 && sj[3]==1)             //0010
	err=1;
	else if(sj[0]==1 && sj[1]==1 && sj[2]==1 && sj[3]==0)             //0001
	err=2;
	else if(sj[0]==1 && sj[1]==0 && sj[2]==0 && sj[3]==0)             //0111
	err=3;	
	else if(sj[0]==1 && sj[1]==0 && sj[2]==1 && sj[3]==1)             //0100
	err=-1;
	else if(sj[0]==0 && sj[1]==1 && sj[2]==1 && sj[3]==1)             //1000
	err=-2;
	else if(sj[0]==0 && sj[1]==0 && sj[2]==0 && sj[3]==1)             //1110
	err=-3;
	else if(sj[0]==1 && sj[1]==0 && sj[2]==0 && sj[3]==1)             //0110
	err=0;
	printf("x1:%d,x2:%d,x3:%d,x4:%d\n",sj[0],sj[1],sj[2],sj[3]);
}

int motor_pid(void)
{
	int output;
	float kp=850,ki=0,kd=0;
	float P,I,D;
	P = err;
	I += err;
	D = err-last_err;
	output = kp*P +ki*I + kd*D;
	last_err = err;
	return output;
}

void motor_run(int speed,int x,int y)
{
	Left_set(x,err,speed);
	Right_set(y,err,speed);
}

void _run(int speed)
{
	extern int flag;
	//int pid;
	sj_read();
	while(err==3 | err==-3 |err==2 | err==-2)
	{
	 sj_read();
	 rx_proc();if(flag != 2) break;
	 if(err!=0) continue;
	 motor_run(speed,speed+motor_pid(),speed-motor_pid());
	 //pid = motor_pid();
	 //printf("left:%d   right:%d",speed+pid,speed-pid);
	 HAL_Delay(50);
	}
//	while(err==2 | err==-2)
//	{
//	 sj_read();
//		rx_proc();
//	 if(err!=0) continue;
//	 motor_run(speed,speed+motor_pid(),speed-motor_pid());
//	 pid = motor_pid();
//	 //printf("left:%d   right:%d",speed+pid,speed-pid);
//	 HAL_Delay(50);
//	}
	 motor_run(speed,speed+motor_pid(),speed-motor_pid());
	 //pid = motor_pid();
	 //printf("left:%d   right:%d",speed+pid,speed-pid);
	 HAL_Delay(50);
}

//寻中线模式
void find_mid_mode(int dif)
{
	if(dif>0)
	{
		go(dif * 10);
	}
	else
	{
		back(dif * 10);
	}
}
