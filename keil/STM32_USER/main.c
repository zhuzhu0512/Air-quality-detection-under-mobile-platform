/*  main.c  */

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "ezio.h"
#include "key.h"
#include "LcdApi.h"
#include "LcdBsp.h"
#include "touch.h"
#include "adc.h"
#include "timer.h"
#include "string.h"
#include "beep.h"
#include "w25qxx.h"
#include "page.h"
#include "UI.h"
#include "sensor.h"
#include "motor.h"
#include "map.h"

//u8 lcd_buf[50]={0};//用于临时存储LCD显示的字符串



int main(void)
{
	delay_init();	    //延时函数初始化
	LCD_Init();    //LCD初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	Key_Init();   //IO初始化
	//Motor_PWM_Init(1000-1,72-1);
	TIM_SetInterval(6,1000);//1ms
	timCnt=0;
	//	Sensor_PMValue(0,0,0);
	//	Sensor_CH2OValue(0,0);
	
//		LCD_Clear(BACK_COLOR);
//		Move_Init();
//		Move_To(0,100);
	while(1)
	{
		Page_Main();
	}
}

#if 1
//定时器中断服务程序
void TIM6_IRQHandler(void)   //TIM中断
{
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)  //检查TIM更新中断发生与否
		{
			TIM_ClearITPendingBit(TIM6, TIM_IT_Update  );  //清除TIMx更新中断标志 
			//LED1=!LED1;
			timCnt++;
		}
}
#endif



