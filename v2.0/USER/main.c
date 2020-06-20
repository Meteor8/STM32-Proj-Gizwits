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
	printf("初始化完成 \r\n");
	LCD_ShowString(00,00,220,24,24,"初始化完成!"); 
	delay_ms(1000);
	LCD_Clear(WHITE);
	POINT_COLOR=BLACK;	  
	LCD_ShowString(00,00,220,24,24,"Welcome!");
	LCD_ShowString(00,50,300,24,24,"Press KEYUP to Reconnect"); 	
	LCD_ShowString(00,150,220,24,24,"LED0:");
	LCD_ShowString(00,200,220,24,24,"LED1:");

  while(1) 
	{		    					  		 
		mykey();
		gizwitsHandle((dataPoint_t *)&currentDataPoint);
		userHandle();
	} 
}

void Hardware_Init(void)
{
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);
	TIM2_Int_Init(1999,35999);
	TIM3_PWM_Init(99,719);
 	LED_Init();			     //LED端口初始化
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
			gizwitsSetMode(WIFI_AIRLINK_MODE);		//SOFTAP/AIRLINK
			printf("配网完成 \r\n");				
			LCD_ShowString(00,50,300,24,24,"Connected!  MODE:AIRLINK"); 	
		}
		while(WK_UP==1);
	}
	if(KEY1==0)
	{
		delay_ms(100);
		if(KEY1==0)
		{
			LED0=~LED0;
		}
		while(KEY1==0);
	}
	if(KEY0==0)
	{
		delay_ms(100);
		if(KEY0==0)
		{
			;
		}
		while(KEY0==0);
	}
}

void Gizwits_Init(void)
{
	TIM3_Int_Init(90,719);
	usart3_init(9600);
	memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));
	gizwitsInit();
}

extern u8 wifi_flag;

void userHandle(void)
{
	if(wifi_flag==1)
	{
		if(LED0==0)
		{
			currentDataPoint.valueled0 = 1;
			LCD_ShowString(100,150,220,24,24,"on ");
		}
		else
		{
			currentDataPoint.valueled0 = 0;
			LCD_ShowString(100,150,220,24,24,"off");
		}
		TIM_SetCompare2(TIM3,currentDataPoint.valueled1/10);
	}
}

