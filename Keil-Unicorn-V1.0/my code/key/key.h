#ifndef __KEY_H
#define __KEY_H	 
#include "stm32f10x.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK miniSTM32������
//������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 


//#define KEY0 PCin(5)   	
//#define KEY1 PAin(15)	 
//#define WK_UP  PAin(0)	 
 

//#define KEY0    GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)//��ȡ����0
//#define KEY1    GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11)//��ȡ����1
//#define KEY2    GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_12)//��ȡ����2
//#define WK_UP   GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)//��ȡȷ�Ͻ�
 

#define KEY0_PRES	1		//KEY0  
#define KEY1_PRES	2		//KEY1 
#define KEY2_PRES	3		//KEY1 
#define WKUP_PRES	4		//WK_UP 


#define KEY0			GPIO_Pin_13

#define KEY1			GPIO_Pin_11

#define KEY2			GPIO_Pin_12

#define KEY3			GPIO_Pin_2


/*******************************************
			���������뵯��
*******************************************/
#define KEYDOWN			1
#define KEYUP			0

#define KEY0DOWN		0

#define KEY1DOWN		3

#define KEY2DOWN		6

#define KEY3DOWN		9

#define KEYNONE			255



void KEY_Init(void);//IO��ʼ��

_Bool KeyScan(GPIO_TypeDef* GPIOX, unsigned int NUM);
unsigned char Keyboard(void);
/*********************************************************/
u8 KEY_Scan(u8 mode);  	//����ɨ�躯��	
void KEY_red(void);
#endif



