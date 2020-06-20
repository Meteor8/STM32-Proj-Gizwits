#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "usart3.h"
#include "timer.h"
#include "gizwits_product.h"

dataPoint_t currentDataPoint;

void Hardware_Init(void); 
void mykey(void);
void Gizwits_Init(void);



int main(void)
{	 
	Hardware_Init();
	Gizwits_Init();
	printf("��ʼ����� \r\n");
	LCD_ShowString(00,00,220,24,24,"��ʼ�����!"); 
	delay_ms(1000);
	LCD_Clear(WHITE);
	POINT_COLOR=BLACK;	  
	LCD_ShowString(00,00,220,24,24,"Welcome!");
	LCD_ShowString(00,150,220,24,24,"LED:");

  while(1) 
	{		    					  		 
		mykey();
		gizwitsHandle((dataPoint_t *)&currentDataPoint);
	} 
}

void Hardware_Init(void)
{
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);
	TIM2_Int_Init(1999,35999);
 	LED_Init();			     //LED�˿ڳ�ʼ��
	KEY_Init();

	LCD_Init();
}


void mykey(void)
{
	if(WK_UP==1)
	{
		delay_ms(100);
		if(WK_UP==1)
		{
			LED1=!LED1;
			gizwitsSetMode(WIFI_AIRLINK_MODE);		//SOFTAP/AIRLINK
			printf("������� \r\n");
			LCD_ShowString(00,50,230,24,24,"WIFI_AIRLINK_MODE:OK"); 
			
		}
		while(WK_UP==1);
		
	}
}

void Gizwits_Init(void)
{
	TIM3_Int_Init(9,7199);
	usart3_init(9600);
	memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));
	gizwitsInit();
}

