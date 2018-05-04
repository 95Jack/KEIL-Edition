#include "led.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK mini�SSTM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//��ʼ��PB5��PE5Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
LED_STATUS led_status;

void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PA,PD�˿�ʱ��
 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 |GPIO_Pin_10; //LED1-->PD.7/8/10 �˿�����, �������	
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);	 
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				 //LED0-->PA.2 �˿�����  				
 GPIO_Init(GPIOA, &GPIO_InitStructure);	
    Led1_Set(LED_OFF);
    Led2_Set(LED_OFF);
    Led3_Set(LED_OFF);
    Led4_Set(LED_OFF);
}
 

/*
************************************************************
*	�������ƣ�	Led1_Set
*
*	�������ܣ�	LED1����
*
*	��ڲ�����	status��LED_ON-����	LED_OFF-�ص�
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
void Led1_Set(LED_ENUM status)
{

	GPIO_WriteBit(GPIOC, GPIO_Pin_7, status != LED_ON ? Bit_SET : Bit_RESET);	//status���������LED_ON�򷵻�Bit_SET�����򷵻�Bit_RESET����ͬ
	led_status.Led1Sta = status;

}

/*
************************************************************
*	�������ƣ�	Led2_Set
*
*	�������ܣ�	LED2����
*
*	��ڲ�����	status��LED_ON-����	LED_OFF-�ص�
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
void Led2_Set(LED_ENUM status)
{

	GPIO_WriteBit(GPIOC, GPIO_Pin_8, status != LED_ON ? Bit_SET : Bit_RESET);
	led_status.Led2Sta = status;

}

/*
************************************************************
*	�������ƣ�	Led3_Set
*
*	�������ܣ�	LED3����
*
*	��ڲ�����	status��LED_ON-����	LED_OFF-�ص�
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
void Led3_Set(LED_ENUM status)
{

	GPIO_WriteBit(GPIOA, GPIO_Pin_12, status != LED_ON ? Bit_SET : Bit_RESET);
	led_status.Led3Sta = status;

}

/*
************************************************************
*	�������ƣ�	Led4_Set
*
*	�������ܣ�	LED4����
*
*	��ڲ�����	status��LED_ON-����	LED_OFF-�ص�
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
void Led4_Set(LED_ENUM status)
{

	GPIO_WriteBit(GPIOC, GPIO_Pin_10, status != LED_ON ? Bit_SET : Bit_RESET);
	led_status.Led4Sta = status;
}
