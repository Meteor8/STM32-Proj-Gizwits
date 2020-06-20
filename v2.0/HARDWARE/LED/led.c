#include "led.h"
 

//³õÊ¼»¯PB5ºÍPE5ÎªÊä³ö¿Ú.²¢Ê¹ÄÜÕâÁ½¸ö¿ÚµÄÊ±ÖÓ		    
//LED IO³õÊ¼»¯
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);	 //Ê¹ÄÜPB,PE¶Ë¿ÚÊ±ÖÓ
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //LED1-->PB.5 ¶Ë¿ÚÅäÖÃ
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //ÍÆÍìÊä³ö
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO¿ÚËÙ¶ÈÎª50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //¸ù¾İÉè¶¨²ÎÊı³õÊ¼»¯GPIOB.5
 GPIO_SetBits(GPIOB,GPIO_Pin_5);						 //PB.5 Êä³ö¸ß

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //LED0-->PE.5 ¶Ë¿ÚÅäÖÃ, ÍÆÍìÊä³
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //ÍÆÍìÊä³ö £¬IO¿ÚËÙ¶ÈÎª50MHz
 GPIO_SetBits(GPIOE,GPIO_Pin_5); 						 //PE.5 Êä³ö¸ß 
}
 
