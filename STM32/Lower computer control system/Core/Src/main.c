/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "dianji.h"
#include "duoji.h"
#include "intterupt.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "lineread.h"


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
extern unsigned pointer;
extern char rxdata[30];
extern uint8_t data;
void rx_proc(void);
void print(int n);
int axie[5];
the t;
int flag = 0; //��ʶ��
int distance = 0;
int uart3_flag=0;
int egg_dif=0;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	char temp[30];
	int i1=01;int i2=1;int i3=1;int i4=1;int i5=1;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_TIM3_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM4_Init();
  MX_TIM8_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	//��Դ��ʼ��
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_2); //���PWM��ʼ�� ABCD
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);
	HAL_UART_Receive_IT(&huart1,&data,1);
	HAL_UART_Receive_IT(&huart3,&data,1);
	HAL_Delay(1);
	
	printf("UART1_Init SECCUSS!\n");
	printf("UART3_Init SECCUSS!\n");
	sprintf(temp,"arm init all right\n");
	HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 
	//�Ƕȳ�ʼ��
	axie[0]=135;axie[1]=90;axie[2]=0;axie[3]=90;axie[4]=90;
	printf("angle_int:135:090:000:090:090\n");
	arm_init();	
	t.x = 236.26;t.y = 0;t.z = 106.76;
	t.n_x = 236.26;t.n_y = 0;t.n_z = 106.76; //��е��ĩ�˳�ʼλ�� 
	t.n1 = t.n2 =t.n3 =t.n4 = 0;  //��е���������ʼ�Ƕ� 	
//	while(1)
//	{

//	}
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

		switch(flag)
		{
			//������ʼ��λ
			case 0: {
			printf("flag=1\n");
			HAL_Delay(1000);	
			};break;
			
			//flag = 1  ���͸���ݮ�ɿ���YOLO ��е�۴��ڼ��״̬
			case 1:{
			axie[0]=135;axie[1]=90;axie[2]=0;axie[3]=90;axie[4]=90;
			arm_control(axie[0],axie[1],axie[2],axie[3],axie[4]);
			printf("flag=1\n");
			HAL_Delay(1000);	
			};break;
			
			//flag = 2  С������ѭ��ģʽ(flag=2����ݮ�ɽ���)
			case 2:{
			wait_mode();
			duoji_pwmstop(); //ֹͣ���pwm��� ��ʱ��ֹ����
			_run(3000); //ѭ������
			while(i1){printf("Trace mode\n");i1-=1;}
			};break;
			
			//flag = 4  ���ղ�ֵ���� ��תΪѰ����ģʽ (flag=4����ݮ�ɽ���)
			case 4:{
			Stop();
			find_mid_mode(egg_dif);
			while(i2){printf("Centering mode mode\n");i2-=1;}
			duoji_pwmstart();//�������pwm��� ��ʱ��ֹ����
			};break;
			
			//flag = 5  ����Z���ֵ���� ֹͣѰ����ģʽ ���ƻ�е��z���˶�(flag=5����ݮ�ɽ���)
			case 5:{
			move_z(egg_dif,1);
			HAL_Delay(10);
			egg_dif = 0;
			while(i3){printf("Z-axis mode\n");i3-=1;}
			};break;
			
			//flag = 6  ���������� ���ƻ�е��x�᷽���˶� ���жϾ���(flag=6����ݮ�ɽ���)
			//������< ? ʱ��ֹͣ��е���˶���ʵ�м���˶�������ɼ��ж���  ʹflag= 8 
			case 6:{
			if(uart3_flag==0){uart3_flag = 1;HAL_UART_Receive_IT(&huart3,&data,1);	}
			while(i4){printf("Laser mode\n");i4-=1;}
			HAL_Delay(20);
			move_x_mode();
			print(8); //**********
			
			};break;
			
			//flag = 8  ����е�����̧�ߴ�����ת��е�۵���ǰ����ת������ʹ������б��
			//ʵ���ſ�צǯ����  ����̧�ߴ���  ʹflag = 1 �ظ�ѭ��
			case 8:{
			while(i5){printf("Grab A Place mode\n");i5-=1;}
			uart3_flag = 0;
			HAL_Delay(20);
			distance = 0;
			glab_place_mode();
			print(1);
			
			};break;
			//Ԥ���ڣ���ʱ���ڻָ���ʼ��
			case 9:{
			axie[0]=135;axie[1]=90;axie[2]=0;axie[3]=90;axie[4]=90;
			arm_init();	
			};break;			
		}
		
		rx_proc();
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

struct{
char axis1[10];
	char axis2[10];
	char axis3[10];
	char axis4[10];
	char axis5[10];
	char px[10];
	char py[10];
	char pz[10];
	char data[3];	//�ƶ�����
	int da;
	char wh[2];   //�������
	char fl[1];  //flag�ַ�����
	char dis[200];
	char e_d[20];
}rx_axis;
//�����յ����ַ�תΪ16������ �������ࣩ
void str_hex(char str[])
{
	int x;
    for(x = 0; x < 7; x++) {
        sprintf(rx_axis.dis + x*2, "%02X", str[x]);
    }
}
void rx_proc(void)
{
		if(pointer!=0)
		{
			int temp=pointer;
			HAL_Delay(1);
			if(temp==pointer)
			{
	char temp[30];
	extern int axie[];
	if(pointer>0)
	{
		if(pointer==19) //0,0,0,0,0  180,180,180,180,180
		{
			
			sscanf(rxdata,"%3s:%3s:%3s:%3s:%3s",rx_axis.axis1,rx_axis.axis2,rx_axis.axis3,rx_axis.axis4,rx_axis.axis5);
			sprintf(temp,"all right\r\n");		
			HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 
			HAL_UART_Transmit(&huart1,(uint8_t *)rxdata,strlen(rxdata),50); 
			axie[0] = atoi(rx_axis.axis1);axie[1] = atoi(rx_axis.axis2);axie[2] = atoi(rx_axis.axis3);axie[3] = atoi(rx_axis.axis4);axie[4] = atoi(rx_axis.axis5);
			arm_control(axie[0],axie[1],axie[2],axie[3],axie[4]);
		}
//		pointer = 0;memset(rxdata,0,30);
//		else if(pointer == 11) //�����������ݣ���е���˶�����Ӧ����
//		{
//			sscanf(rxdata,"%3s:%3s:%3s",rx_axis.px,rx_axis.py,rx_axis.pz);
//			sprintf(temp,"px py pz all right\r\n");	
//			HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 
//			HAL_UART_Transmit(&huart1,(uint8_t *)rxdata,strlen(rxdata),50); 
//			t.x = atof(rx_axis.px);t.y = atof(rx_axis.py);t.z = atof(rx_axis.pz);
//			pro_ni();
//			//pro_jd();
//			//axie[0]=t.theta1; theta1�������ı�
//			axie[1]=t.theta2;axie[2]=t.theta3;axie[3]=t.theta4;
//			arm_control(axie[0],axie[1],axie[2],axie[3],axie[4]);
//			sprintf(temp,"px py pz start finshed\r\n");	
//			HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 			
//		}
		else if(pointer == 5) //������룬ĩ��ƽ��
		{
			sscanf(rxdata,"%1s:%3s",rx_axis.wh,rx_axis.data);
			sprintf(temp,"wh = %1s  data = %3s\n",rx_axis.wh,rx_axis.data);	
			HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 
			rx_axis.da = atof(rx_axis.data);
			switch (rx_axis.wh[0]){
				case 'x':
				move_x(rx_axis.da,1);	
				sprintf(temp,"x:%d\n",rx_axis.da);	
				HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 				
				break;
				case 'y':
				move_y(rx_axis.da,1);	
				sprintf(temp,"y:%d\n",rx_axis.da);	
				HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50);
				break;
				case 'z':
				move_z(rx_axis.da,1);	
				sprintf(temp,"z:%d\n",rx_axis.da);	
				HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50);
				break;
				case 'a':
				move_axie0(rx_axis.da,1);
				sprintf(temp,"a:%d\n",rx_axis.da);	
				HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50);
				break;
				case 'd':
				move_axie0(rx_axis.da,1);
				sprintf(temp,"d:%d\n",rx_axis.da);	
				HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50);
				break;	
				
			}
			sprintf(temp,"now_co %.0f:%.0f:%.0f\n",t.n_x,t.n_y,t.n_z);	
			HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50);						
			memset(rx_axis.wh,0,2);memset(rx_axis.data,0,3);rx_axis.da=0;
		}
		else if(pointer == 6)
		{
			sscanf(rxdata,"flag=%1s",rx_axis.fl);
			flag = atoi(rx_axis.fl);
			//printf("flag=%d",flag);
		}
		else if(pointer == 7)
		{
			char d[4];
			int x;
			str_hex(rxdata); //�ַ�ת16����
			//printf("%14s\n",rx_axis.dis);
			for(x=7;x<=10;x++)
			{
				d[x-7]=rx_axis.dis[x-1];
			} //��ȡ���벿�ֵ�16������
			distance = strtol(d,NULL,16); //��16����תΪ10���ƣ�ת��Ϊ10���Ƶľ���
			printf("distance = %d mm\n",distance);	
		}
		//egg_dif=99 ��ȡ��ݮ�ɷ��͵��м��ֵ�����浽egg_dif��
		else if(pointer == 10)
		{
			sscanf(rxdata,"egg_dif=%2s",rx_axis.e_d);
			egg_dif = atoi(rx_axis.e_d);
			//printf("egg_dif = %2d\n",egg_dif);			
		}
		else
		{
//			printf("len = %d\n",pointer);
//			sprintf(temp,"Data Error:\r\n");		
//			HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 
//			HAL_UART_Transmit(&huart1,(uint8_t *)rxdata,strlen(rxdata),50); 			
		}
//		sprintf(temp,"now angle:%d,%d,%d,%d,%d\r\n",axie[0],axie[1],axie[2],axie[3],axie[4]);		
//		HAL_UART_Transmit(&huart1,(uint8_t *)temp,strlen(temp),50); 
		pointer = 0;memset(rxdata,0,30);
	}
			}
				
		}
//	char axis1[10],axis2[10],axis3[10],axis4[10],axis5[10];
//	char px[10],py[10],pz[10];
//	float Px,Py,Pz;
}
//���Ͳ���flagλ
void print(int n)
{
	printf("flag=%d",n);
	flag = n;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
