#include "Mat.h"
//#����Ŀ������������е�۽Ƕ�

//#_w_m_T Ŀ��������������������ת������   -------���� 
//#_w_0_T ��е�۵�����������������ת������  ------Ĭ�� 
//#_0_4_T ����������ڵ������ת������ -------------���� 
//#_4_m_T Ŀ����������ڵ����������ת������--------Ĭ�� 

//1 0 0 100
//0 1 0 100
//0 0 1 100
//0 0 0 1
#define PI 3.141592653
float theta1,theta2,theta3,theta4;
//float do_tt4(float T[3][3]);
int i,j,k,y,a,n,m;
void Multy(float A[4][4],float  B[4][4],float result[4][4] )//����A*B
{//û����AB���в���������ж�
	for (i = 0; i <4; i++)
	{//ȡA��ÿһ�У���3�У����i<3
		for (j = 0; j <  4; j++)
		{//ȡB��ÿһ�У���3�У����j<3
			float sum = 0;
			for (k = 0; k < 4; k++)
			{//��A�е������У�B�е������С����K=4
				sum += A[i][k] * B[k][j];//�������г˻�֮��
			}
			result[i][j] = sum;//����A�ĵ�i����B�ĵ�j�г˻�֮�ͣ���Ϊresult��ijԪ��
		}
	}
}
void Multy_3(float A[3][3],float  B[3][3],float result[3][3] )//����A*B
{//û����AB���в���������ж�
	for (i = 0; i <3; i++)
	{//ȡA��ÿһ�У���3�У����i<3
		for (j = 0; j <  3; j++)
		{//ȡB��ÿһ�У���3�У����j<3
			float sum = 0;
			for (k = 0; k < 3; k++)
			{//��A�е������У�B�е������С����K=4
				sum += A[i][k] * B[k][j];//�������г˻�֮��
			}
			result[i][j] = sum;//����A�ĵ�i����B�ĵ�j�г˻�֮�ͣ���Ϊresult��ijԪ��
		}
	}
}
//ȡ���Ͻ�3*3 �ǶȾ��� 
void _3_3_tran(float org[4][4],float _new[3][3])
{
	for(i=0;i<3;i++)
	{
		for(y=0;y<3;y++)
		_new[i][y] = org[i][y];
	}
}
//��ȡ�ұ߾������ORG
void ORG_tran(float org[4][4],float _new[3][1])
{
	for(a=0;a<3;a++)
	{
		_new[a][0]= org[a][3];
	}
 } 
//���theta����
struct{
	float f1;
	float f2;
	float f3;
	float g1;
	float g2;
	float g3;
}theta_x;
void theta(float ORG[3][1],float * a1,float * a2,float * a3)
{
	//float a1,a2,a3;
//	float f1,f2,f3;
//	float g1,g2,g3;
	float Px=ORG[0][0];float Py=ORG[1][0];float Pz=ORG[2][0];
	//��a3��ֵ 
	if((pow(Py,2)+pow(Px,2)-pow(76.89/2,2))>0)
	*a3=2*atan((-Py+sqrt(pow(Py,2)+pow(Px,2)-pow(76.89/2,2)))/(Px+(-76.89/2))); //���ػ���
	//��b3��ֵ 
//	if((pow(Py,2)+pow(Px,2)-pow(111.9/2,2))>0)
//	*b3=2*atan((-Py-sqrt(pow(Py,2)+pow(Px,2)-pow(111.9/2,2)))/(Px+(-111.9/2))); //���ػ���
	//��f1,f2,f3�����ľ���ֵ �Ӷ���theta2 
	theta_x.f1 = Px*cos(*a3)-Py*sin(*a3)+76.89;                      //cos��x��xΪ���� 
	theta_x.f2 = Px*sin(*a3)+Py*cos(*a3);
	theta_x.f3 = Pz;
	if((pow(theta_x.f2,2)+pow(theta_x.f1,2)-pow(Pz,2))>0) 
	*a2=2*atan((theta_x.f1+sqrt(pow(theta_x.f2,2)+pow(theta_x.f1,2)-pow(Pz,2)))/(theta_x.f2+Pz));
	
//	if((pow(f2,2)+pow(f1,2)-pow(Pz,2))>0) 
//	*b2=2*atan((f1-sqrt(pow(f2,2)+pow(f1,2)-pow(Pz,2)))/(f2+Pz));
	//��g1,g2,g3�����ľ���ֵ �Ӷ���theta1 
	theta_x.g1 = theta_x.f1*cos(*a2)-theta_x.f2*sin(*a2);
	theta_x.g2 = -theta_x.f3;
	theta_x.g3 = theta_x.f1*sin(*a2)+theta_x.f2*cos(*a2);
//	printf("g1,g2,g3��ֵ��%f,%f,%f\n",g1,g2,g3);
	if((pow(theta_x.g2,2)+pow(theta_x.g1,2)-pow(Py,2))>0)
	*a1=2*atan((theta_x.g1+sqrt(pow(theta_x.g2,2)+pow(theta_x.g1,2)-pow(Py,2)))/(theta_x.g2+Py));
	
//	if((pow(g2,2)+pow(g1,2)-pow(Py,2))>0)
//	*b1=2*atan((g1-sqrt(pow(g2,2)+pow(g1,2)-pow(Py,2)))/(g2+Py));
	//����ת�Ƕ� 
//	*a3 = *a3*180/PI; 
//	*a2 = *a2*180/PI;
//	*a1 = *a1*180/PI;
	
} 

//���theta4�ĺ��� 
struct{
	float _0_1_R[3][3];
	float _1_2_R[3][3];
	float _2_3_R[3][3];
	float _3_4_R[3][3];
	float mid[3][3];
	float _0_3_R[3][3];
	float Ni_0_3_R[3][3];
	float B_0_3_R[3][3];
	float th4;
	double data;
}do_tt4_R;
float do_tt4(float * th1,float * th2,float * th3,float T[3][3]) 
{
	char temp[50];
	sprintf(temp,"do_tt4 Start\r\n");	
	HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 		
//	float _0_1_R[3][3];float _1_2_R[3][3];float _2_3_R[3][3];float _3_4_R[3][3];float mid[3][3];float _0_3_R[3][3];
//	float Ni_0_3_R[3][3];double data=0;float B_0_3_R[3][3];//����� �����ֵ ������� 
	do_tt4_R.data=0;
	//extern float theta1,theta2,theta3;
	sprintf(temp,"to_theta4 start \ncos(theta1)=,cos(theta2)=,cos(theta3)=\r\n");	
	HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 		
	//ͨ��theta1,theta2,theta3��� _0_1_R�� _1_2_R�� _2_3_R
	// _0_1_R��ֵ
	do_tt4_R._0_1_R[0][0]=cos(*th1);do_tt4_R._0_1_R[0][1]=-sin(*th1);do_tt4_R._0_1_R[0][2]=0;
	do_tt4_R._0_1_R[1][0]=sin(*th1);do_tt4_R._0_1_R[1][1]=cos(*th1);do_tt4_R._0_1_R[1][2]=0;
	do_tt4_R._0_1_R[2][0]=0;do_tt4_R._0_1_R[2][1]=0;do_tt4_R._0_1_R[2][2]=1;
	sprintf(temp,"theta 1,1\r\n");	
	HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 		
	//_1_2_R��ֵ
	do_tt4_R._1_2_R[0][0]=cos(*th2);do_tt4_R._1_2_R[0][1]=-sin(*th2);do_tt4_R._1_2_R[0][2]=0;
	do_tt4_R._1_2_R[1][0]=0;do_tt4_R._1_2_R[1][1]=0;do_tt4_R._1_2_R[1][2]=-1;
	do_tt4_R._1_2_R[2][0]=sin(*th2);do_tt4_R._1_2_R[2][1]=cos(*th2);do_tt4_R._1_2_R[2][2]=0;
	sprintf(temp,"theta 1.2\r\n");	
	HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 		
	//_2_3_R��ֵ
	do_tt4_R._2_3_R[0][0]=cos(*th3);do_tt4_R._2_3_R[0][1]=-sin(*th3);do_tt4_R._2_3_R[0][2]=0;
	do_tt4_R._2_3_R[1][0]=sin(*th3);do_tt4_R._2_3_R[1][1]=cos(*th3);do_tt4_R._2_3_R[1][2]=0;
	do_tt4_R._2_3_R[2][0]=0;do_tt4_R._2_3_R[2][1]=0;do_tt4_R._2_3_R[2][2]=1;
		sprintf(temp,"theta 1.3\r\n");	
		HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 		
	// _0_1_R��ֵ�� _1_2_R��ֵ��_2_3_R��ֵ��˵� _0_3_R
		sprintf(temp,"theta 1\r\n");	
		HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 		
	Multy_3(do_tt4_R._0_1_R,do_tt4_R._1_2_R,do_tt4_R.mid);
		sprintf(temp,"theta 2\r\n");	
		HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 		
	Multy_3(do_tt4_R.mid,do_tt4_R._2_3_R,do_tt4_R._0_3_R);
		sprintf(temp,"theta 3\r\n");	
		HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 		
    //3�� _0_3_R�������
	do_tt4_R.data = (((do_tt4_R._0_3_R[0][0]*do_tt4_R._0_3_R[1][1]*do_tt4_R._0_3_R[2][2])+(do_tt4_R._0_3_R[0][1]*do_tt4_R._0_3_R[1][2]*do_tt4_R._0_3_R[2][0])+(do_tt4_R._0_3_R[0][2]*do_tt4_R._0_3_R[1][0]*do_tt4_R._0_3_R[2][1]))-
			((do_tt4_R._0_3_R[0][2]*do_tt4_R._0_3_R[1][1]*do_tt4_R._0_3_R[2][0])+(do_tt4_R._0_3_R[0][1]*do_tt4_R._0_3_R[1][0]*do_tt4_R._0_3_R[2][2])+(do_tt4_R._0_3_R[2][1]*do_tt4_R._0_3_R[1][2]*do_tt4_R._0_3_R[0][0])));
			sprintf(temp,"theta 4   data=%f:\r\n",do_tt4_R.data);	
		HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 		
	if(do_tt4_R.data != 0.0)
	{
		do_tt4_R.B_0_3_R[0][0] = ((do_tt4_R._0_3_R[1][1]*do_tt4_R._0_3_R[2][2])-(do_tt4_R._0_3_R[1][2]*do_tt4_R._0_3_R[2][1]));//
		do_tt4_R.B_0_3_R[0][1] = -((do_tt4_R._0_3_R[0][1]*do_tt4_R._0_3_R[2][2])-(do_tt4_R._0_3_R[0][2]*do_tt4_R._0_3_R[2][1]));//
		do_tt4_R.B_0_3_R[0][2] = ((do_tt4_R._0_3_R[0][1]*do_tt4_R._0_3_R[1][2])-(do_tt4_R._0_3_R[0][2]*do_tt4_R._0_3_R[1][1]));//
		
		do_tt4_R.B_0_3_R[1][0] = -((do_tt4_R._0_3_R[1][0]*do_tt4_R._0_3_R[2][2])-(do_tt4_R._0_3_R[1][2]*do_tt4_R._0_3_R[2][0]));//
		do_tt4_R.B_0_3_R[1][1] = ((do_tt4_R._0_3_R[0][0]*do_tt4_R._0_3_R[2][2])-(do_tt4_R._0_3_R[0][2]*do_tt4_R._0_3_R[2][0]));//
		do_tt4_R.B_0_3_R[1][2] = -((do_tt4_R._0_3_R[0][0]*do_tt4_R._0_3_R[1][2])-(do_tt4_R._0_3_R[0][2]*do_tt4_R._0_3_R[1][0]));//
		
		do_tt4_R.B_0_3_R[2][0] = ((do_tt4_R._0_3_R[1][0]*do_tt4_R._0_3_R[2][1])-(do_tt4_R._0_3_R[1][1]*do_tt4_R._0_3_R[2][0]));//
		do_tt4_R.B_0_3_R[2][1] = -((do_tt4_R._0_3_R[0][0]*do_tt4_R._0_3_R[2][1])-(do_tt4_R._0_3_R[0][1]*do_tt4_R._0_3_R[2][0]));//
		do_tt4_R.B_0_3_R[2][2] = ((do_tt4_R._0_3_R[0][0]*do_tt4_R._0_3_R[1][1])-(do_tt4_R._0_3_R[0][1]*do_tt4_R._0_3_R[1][0]));	//
		
		for( n=0;n<3;n++)
		{
			for( m=0;m<3;m++)
			{
				do_tt4_R.Ni_0_3_R[n][m] = -(do_tt4_R.B_0_3_R[n][m]/fabs(do_tt4_R.data));
			}
		}
	}
		sprintf(temp,"theta 5\r\n");	
		HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 		
	//���theta4
	Multy_3(do_tt4_R.Ni_0_3_R,T,do_tt4_R._3_4_R);
		sprintf(temp,"theta 6\r\n");	
		HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 		
    do_tt4_R.th4 = acos(do_tt4_R._3_4_R[0][0]);
		sprintf(temp,"theta 7\r\n");	
		HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 	
	return do_tt4_R.th4;
}

//�жϽǶ� ��ֹ��е�۹���
void theta_tran(float * a1,float *a2,float *a3,float *a4)
{
		*a3 = *a3*180/PI; 
		*a2 = *a2*180/PI;
		*a1 = *a1*180/PI;
		*a4 = *a4*180/PI;
	if(*a1<135 & *a1>-135) *a1 = *a1 +135;
	else *a1 = 135;
	if(*a2>180 & *a2<0) *a2 = 90;
	if(*a3<135 & *a3>-135) *a3 = *a3 +135;
	else *a3 = 135;
	if(*a4<135 & *a4>-135) *a4 = *a4 +135;
	else *a4 = 135;
}
struct jz{
	float _0_1_R[3][3];
	float _1_2_R[3][3];
	float _2_3_R[3][3];
	float _3_4_R[3][3];
	float mid1[3][3];
	float _0_3_R[3][3];
	float Ni_0_3_R[3][3];
	float B_0_3_R[3][3];//����� �����ֵ ������� 
	float _0_4_T[4][4];
	float mid[4][4];
	float _0_4_R[3][3];
	float _0_4_ORG[3][1];
	double data;
}R_jz;
int n,m;
void Mat(float Px,float Py,float Pz)
{
	//��ʼ������ 
	extern int axie[]; //ȫ�ֽǶ�
	float Ni_w_0_T[4][4]={1,0,0,0,
						  0,1,0,0,
						  0,0,1,-79.05,
						  0,0,0,1};
	float Ni_4_m_T[4][4]={1,0,0,-113.2,
						  0,0,1,-14.09,
						  0,1,0,0,
						  0,0,0,1};
	float w_m_T[4][4]={0};
//	float _0_4_T[4][4];
//	float mid[4][4];
//	float _0_4_R[3][3];
//	float _0_4_ORG[3][1];
	//�Ƕ�theta1,theta2,theta3,theta4
	extern float theta1,theta2,theta3,theta4;
	//float theta1_1,theta2_1,theta3_1,theta4_1;
	
//	float f1,f2,f3;
//	float g1,g2,g3;
//	float Px1;float Py1;float Pz1;

	char temp[30];
	//��main�����л�ȡĿ������������Px,Py,Pz
	w_m_T[0][0]=1;w_m_T[1][1]=1;w_m_T[2][2]=1;w_m_T[3][3]=1;
	w_m_T[0][3]=Px;w_m_T[1][3]=Py;w_m_T[2][3]=Pz;
   //��� _0_4_T���� 
	//��һ����� 
		Multy(Ni_w_0_T,w_m_T,R_jz.mid);
		sprintf(temp,"Mat 1\r\n");	
		HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50);
	
	//�ڶ������ 
		Multy(R_jz.mid,Ni_4_m_T,R_jz._0_4_T);
		sprintf(temp,"Mat 2\r\n");	
		HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50);
		
  //��ȡ _0_4_T �ǶȾ��� 
		_3_3_tran(R_jz._0_4_T,R_jz._0_4_R);
		sprintf(temp,"Mat 3\r\n");	
		HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 
		
	//ȡ _0_4_T �������
    ORG_tran(R_jz._0_4_T,R_jz._0_4_ORG);
		sprintf(temp,"Mat 4\r\n");	
		HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 
		
		theta(R_jz._0_4_ORG,&theta1,&theta2,&theta3);
/*****************************************/
/*
	sprintf(temp,"px1\r\n");	
	HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 
	Px1=_0_4_ORG[0][0]; Py1=_0_4_ORG[1][0]; Pz1=_0_4_ORG[2][0];
	//��a3��ֵ 
	sprintf(temp,"px2\r\n");	
	HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50);
	
	if((pow(Py1,2)+pow(Px1,2)-3130.4025)>0)
	theta3=2*atan((-Py1+sqrt(pow(Py1,2)+pow(Px1,2)-3130.4025))/(Px1+55.95)); //���ػ���
	//��f1,f2,f3�����ľ���ֵ �Ӷ���theta2 
	sprintf(temp,"px3\r\n");	
	HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 
	f1 = Px1*cos(theta3)-Py1*sin(theta3)+111.9;                      //cos��x��xΪ���� 
	f2 = Px1*sin(theta3)+Py1*cos(theta3);
	f3 = Pz1;
	sprintf(temp,"px4\r\n");	
	HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 
	if((pow(f2,2)+pow(f1,2)-pow(Pz1,2))>0) 
	theta2=2*atan((f1+sqrt(pow(f2,2)+pow(f1,2)-pow(Pz1,2)))/(f2+Pz1));
	//��g1,g2,g3�����ľ���ֵ �Ӷ���theta1 
	sprintf(temp,"px5\r\n");	
	HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 
	g1 = f1*cos(theta2)-f2*sin(theta2);
	g2 = -f3;
	g3 = f1*sin(theta2)+f2*cos(theta2);
//	printf("g1,g2,g3��ֵ��%f,%f,%f\n",g1,g2,g3);
	sprintf(temp,"px6\r\n");	
	HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 
	if((pow(g2,2)+pow(g1,2)-pow(Py1,2))>0)
	theta1=2*atan((g1+sqrt(pow(g2,2)+pow(g1,2)-pow(Py,2)))/(g2+Py1));
*/
/*****************************************/
		sprintf(temp,"Mat 5\r\n");	
		HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 
		sprintf(temp,"theta1=%f,theta2=%f,theta3=%f,theta4=%f\r\n",theta1,theta2,theta3,theta4);
		HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 	
		
		//theta1_1=theta1;theta2_1=theta2;theta3_1=theta3;
		sprintf(temp,"Mat theta4\r\n");	
		HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 
    //���theta4 //***********************
//    theta4 = do_tt4(&theta1,&theta2,&theta3,_0_4_R);

/************************************************/
	sprintf(temp,"do_tt4 Start\r\n");	
	HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50);
  R_jz.data=0;
//	float _0_1_R[3][3];float _1_2_R[3][3];float _2_3_R[3][3];float _3_4_R[3][3];float mid1[3][3];float _0_3_R[3][3];
//	float Ni_0_3_R[3][3];double data=0;float B_0_3_R[3][3];//����� �����ֵ ������� 
	//float th4;
	//extern float theta1,theta2,theta3;
	sprintf(temp,"to_theta4 start \ncos(theta1)=,cos(theta2)=,cos(theta3)=\r\n");	
	HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 		
	//ͨ��theta1,theta2,theta3��� _0_1_R�� _1_2_R�� _2_3_R
	// _0_1_R��ֵ
	R_jz._0_1_R[0][0]=cos(theta1);R_jz._0_1_R[0][1]=-sin(theta1);R_jz._0_1_R[0][2]=0;
	R_jz._0_1_R[1][0]=sin(theta1);R_jz._0_1_R[1][1]=cos(theta1);R_jz._0_1_R[1][2]=0;
	R_jz._0_1_R[2][0]=0;R_jz._0_1_R[2][1]=0;R_jz._0_1_R[2][2]=1;
	sprintf(temp,"theta 1,1\r\n");	
	HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 		
	//_1_2_R��ֵ
	R_jz._1_2_R[0][0]=cos(theta2);R_jz._1_2_R[0][1]=-sin(theta2);R_jz._1_2_R[0][2]=0;
	R_jz._1_2_R[1][0]=0;R_jz._1_2_R[1][1]=0;R_jz._1_2_R[1][2]=-1;
	R_jz._1_2_R[2][0]=sin(theta2);R_jz._1_2_R[2][1]=cos(theta2);R_jz._1_2_R[2][2]=0;
	sprintf(temp,"theta 1.2\r\n");	
	HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 		
	//_2_3_R��ֵ
	R_jz._2_3_R[0][0]=cos(theta3);R_jz._2_3_R[0][1]=-sin(theta3);R_jz._2_3_R[0][2]=0;
	R_jz._2_3_R[1][0]=sin(theta3);R_jz._2_3_R[1][1]=cos(theta3);R_jz._2_3_R[1][2]=0;
	R_jz._2_3_R[2][0]=0;R_jz._2_3_R[2][1]=0;R_jz._2_3_R[2][2]=1;
		sprintf(temp,"theta 1.3\r\n");	
		HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 		
	// _0_1_R��ֵ�� _1_2_R��ֵ��_2_3_R��ֵ��˵� _0_3_R
		sprintf(temp,"theta 1\r\n");	
		HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 		
	Multy_3(R_jz._0_1_R,R_jz._1_2_R,R_jz.mid1);
		sprintf(temp,"theta 2\r\n");	
		HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 		
	Multy_3(R_jz.mid1,R_jz._2_3_R,R_jz._0_3_R);
		sprintf(temp,"theta 3\r\n");	
		HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 		
    //3�� _0_3_R�������
	R_jz.data = (((R_jz._0_3_R[0][0]*R_jz._0_3_R[1][1]*R_jz._0_3_R[2][2])+(R_jz._0_3_R[0][1]*R_jz._0_3_R[1][2]*R_jz._0_3_R[2][0])+(R_jz._0_3_R[0][2]*R_jz._0_3_R[1][0]*R_jz._0_3_R[2][1]))-
			((R_jz._0_3_R[0][2]*R_jz._0_3_R[1][1]*R_jz._0_3_R[2][0])+(R_jz._0_3_R[0][1]*R_jz._0_3_R[1][0]*R_jz._0_3_R[2][2])+(R_jz._0_3_R[2][1]*R_jz._0_3_R[1][2]*R_jz._0_3_R[0][0])));
			sprintf(temp,"theta 4   data=%f:\r\n",R_jz.data);	
		HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 		
	if(R_jz.data != 0.0)
	{
		R_jz.B_0_3_R[0][0] = ((R_jz._0_3_R[1][1]*R_jz._0_3_R[2][2])-(R_jz._0_3_R[1][2]*R_jz._0_3_R[2][1]));//
		R_jz.B_0_3_R[0][1] = -((R_jz._0_3_R[0][1]*R_jz._0_3_R[2][2])-(R_jz._0_3_R[0][2]*R_jz._0_3_R[2][1]));//
		R_jz.B_0_3_R[0][2] = ((R_jz._0_3_R[0][1]*R_jz._0_3_R[1][2])-(R_jz._0_3_R[0][2]*R_jz._0_3_R[1][1]));//
		
		R_jz.B_0_3_R[1][0] = -((R_jz._0_3_R[1][0]*R_jz._0_3_R[2][2])-(R_jz._0_3_R[1][2]*R_jz._0_3_R[2][0]));//
		R_jz.B_0_3_R[1][1] = ((R_jz._0_3_R[0][0]*R_jz._0_3_R[2][2])-(R_jz._0_3_R[0][2]*R_jz._0_3_R[2][0]));//
		R_jz.B_0_3_R[1][2] = -((R_jz._0_3_R[0][0]*R_jz._0_3_R[1][2])-(R_jz._0_3_R[0][2]*R_jz._0_3_R[1][0]));//
		
		R_jz.B_0_3_R[2][0] = ((R_jz._0_3_R[1][0]*R_jz._0_3_R[2][1])-(R_jz._0_3_R[1][1]*R_jz._0_3_R[2][0]));//
		R_jz.B_0_3_R[2][1] = -((R_jz._0_3_R[0][0]*R_jz._0_3_R[2][1])-(R_jz._0_3_R[0][1]*R_jz._0_3_R[2][0]));//
		R_jz.B_0_3_R[2][2] = ((R_jz._0_3_R[0][0]*R_jz._0_3_R[1][1])-(R_jz._0_3_R[0][1]*R_jz._0_3_R[1][0]));	//
		
		for(n=0;n<3;n++)
		{
			for(m=0;m<3;m++)
			{
				R_jz.Ni_0_3_R[n][m] = -(R_jz.B_0_3_R[n][m]/fabs(R_jz.data));
			}
		}
	}
		sprintf(temp,"theta 5\r\n");	
		HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 		
	//���theta4
		Multy_3(R_jz.Ni_0_3_R,R_jz._0_4_R,R_jz._3_4_R);
		sprintf(temp,"theta 6\r\n");	
		HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 		
    theta4 = acos(R_jz._3_4_R[0][0]);
		sprintf(temp,"theta 7\r\n");	
		HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 	


/********************************************/

//		sprintf(temp,"Mat 6\r\n");	
//		HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 
//theta4_1=do_tt4(_0_4_R,theta1_1,theta2_1,theta3_1); 
		sprintf(temp,"Mat 7\r\n");	
		HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 		//�Ƕ�����
		theta_tran(&theta1,&theta2,&theta3,&theta4);
		
		sprintf(temp,"Mat 8\r\n");	
		HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 
		axie[0]=(int)theta1;axie[1]=(int)theta2;axie[2]=(int)theta3;axie[3]=(int)theta4;
		
		sprintf(temp,"theta1=%f,theta2=%f,theta3=%f,theta4=%f\r\n",theta1,theta2,theta3,theta4);	
		HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 		
}





