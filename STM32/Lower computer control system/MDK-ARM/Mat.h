#ifndef _MAT_H_
#define _MAT_H_

#include "main.h"
#include "stdio.h"
#include "math.h"
#include "string.h"
#include "usart.h"
void Multy(float A[4][4],float  B[4][4],float result[4][4] );//4*4
void Multy_3(float A[3][3],float  B[3][3],float result[3][3] );//����3*3
void _3_3_tran(float org[4][4],float _new[3][3]);//ȡ���Ͻ�3*3 �ǶȾ��� 
void ORG_tran(float org[4][4],float _new[3][1]);//��ȡ�ұ߾������ORG
void theta(float ORG[3][1],float * a1,float * a2,float * a3);//���theta����
//float do_tt4(float T[3][3],float th1,float th2,float th3); 
void Mat(float Px,float Py,float Pz);
void theta_tran(float * a1,float *a2,float *a3,float *a4);
void mat(float Px,float Py,float Pz);

#endif
