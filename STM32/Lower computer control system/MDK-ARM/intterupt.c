#include "intterupt.h"
#include "usart.h"
#include "stdio.h"

char rxdata[30];
uint8_t data;
extern int uart3_flag;
unsigned int pointer=0;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	rxdata[pointer++]=data;
	if(uart3_flag==1)
	{
		HAL_UART_Receive_IT(&huart1,&data,1);
		HAL_UART_Receive_IT(&huart3,&data,1);	
	}
	else HAL_UART_Receive_IT(&huart1,&data,1);

}
/* USER CODE BEGIN 4 */
extern int flag;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(flag<10) 
	{
		flag++;
	}
	else flag = 0;
	printf("flag=%d\n",flag);
 

}
/* USER CODE END 4 */



