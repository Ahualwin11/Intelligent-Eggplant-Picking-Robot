#include "bsp_i2c_gpio.h"

#include <string.h>

#define I2C_ADDR                    0x2D   

#define macI2C_WR	0		/* д����bit */
#define macI2C_RD	1		/* ������bit */


/* ����I2C�������ӵ�GPIO�˿�, �û�ֻ��Ҫ�޸�����4�д��뼴������ı�SCL��SDA������ */
#define macGPIO_PORT_I2C	GPIOB			/* GPIO�˿� */
#define macRCC_I2C_PORT 	RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define macI2C_SCL_PIN		GPIO_Pin_6			/* ���ӵ�SCLʱ���ߵ�GPIO */
#define macI2C_SDA_PIN		GPIO_Pin_7			/* ���ӵ�SDA�����ߵ�GPIO */

#define macI2C_SCL_1() HAL_GPIO_WritePin(macGPIO_PORT_I2C,GPIO_PIN_6,GPIO_PIN_SET);
#define macI2C_SCL_0() HAL_GPIO_WritePin(macGPIO_PORT_I2C,GPIO_PIN_6,GPIO_PIN_RESET);
#define macI2C_SDA_1() HAL_GPIO_WritePin(macGPIO_PORT_I2C,GPIO_PIN_7,GPIO_PIN_SET);
#define macI2C_SDA_0() HAL_GPIO_WritePin(macGPIO_PORT_I2C,GPIO_PIN_7,GPIO_PIN_RESET);
#define SDA_READ() HAL_GPIO_ReadPin(macGPIO_PORT_I2C,GPIO_Pin_7);
#define SCL_READ() HAL_GPIO_ReadPin(macGPIO_PORT_I2C,GPIO_Pin_6);
uint8_t ack;                 /*Ӧ���־λ*/
/*
*********************************************************************************************************
*	�� �� ��: i2c_Delay
*	����˵��: I2C����λ�ӳ٣����400KHz
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/

static void i2c_Delay(void)
{
	uint8_t i;

	/*��
	 	�����ʱ����ͨ��������AX-Pro�߼������ǲ��Եõ��ġ�
		CPU��Ƶ72MHzʱ�����ڲ�Flash����, MDK���̲��Ż�
		ѭ������Ϊ10ʱ��SCLƵ�� = 205KHz 
		ѭ������Ϊ7ʱ��SCLƵ�� = 347KHz�� SCL�ߵ�ƽʱ��1.5us��SCL�͵�ƽʱ��2.87us 
	 	ѭ������Ϊ5ʱ��SCLƵ�� = 421KHz�� SCL�ߵ�ƽʱ��1.25us��SCL�͵�ƽʱ��2.375us 
        
    IAR���̱���Ч�ʸߣ���������Ϊ7
	*/
	for (i = 0; i < 50; i++);
}


void delay(int z)
{   
	  int i;
	  int j;
	  for(i = 0;i<z;i++)
		{
			for(j = 0;j<50;j++)
			{
					i2c_Delay();
				}
		}
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_Start
*	����˵��: CPU����I2C���������ź�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/

void Start_I2c(void)
{
	HAL_GPIO_WritePin(macGPIO_PORT_I2C,GPIO_PIN_7,GPIO_PIN_SET);
	HAL_GPIO_WritePin(macGPIO_PORT_I2C,GPIO_PIN_6,GPIO_PIN_SET);
//  macI2C_SDA_1();         /*������ʼ�����������ź�*/
//  macI2C_SCL_1();
  i2c_Delay();    
	HAL_GPIO_WritePin(macGPIO_PORT_I2C,GPIO_PIN_7,GPIO_PIN_RESET);
//  macI2C_SDA_0();
  i2c_Delay();  
	HAL_GPIO_WritePin(macGPIO_PORT_I2C,GPIO_PIN_6,GPIO_PIN_RESET);
  //macI2C_SCL_0();       /*ǯסI2C���ߣ�׼�����ͻ�������� */
  i2c_Delay();
	
}
/*
*********************************************************************************************************
*	�� �� ��: i2c_Stop
*	����˵��: CPU����I2C����ֹͣ�ź�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Stop_I2c(void)
{
	/* ��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C����ֹͣ�ź� */
	macI2C_SDA_0();
	macI2C_SCL_1();
	while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6) == 0){macI2C_SCL_1();}
	i2c_Delay();
	macI2C_SDA_1();
	while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_7) == 0){macI2C_SDA_1();}
	i2c_Delay();
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_SendByte
*	����˵��: CPU��I2C�����豸����8bit����
*	��    �Σ�_ucByte �� �ȴ����͵��ֽ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/

void  I2C_SendByte(unsigned char  c)
{
 unsigned char  i;
 
 for(i=0;i<8;i++)  /*Ҫ���͵����ݳ���Ϊ8λ*/
    {
     if((c<<i)&0x80) macI2C_SDA_1()   /*�жϷ���λ*/
       else  macI2C_SDA_0();                
     i2c_Delay();
     macI2C_SCL_1();               /*��ʱ����Ϊ�ߣ�֪ͨ��������ʼ��������λ*/
		 while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6) == 0){macI2C_SCL_1();}
      i2c_Delay();
			
     macI2C_SCL_0();
    }
    i2c_Delay();
    macI2C_SDA_1() ;                /*8λ��������ͷ������ߣ�׼������Ӧ��λ*/
    i2c_Delay();   
    macI2C_SCL_1();
		while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6) == 0){macI2C_SCL_1();}
    i2c_Delay();
    if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_7))ack=0;     
       else ack=1;        /*�ж��Ƿ���յ�Ӧ���ź�*/
    macI2C_SCL_0();
    i2c_Delay();

}

/*
*********************************************************************************************************
*	�� �� ��: i2c_ReadByte
*	����˵��: CPU��I2C�����豸��ȡ8bit����
*	��    �Σ���
*	�� �� ֵ: ����������
*********************************************************************************************************
*/



unsigned char I2C_RcvByte(void)
{
  unsigned char  retc=0,i=0; 
  macI2C_SDA_1();                     /*��������Ϊ���뷽ʽ*/

  for(i=0;i<8;i++)
      {

        i2c_Delay();           
        macI2C_SCL_0();                  /*��ʱ����Ϊ�ͣ�׼����������λ*/
				while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6) == 1){macI2C_SCL_0() ;}
        i2c_Delay();
        macI2C_SCL_1();                  /*��ʱ����Ϊ��ʹ��������������Ч*/
				while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6) == 0){macI2C_SCL_1();}
        i2c_Delay();
        retc=retc<<1;
        if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_7))retc=retc+1;  /*������λ,���յ�����λ����retc�� */
        i2c_Delay();
      } 
  macI2C_SCL_0();    
   i2c_Delay();
  return(retc);
}



/********************************************************************
                     Ӧ���Ӻ���
********************************************************************/
void Ack_I2c(uint8_t a)
{  
  if(a==0) macI2C_SDA_0()              /*�ڴ˷���Ӧ����Ӧ���ź� */
  else macI2C_SDA_1();				  /*0Ϊ����Ӧ��1Ϊ��Ӧ���ź� */
  i2c_Delay();      
  macI2C_SCL_1();
  i2c_Delay(); 
  macI2C_SCL_0();                    /*��ʱ���ߣ�סI2C�����Ա��������*/
  i2c_Delay();   
}



uint8_t IIC_Servo(unsigned char servonum,unsigned char angle)
{
  
    Start_I2c();          		//��������
	I2C_SendByte(I2C_ADDR);     //����������ַ
	if(ack==0)return(0);
   	I2C_SendByte(servonum);    //��������
	if(ack==0)return(0);
   	I2C_SendByte(angle);    //��������
	if(ack==0)return(0);

	Stop_I2c();               //��������
	HAL_Delay(100);
   	return(1);

}






