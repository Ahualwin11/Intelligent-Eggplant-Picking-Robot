#include "duoji.h"
#include "math.h"
#include "stdio.h"
#include <stdlib.h> 
#define PI 3.141592653
extern the t;
extern int axie[];
/**********���Ŷ�Ӧ��************/
/*
PE11-------AXIE1
PE13-------AXIE2
PB1--------AXIE3
PA2--------AXIE4
PA6--------AXIE5
*/
int axie_copy[5]; //����Ƕȴ洢ֵ
//��е�� ��Ƕȿ���
//axis���ı���
//angle���ı�Ƕ�
void Axis_angle(uint16_t axis,uint16_t angle)
{
	double k;
	uint16_t Axis_pwm=0;
	switch(axis)
	{
		case 1:
			k=200.0/270.0;
			Axis_pwm=((int)(270-angle)*k)+55;
			__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,Axis_pwm);
		  break;
		case 2:
//			if(angle<=5) angle = 5;
//			if(angle>=175) angle = 175;
			k=190.0/180.0;    //5   //175
			Axis_pwm=((int)(180-angle)*k)+50;
			__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_3,Axis_pwm);

			break;
		case 3:
			k=175.0/270.0;
			Axis_pwm=((int)(270-angle)*k)+50;
			__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,Axis_pwm);
			break;		
		case 4:
			k=175.0/270.0;
			Axis_pwm=((int)(angle)*k)+55;
			__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_3,Axis_pwm);
			break;
		case 5:
			k=200.0/180.0;
			Axis_pwm=((int)angle*k)+50;
			__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,Axis_pwm);
			break;
	}
}
/*��е�۽Ƕȳ�ʼ��*/
int x;
void arm_init(void)
{
	extern int axie[];
	extern int axie_copy[];
	for(x=0;x<5;x++)
	{
		axie_copy[x] = axie[x];
	}
	Axis_angle(1,axie[0]);
	HAL_Delay(500);
	Axis_angle(2,axie[1]);
	HAL_Delay(500);
	Axis_angle(3,axie[2]);
	HAL_Delay(500);
	Axis_angle(4,axie[3]);
	HAL_Delay(500);
	Axis_angle(5,axie[4]); //ĩ��צǯ�պ�
	HAL_Delay(500);
//	HAL_Delay(1000);//�ȴ��������
}

void arm_control(uint16_t a1,uint16_t a2,uint16_t a3,uint16_t a4,uint16_t a5)
{
	int time;
	extern int axie_copy[]; //��¼��һ�λ�е�۽Ƕ�
	int flag0=1,flag1=1,flag2=1,flag3=1,flag4=1;
	while(flag0|flag1|flag2|flag3|flag4)
	{
		//��һ����ת������
		if(axie[0]>axie_copy[0]) axie_copy[0]++;
		else if(axie[0]<axie_copy[0]) axie_copy[0]--;
		else flag0 = 0;
		//�ڶ�����ת������
		if(axie[1]>axie_copy[1]) axie_copy[1]++;
		else if(axie[1]<axie_copy[1]) axie_copy[1]--;
		else flag1 = 0;
		//��������ת������
		if(axie[2]>axie_copy[2]) axie_copy[2]++;
		else if(axie[2]<axie_copy[2]) axie_copy[2]--;
		else flag2 = 0;
		//���ĸ���ת������
		if(axie[3]>axie_copy[3]) axie_copy[3]++;
		else if(axie[3]<axie_copy[3]) axie_copy[3]--;
		else flag3 = 0;
		//�������ת������
		if(axie[4]>axie_copy[4]) axie_copy[4]++;
		else if(axie[4]<axie_copy[4]) axie_copy[4]--;
		else flag4 = 0;
		
		//���ƶ��ת��		
		time = 20;
		Axis_angle(1,axie_copy[0]);
		HAL_Delay(time);
		Axis_angle(2,axie_copy[1]);
		HAL_Delay(time);
		Axis_angle(3,axie_copy[2]);
		HAL_Delay(time);
		Axis_angle(4,axie_copy[3]);
		HAL_Delay(time);
		Axis_angle(5,axie_copy[4]); //ĩ��צǯ�պ�
		HAL_Delay(time);	
	}
	t.n1 = axie[0];t.n2 = axie[1];t.n3 = axie[2];t.n4 = axie[3];//��th�ṹ���б����е���ֽǶ�
	t.n_x = t.x;t.n_y = t.y;t.n_z = t.z;//����th�Ļ�е��ĩ��������
//	for(int x=0;x<5;x++)
//	{
//		axie_copy[x] = axie[x];
//	}
}
void pro_ni(void)
{
	float val = 180/PI; //����ת�Ƕ� 
	//float cal = PI/180;//�Ƕ�ת���� 
 	t.px = t.x-163.08;t.py = t.y;t.pz = t.z-69.95;
	if(((t.px*t.px+t.py*t.py+t.pz*t.pz)-22812.25)>22770)
	{//�ж�px��py��pzֵ�Ƿ���Ҫ���� 
		//printf("theta3 Error! Please input again\n");
		t.t1=0;t.t2[0]=0;t.t2[1]=0;t.t3=0.0;t.t4[0]=0.0;t.t4[1]=0.0;
	}
	else{
		//���theta3��ֵ  �����Ƽ��� 
		t.t3 = -acos(((t.px*t.px+t.py*t.py+t.pz*t.pz)-22812.25)/22770); 
		t.f1 = 103.5*cos(t.t3)+110; 
		t.f2 = 103.5*sin(t.t3);
		t.f3 = 0;
		//���theta2��������� ���� 
		t.t2[0] =  2*atan((t.f1+sqrt(t.f1*t.f1+t.f2*t.f2-t.pz*t.pz))/(t.f2-t.pz));
		//t.t2[1] =  2*atan((t.f1-sqrt(t.f1*t.f1+t.f2*t.f2-t.pz*t.pz))/(t.f2-t.pz));
		//���theta1 ����
		t.t1 = atan2(t.y,t.x);
		//���theta4��������� ����
		t.t34[0] = sin(t.t3 + t.t2[0]);
		//t.t34[1] = sin(t.t3 + t.t2[1]);
		 
		t.t4[0] = -asin(t.t34[0]);
		//t.t4[1] = -asin(t.t34[1]);
		//printf("t4_1 = %.f , t4_2 = %.f\n",t.t4[0]*val,t.t4[1]*val);
		//������תΪ�Ƕȣ��������ֵתΪʵ��ת�� 
		t.t1 = t.t1*val;
		t.t3 = ((t.t3*val)+135);  //ת���ĽǶ�Ϊ���ʵ��ת���Ƕȣ���Ϊ���Ƕ�
		t.t2[0] = 180+(t.t2[0]*val);
		//t.t2[1] = (t.t2[1]*val)+90;
		t.t4[0] = (t.t4[0]*val)+135;
		//t.t4[1] = (t.t4[1]*val)+45;
		t.theta1 = t.t1;t.theta3 = t.t3;t.theta2 = t.t2[0];t.theta4 = t.t4[0];
	}
} 
//ѡȡ���ʽǶ�  //ȡ��
//void pro_jd(void)
//{
//	t.theta1 = t.t1;t.theta3 = t.t3;
//	if ((t.t1>=-0.1 && t.t2[0]>=-0.1 && t.t3>=-0.1 && t.t4[0]>=-0.1 && t.t3<=270)&&
//       (t.t1>=-0.1 && t.t2[1]>=-0.1 && t.t3>=-0.1 && t.t4[1]>=-0.1 && t.t3<=270))
//	   {
//	   	float s1 = abs(t.t2[0]-t.n2);
//        float s2 = abs(t.t2[1]-t.n2);
//        if(s1>s2){
//        	t.theta2 = t.t2[1];t.theta4 = t.t4[1];
//		}
//		else if(s1 == s2){
//			t.theta2 = t.t2[1];t.theta4 = t.t4[1];
//		}
//		else{
//			t.theta2 = t.t2[0];t.theta4 = t.t4[0];
//		}
//			}
//	else if((t.t1>=-0.1 && t.t2[0]>=-0.1 && t.t3>=-0.1 && t.t4[0]>=-0.1 && t.t3<=270)){
//	t.theta2 = t.t2[0];t.theta4 = t.t4[0];
//	}     
//	else if((t.t1>=-0.1 && t.t2[1]>=-0.1 && t.t3>=-0.1 && t.t4[1]>=-0.1 && t.t3<=270)){
//	t.theta2 = t.t2[1];t.theta4 = t.t4[1];
//	}
//	else{ //printf("�Ƕȴ��󣬻�е���޷�����\n");
//	}
//}
//��е��x����ƽ�� 

//�������˶� ������������ϵ���꣬��е��ʵ����Ӧ���˶�
void world_move(int x,int y,int z)
{
	t.x = x;t.y = y;t.z = z;
	pro_ni();
	axie[1]=t.theta2;axie[2]=t.theta3;axie[3]=t.theta4;
	arm_control(axie[0],axie[1],axie[2],axie[3],axie[4]);

}
void move_x(int jl,int dif){    //jl �ƶ���������ʸ����,dif ÿ���ƶ��ľ���  jlҪΪdif�ı��� 
	while(jl!=0){
	if(jl>0){		//����ͷ�����Ӿ���С�ڣ� ֹͣ�˶� 
		t.x = t.n_x + dif;
		pro_ni();
		//pro_jd();
		HAL_Delay(2);
		axie[1]=t.theta2;axie[2]=t.theta3;axie[3]=t.theta4;
		arm_control(axie[0],axie[1],axie[2],axie[3],axie[4]);
		jl=jl-dif; 
	}
	else if(jl<0){
		t.x = t.n_x - dif;
		pro_ni();
		//pro_jd();
		HAL_Delay(2);
		axie[1]=t.theta2;axie[2]=t.theta3;axie[3]=t.theta4;
		arm_control(axie[0],axie[1],axie[2],axie[3],axie[4]);
		jl=jl+dif; 		
	}
	HAL_Delay(1);
	}
} 
//��е��y����ƽ�� 
void move_y(int jl,int dif){    //jl �ƶ���������ʸ����,dif ÿ���ƶ��ľ���  jlҪΪdif�ı��� 
	while(jl!=0){
	if(jl>0){		//����ͷ�����Ӿ���С�ڣ� ֹͣ�˶� 
		t.y = t.n_y + dif;
		pro_ni();
		//pro_jd();
		HAL_Delay(2);
		axie[0]=t.theta1;axie[1]=t.theta2;axie[2]=t.theta3;axie[3]=t.theta4;
		arm_control(axie[0],axie[1],axie[2],axie[3],axie[4]);
		jl=jl-dif; 
	}
	else if(jl<0){
		t.y = t.n_y - dif;
		pro_ni();
		//pro_jd();
		HAL_Delay(2);
		axie[0]=t.theta1;axie[1]=t.theta2;axie[2]=t.theta3;axie[3]=t.theta4;
		arm_control(axie[0],axie[1],axie[2],axie[3],axie[4]);
		jl=jl+dif; 		
	}
	HAL_Delay(1);
	}
}
//��е��z����ƽ�� 
void move_z(int jl,int dif){    //jl �ƶ���������ʸ����,dif ÿ���ƶ��ľ���  jlҪΪdif�ı��� 
	while(jl!=0){
	if(jl>0){		//����ͷ�����Ӿ���С��30 ֹͣ�˶� 
		t.z = t.n_z + dif;
		pro_ni();
		//pro_jd();
		HAL_Delay(2);
		axie[1]=t.theta2;axie[2]=t.theta3;axie[3]=t.theta4;
		arm_control(axie[0],axie[1],axie[2],axie[3],axie[4]);
		jl=jl-dif; 
	}
	else if(jl<0){
		t.z = t.n_z - dif;
		pro_ni();
		//pro_jd();
		HAL_Delay(2);
		axie[1]=t.theta2;axie[2]=t.theta3;axie[3]=t.theta4;
		arm_control(axie[0],axie[1],axie[2],axie[3],axie[4]);
		jl=jl+dif; 		
	}
	HAL_Delay(1);
	}
}

//����0����ת
void move_axie0(int jl,int dif)
{    //jl �ƶ���������ʸ����,dif ÿ���ƶ��ľ���  jlҪΪdif�ı��� 
	while(jl!=0){
	if(jl>0){		//����ͷ�����Ӿ���С��30 ֹͣ�˶� 
		axie[0] = axie[0] + dif;
		HAL_Delay(2);
		arm_control(axie[0],axie[1],axie[2],axie[3],axie[4]);
		jl=jl-dif; 
	}
	else if(jl<0){
		axie[0] = axie[0] - dif;
		HAL_Delay(2);
		arm_control(axie[0],axie[1],axie[2],axie[3],axie[4]);
		jl=jl+dif; 		
	}
	}
} 
//����ĩ�˻�������ץȡ
//1��ʵ�м����˶�
//0��ʵ���ſ��˶�
void extremity_set(int flag)
{
	if(flag)axie[4]=73;
	else axie[4]=100;
	arm_control(axie[0],axie[1],axie[2],axie[3],axie[4]);
}
//��е�۴����Ҳ� �����ڴ����״̬ px: 211.26, py: 0, pz: 201.76
void wait_mode(void)  						//theta:0,117,36,153,90
{
	world_move(211,0,201);
	axie[0]=225;
	arm_control(axie[0],axie[1],axie[2],axie[3],axie[4]);
	extremity_set(0);
}

//���뼤�����distance ��distance>100mmʱ����x��������10mm
//ֱ��distance<70mm�ǣ�ֹͣ�˶� ʵ�м����˶�
void move_x_mode(void) 
{
	extern int distance;
	while(!distance) rx_proc();
	while(distance>100)
	{
		if(t.n_x>325) break;
		rx_proc();
		move_x(5,1);//��е��ǰ��5mm
	} 
	
	extremity_set(1); //�����˶�
}

//ץȡ����ģʽ
//����е�����̧�ߴ�����ת��е�۵���ǰ����ת������ʹ������б��
//ʵ���ſ�צǯ����  ����̧�ߴ���  ʹflag = 1 �ظ�ѭ��
void glab_place_mode(void)
{
	//̧�߻�е�� px: 286.26, py: 0, pz: 241.76
	//0,63,116,179,90 0�᲻�ı䣬ֻ̧��ǰ��е�۽Ƕ�
	//t.x = 286;t.y = 0;t.z = 241; //̧��
	world_move(286,0,241);
	axie[0] = 135; //ת������ǰ
	arm_control(axie[0],axie[1],axie[2],axie[3],axie[4]);
	axie[3] = 220; //��ת������ ��б����
	arm_control(axie[0],axie[1],axie[2],axie[3],axie[4]);
	extremity_set(0);//�ɿ�צǯ
	world_move(286,0,241);	//̧��	
}

void duoji_pwmstart(void)
{
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
}
void duoji_pwmstop(void)
{
	HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_2);
	HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_3);
	HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_4);
	HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_3);
	HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_1);
}

