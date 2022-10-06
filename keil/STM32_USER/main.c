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

//u8 lcd_buf[50]={0};//������ʱ�洢LCD��ʾ���ַ���



int main(void)
{
	delay_init();	    //��ʱ������ʼ��
	LCD_Init();    //LCD��ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	Key_Init();   //IO��ʼ��
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
//��ʱ���жϷ������
void TIM6_IRQHandler(void)   //TIM�ж�
{
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)  //���TIM�����жϷ������
		{
			TIM_ClearITPendingBit(TIM6, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
			//LED1=!LED1;
			timCnt++;
		}
}
#endif



