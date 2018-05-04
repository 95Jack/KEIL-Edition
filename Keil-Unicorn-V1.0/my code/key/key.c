#include "key.h"
#include "delay.h"
#include "OLED.h"
#include "stm32f10x.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK Mini STM32������
//�������� ��������		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/3/06
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									   
//////////////////////////////////////////////////////////////////////////////////	 	    
//������ʼ������ 
void KEY_Init(void)
{
        GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);	//��GPIOC��GPIOD��ʱ��
        //GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//�ر�jtag��ʹ��SWD��������SWDģʽ����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;//��ʼ��Pin11��12��13
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//���ص����Ƶ��
	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��GPIOD
} 
/*
************************************************************
*	�������ƣ�	KeyScan
*
*	�������ܣ�	������ƽɨ��
*
*	��ڲ�����	GPIOX����Ҫɨ���GPIO��	NUM����GPIO���ڵı��
*
*	���ز�����	IO��ƽ״̬
*
*	˵����		
************************************************************
*/
_Bool KeyScan(GPIO_TypeDef* GPIOX, unsigned int NUM)
{
	
	if(GPIOX == GPIOC)
	{
		if(!GPIO_ReadInputDataBit(GPIOC, NUM))	//����  Ϊ��
		{
			return KEYDOWN;
		}
		else									//����  Ϊ��
		{
			return KEYUP;
		}
	}
	else if(GPIOX == GPIOD)
	{
		if(!GPIO_ReadInputDataBit(GPIOD, NUM))	//����  Ϊ��
		{
			return KEYDOWN;
		}
		else									//����  Ϊ��
		{
			return KEYUP;
		}
	}
	
	return KEYUP;								//Ĭ�Ϸ��ذ����ͷ�
	
}

/*
************************************************************
*	�������ƣ�	Keyboard
*
*	�������ܣ�	�������ܼ��
*
*	��ڲ�����	
*
*	���ز�����	IO��ƽ״̬
*
*	˵����		
************************************************************
*/
unsigned char Keyboard(void)
{
	
	if(KeyScan(GPIOC, KEY0) == KEYDOWN)
	{
		while(KeyScan(GPIOC, KEY0) != KEYUP);		//�ȴ��ͷ�
		return KEY0DOWN;
	}
	
	if(KeyScan(GPIOC, KEY1) == KEYDOWN)
	{
		while(KeyScan(GPIOC, KEY1) != KEYUP);		//�ȴ��ͷ�
		return KEY1DOWN;
	}
	
	if(KeyScan(GPIOC, KEY2) == KEYDOWN)
	{
		while(KeyScan(GPIOC, KEY2) != KEYUP);		//�ȴ��ͷ�
		return KEY2DOWN;
	}
	
	if(KeyScan(GPIOD, KEY3) == KEYDOWN)
	{
		while(KeyScan(GPIOD, KEY3) != KEYUP);		//�ȴ��ͷ�
		return KEY3DOWN;
	}
	
	return KEYNONE;
	
}
/*
************************************************************
*	�������ƣ�	Keyboard
*
*	�������ܣ�	�����˵�����
*
*	��ڲ�����	
*
*	���ز�����	��ʾ����仯
*
*	˵����		
************************************************************
*/
u8 menu=0,menu1=0;
extern bool GO_1;
void KEY_red(void)
{
 switch(Keyboard())
  {
  case KEY0DOWN:{
       GO_1=false;      
       menu-=1;
       if(menu<1) menu=1;
       else if(menu>9) menu=10;
       OLED_Interface(menu);

      }break;
   case KEY1DOWN:{
            GO_1=false;
            menu+=1;
            if(menu>10)  menu=1;
            else if(menu<1) menu=10;
            OLED_Interface(menu);
        }break;
    case KEY2DOWN:{
                 GO_1=true;
	      }break;
case KEY3DOWN:{
  
                    
     }break;			
  default:
   break;	
 }
}


