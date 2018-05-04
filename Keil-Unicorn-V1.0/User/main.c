#include "includes.h"
/*****************��������*************/
/*<<<<<<< HEAD:Unicorn-V1.0/User/main.c*/
static void vTaskFLASH(void *pvParameters);
static void vTaskLED(void *pvParameters);
static void vTaskMsgPro(void *pvParameters);
static void vTaskStart(void *pvParameters);
static void AppTaskCreate (void);
/*****************��������**************/
static TaskHandle_t xHandleTaskFLASH = NULL;
static TaskHandle_t xHandleTaskLED = NULL;
static TaskHandle_t xHandleTaskMsgPro = NULL;
static TaskHandle_t xHandleTaskStart = NULL;
/**
  * @brief  ��ѭ��
  * @param  None
  * @retval None
  */
int main(void)
{         
          Delay_Init();	//Timer3��ʼ��
          IIC_Init();	//I2C���߳�ʼ��
          ADXL362_Init();    //������ټƳ�ʼ��
          LCD_Init();
          KEY_Init();
          LED_Init();
          Beep_Init();
          LIGHT_Init();//��ʼ��
         //__set_PRIMASK(1); 
        //��ʼ�� RTUģʽ �ӻ���ַΪ1 USART1 9600 ��У��
          eMBInit(MB_RTU, 0x01, 0x01, 9600, MB_PAR_NONE);
        //����FreeModbus 
          eMBEnable();
          Usart2_Init(115200);//����2������ESP8266��
          ESP8266_Init();
        // ��������
        AppTaskCreate();
                
        /* �������ȣ���ʼִ������ */
        vTaskStartScheduler();
        /* 
        ���ϵͳ���������ǲ������е�����ģ����е����Ｋ�п��������ڶ�ʱ��������߿��������
        heap�ռ䲻����ɴ���ʧ�ܣ���Ҫ�Ӵ�FreeRTOSConfig.h�ļ��ж����heap��С��
        #define configTOTAL_HEAP_SIZE	      ( ( size_t ) ( 17 * 1024 ) )
        */
          while(1);
}
/*
*********************************************************************************************************
*	�� �� ��: vTaskFLASH
*	����˵��: �ӿ���Ϣ������������FLASH
*	��    ��: pvParameters ���ڴ���������ʱ���ݵ��β�
*	�� �� ֵ: ��
*   �� �� ��: 1  (��ֵԽС���ȼ�Խ�ͣ������uCOS�෴)
*********************************************************************************************************
*/
//Ҫд�뵽STM32 FLASH���ַ�������
//#define FLASH_SAVE_ADDR  0X08020000   
//#define SIZE sizeof(FreeSize)	 	//���鳤��
//u8 FreeSize[]={"STM32 ModbusTEST"};  
//u8 datatemp[SIZE];   
bool GO_1=false;
extern u8 menu;
bool flag_LED=false,flag_Beep=false;
//����FLASH �����ַ(����Ϊż��������ֵҪ���ڱ�������ռ��FLASH�Ĵ�С+0X08000000)
static void vTaskFLASH(void *pvParameters)
{
    while(1)
    {
         KEY_red();
        if(GO_1==true)	
        {
          OLED_function(menu);
	}
        if(flag_LED==true)
        {
           LCD_CLS();
           OLED_P6x8Str(0,4,"LED !"); 
           Led1_Set(LED_ON);vTaskDelay(500);Led1_Set(LED_OFF);		//����LED4������ʱ500ms��Ȼ��Ϩ��LED4
               
           Led2_Set(LED_ON);vTaskDelay(500);Led2_Set(LED_OFF);		//����LED5������ʱ500ms��Ȼ��Ϩ��LED5
                      
           Led3_Set(LED_ON);vTaskDelay(500);Led3_Set(LED_OFF);		//����LED6������ʱ500ms��Ȼ��Ϩ��LED6
                      
           Led4_Set(LED_ON);vTaskDelay(500);Led4_Set(LED_OFF);		//����LED7������ʱ500ms��Ȼ��Ϩ��LED7
           flag_LED=false;
        }
        if(flag_Beep==true)
        {
             LCD_CLS();
             OLED_P6x8Str(0,4,"Beep !"); 
             Beep_Set(BEEP_ON);
             vTaskDelay(1000);
             Beep_Set(BEEP_OFF);           //�򿪷�����,�رշ�����
             flag_Beep=false;
       }
       //STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)datatemp,SIZE);
      //STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)FreeSize,SIZE);
      vTaskDelay(100);
    }
}

/*
*********************************************************************************************************
*	�� �� ��: vTaskLED
*	����˵��: ��������&�Ƕȴ�����	
*	��    ��: pvParameters ���ڴ���������ʱ���ݵ��β�
*	�� �� ֵ: ��
*   �� �� ��: 2  
*********************************************************************************************************
*/
static void vTaskLED(void *pvParameters)
{
    /* LED��˸ */
    while(1)
    {
      LIGHT_GetVoltag() ;//����
      ADXL362_GetValue();
      vTaskDelay(100);
    }
}

/*
*********************************************************************************************************
*	�� �� ��: vTaskMsgPro
*	����˵��: ��Ϣ��������������LED��˸	
*	��    ��: pvParameters ���ڴ���������ʱ���ݵ��β�
*	�� �� ֵ: ��
*   �� �� ��: 3  
*********************************************************************************************************
*/
static void vTaskMsgPro(void *pvParameters)
{
    while(1)
    { 
        eMBPoll(); 
        vTaskDelay(300);
    }
}

/*
*********************************************************************************************************
*	�� �� ��: vTaskStart
*	����˵��: ��������Ҳ����������ȼ�������������LED��˸
*	��    ��: pvParameters ���ڴ���������ʱ���ݵ��β�
*	�� �� ֵ: ��
*   �� �� ��: 4  
*********************************************************************************************************
*/
static void vTaskStart(void *pvParameters)
{
    while(1)
    {
        LED_Poll();
        vTaskDelay(400);
    }
}

/*
*********************************************************************************************************
*	�� �� ��: AppTaskCreate
*	����˵��: ����Ӧ������
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void AppTaskCreate (void)
{
    xTaskCreate( vTaskFLASH,   	/* ������  */
                 "vTaskFLASH",     	/* ������    */
                 512,               	/* ����ջ��С����λword��Ҳ����4�ֽ� */
                 NULL,              	/* �������  */
                 1,                 	/* �������ȼ�*/
                 &xHandleTaskFLASH );  /* ������  */
	
	
	xTaskCreate( vTaskLED,    		/* ������  */
                 "vTaskLED",  		/* ������    */
                 512,         		/* ����ջ��С����λword��Ҳ����4�ֽ� */
                 NULL,        		/* �������  */
                 2,           		/* �������ȼ�*/
                 &xHandleTaskLED ); /* ������  */
	
	xTaskCreate( vTaskMsgPro,     		/* ������  */
                 "vTaskMsgPro",   		/* ������    */
                 512,             		/* ����ջ��С����λword��Ҳ����4�ֽ� */
                 NULL,           		/* �������  */
                 3,               		/* �������ȼ�*/
                 &xHandleTaskMsgPro );  /* ������  */
	
	
	xTaskCreate( vTaskStart,     		/* ������  */
                 "vTaskStart",   		/* ������    */
                 512,            		/* ����ջ��С����λword��Ҳ����4�ֽ� */
                 NULL,           		/* �������  */
                 4,              		/* �������ȼ�*/
                 &xHandleTaskStart );   /* ������  */    
}
