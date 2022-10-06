/*   motor.c    */

/* -------------------------------包含的头文件 -------------------------------*/
#include "motor.h"
#include "LcdBsp.h"
#include "stdio.h"
#include "delay.h"
#include "ezio.h"
/***********************************************************************/
//电机控制接口
//作者：朱庆倩
/***********************************************************************/
u16 tim_period=65535;
int motor1_PWM=0;
int motor1_r=0;
long motor1_count=0,motor1_count_l=0;
int motor1_speed=0,motor1_speed_l=0;
int motor1_acce=0,motor1_acce_l=0;

int motor2_PWM=0;
int motor2_r=0;
long motor2_count=0,motor2_count_l=0;
int motor2_speed=0,motor2_speed_l=0;
int motor2_acce=0,motor2_acce_l=0;

int c,c_l;
long target_count=0,disp_count=0,disp_count_l=0;

u32 timCnt,wav_y=0;
/*  电机PWM */
//TIM8 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void Motor_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_BaseInitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	GPIO_DeInit(GPIOC);
	GPIO_DeInit(GPIOA);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8|RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1|RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_11; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_DeInit(TIM8);
	TIM_DeInit(TIM1);
	
	TIM_BaseInitStructure.TIM_Period =arr;
	TIM_BaseInitStructure.TIM_Prescaler = psc; 
	TIM_BaseInitStructure.TIM_ClockDivision = 0; 
	TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_BaseInitStructure.TIM_RepetitionCounter=0x00;
	TIM_TimeBaseInit(TIM8, &TIM_BaseInitStructure); 
	TIM_TimeBaseInit(TIM1, &TIM_BaseInitStructure);
	
	/* Output Compare Active Mode configuration: Channel4 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	
	TIM_OCInitStructure.TIM_Pulse = 0x0001;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset ;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
				
	TIM_OC1Init(TIM8, &TIM_OCInitStructure); 
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
	
	TIM_OC2Init(TIM8, &TIM_OCInitStructure); 
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
	
	TIM_OC1Init(TIM1, &TIM_OCInitStructure); 
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
	TIM_OC4Init(TIM1, &TIM_OCInitStructure); 
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM8, ENABLE);   
	TIM_CtrlPWMOutputs(TIM8, ENABLE); 
	TIM_Cmd(TIM8,ENABLE); 

	TIM_ARRPreloadConfig(TIM1, ENABLE);   
	TIM_CtrlPWMOutputs(TIM1, ENABLE); 
	TIM_Cmd(TIM1,ENABLE); 
	
	
	TIM_SetCompare1(TIM8,0);
	TIM_SetCompare2(TIM8,0);
	TIM_SetCompare1(TIM1,0);
	TIM_SetCompare4(TIM1,0);
	Pin_ModeSet(PC0,OUTPUT|OUT_H);
	Pin_ModeSet(PC1,OUTPUT|OUT_H);
	Pin_ModeSet(PC2,OUTPUT|OUT_H);
	Pin_ModeSet(PC3,OUTPUT|OUT_H);
}

void Motor1_Run(int dpwm)
{

	if(motor1_PWM+dpwm>=0)
	{
		TIM_SetCompare1(TIM8,motor1_PWM+dpwm);
		TIM_SetCompare2(TIM8,0);
	}
	else
	{
		TIM_SetCompare1(TIM8,0);
		TIM_SetCompare2(TIM8,-motor1_PWM-dpwm);
	}
}

void Motor2_Run(int dpwm)
{
	if(motor2_PWM+dpwm>=0)
	{
		TIM_SetCompare1(TIM1,motor2_PWM+dpwm);
		TIM_SetCompare4(TIM1,0);
	}
	else
	{
		TIM_SetCompare1(TIM1,0);
		TIM_SetCompare4(TIM1,-motor2_PWM-dpwm);
	}
}

/* 左电机编码器 */

//使用TIM3定时器
//黄->PA6, 白->PA7, 蓝->5v, 绿->GND
void Motor1_EncoderInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
  TIM_ICInitTypeDef  TIM_ICInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
  /* TIM clock source enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  
	/* Enable PA6,PA7 */
  GPIO_StructInit(&GPIO_InitStructure);                     
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA,&GPIO_InitStructure);
  
	/* Timer configuration in Encoder mode */
  TIM_DeInit(TIM3);
 
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;
  TIM_TimeBaseStructure.TIM_Period =tim_period; 
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
 
  // TIM编码模式3
  TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
  TIM_ICStructInit(&TIM_ICInitStructure); 
  TIM_ICInitStructure.TIM_ICFilter = 6;
  TIM_ICInit(TIM3, &TIM_ICInitStructure);
  
  //Reset counter
  TIM3->CNT = 0;
	
	/* 开启编码器计数溢出 */
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
	motor1_r=0;
   
}
void Motor1_EncoderEnable(void)
{
	TIM_Cmd(TIM3, ENABLE);
}

void Motor1_EncoderDisable(void)
{
	TIM_Cmd(TIM3, DISABLE);
}

//定时器3中断服务程序
//编码器溢出
void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
//		LED1=!LED1;
			if(TIM3->CNT<tim_period/2)
			{
				motor1_r++;
			}
			else
			{
				motor1_r--;
			}
		}
}


/*  右电机编码器 */

//使用TIM4定时器
//黄->PB7, 白->PB6, 蓝->5v, 绿->GND
void Motor2_EncoderInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
  TIM_ICInitTypeDef  TIM_ICInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
  /* TIM clock source enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
  
	/* Enable PB6,PB7 */
  GPIO_StructInit(&GPIO_InitStructure);                     
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB,&GPIO_InitStructure);
  
	/* Timer configuration in Encoder mode */
  TIM_DeInit(TIM4);
 
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;
  TIM_TimeBaseStructure.TIM_Period =tim_period; 
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
 
 // TIM编码模式3
  TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
  TIM_ICStructInit(&TIM_ICInitStructure); 
  TIM_ICInitStructure.TIM_ICFilter = 6;
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
  
  //Reset counter
  TIM4->CNT = 0;
   
	/* 开启编码器计数溢出 */
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //使能指定的TIM4中断,允许更新中断

	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM4中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
	motor2_r=0;
	
}
void Motor2_EncoderEnable(void)
{
	TIM_Cmd(TIM4, ENABLE);
}

void Motor2_EncoderDisable(void)
{
	TIM_Cmd(TIM4, DISABLE);
}

//定时器4中断服务程序
//编码器溢出
void TIM4_IRQHandler(void)   //TIM4中断
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
//		LED1=!LED1;
			if(TIM4->CNT<tim_period/2)
			{
				motor2_r++;
			}
			else
			{
				motor2_r--;
			}
		}
}

//PID电机调速PWM
//aim: motor1_count_l==motor1_count_l
void Motor_PIDInit(void)
{
	c=0;
	c_l=0;
	motor1_PWM=0;
	motor2_PWM=0;
	Motor_PWM_Init(1000-1,72-1);
	
	Motor1_EncoderInit();
	Motor2_EncoderInit();
	Motor1_EncoderEnable();
	Motor2_EncoderEnable();

	


}
void Motor_PID(u8 mode)
{
	int dpwm=0,t=10;
	float kp=15,ki=0.01,kd=200;//PID
	//update data
	motor1_count_l=motor1_count;
	motor2_count_l=motor2_count;
	motor1_count=TIM3->CNT+motor1_r*tim_period;
	motor2_count=TIM4->CNT+motor2_r*tim_period;
	c_l=c;
	//caculate
	if(mode==0)
		c=motor2_count-motor1_count;
	else
		c=-motor2_count-motor1_count;
	
	dpwm=kp*c+ki*(c+c_l)*t+kd*(c-c_l)/t;
	

	if(motor1_PWM+dpwm>999) dpwm=999-motor1_PWM;
	if(motor1_PWM+dpwm<-999) dpwm=-999-motor1_PWM;
	//dpwm=0;
	Motor1_Run(dpwm);
	if(mode==0)
		Motor2_Run(-dpwm);
	else
		Motor2_Run(dpwm);
	
}

void Motor_PIDc(u8 mode)
{
	int dpwm=0,t=10;
	float kp=1,ki=0,kd=1200;//PID
	
	disp_count_l=disp_count;
	disp_count=target_count-(TIM3->CNT+motor1_r*tim_period);

	dpwm=kp*disp_count+ki*(disp_count+disp_count_l)*t+kd*(disp_count-disp_count_l)/t;
	
	if(dpwm>MOV_ACC) dpwm=MOV_ACC;
	if(dpwm<-MOV_ACC) dpwm=-MOV_ACC;
	if(motor1_PWM+dpwm>MOV_SPD) dpwm=MOV_SPD-motor1_PWM;
	if(motor1_PWM+dpwm<-MOV_SPD) dpwm=-MOV_SPD-motor1_PWM;
	if(mode==0)
	{
		motor1_PWM+=dpwm;
		motor2_PWM+=dpwm;
	}
	else
	{
		motor1_PWM+=dpwm;
		motor2_PWM-=dpwm;
	}

}

//LCD显示电机状态
void Motor_State(void)
{
	unsigned char str[100];
	
	//caculate
	motor1_speed_l=motor1_speed;
	motor1_speed=motor1_count-motor1_count_l;
	motor1_acce_l=motor1_acce;
	motor1_acce=motor1_speed-motor1_speed_l;
	motor2_speed_l=motor2_speed;
	motor2_speed=motor2_count-motor2_count_l;
	motor2_acce_l=motor2_acce;
	motor2_acce=motor2_speed-motor2_speed_l;
	
//	sprintf(str,"cnt1:%6d",motor1_count);
//	LCD_ShowString(0,0,240,32,32,str);
//	sprintf(str,"spd1:%6d",motor1_speed);
//	LCD_ShowString(0,32,240,32,32,str);
//	sprintf(str,"acc1:%6d",motor1_acce);
//	LCD_ShowString(0,64,240,32,32,str);
//	sprintf(str,"pwm1:%6d",motor1_PWM);
//	LCD_ShowString(0,96,240,32,32,str);

//	sprintf(str,"cnt2:%6d",motor2_count);
//	LCD_ShowString(0,128,240,32,32,str);
//	sprintf(str,"spd2:%6d",motor2_speed);
//	LCD_ShowString(0,160,240,32,32,str);
//	sprintf(str,"acc2:%6d",motor2_acce);
//	LCD_ShowString(0,192,240,32,32,str);
//	sprintf(str,"pwm2:%6d",motor2_PWM);
//	LCD_ShowString(0,224,240,32,32,str);
//	sprintf(str,"%6d",c);
//	LCD_ShowString(0,256,240,32,32,str);
	//LCD_DrawPoint(disp_count/10+120,wav_y++);
//	LCD_DrawPoint(120+c,wav_y++);
//	if(wav_y>=320)
//	{
//		wav_y=0;
//		LCD_Clear(BACK_COLOR);
//	}
	//sprintf(str,"%2d %3d",timCnt,motor1_count+motor2_count);
	//sprintf(str,"%2d %3d",timCnt,disp_count-disp_count_l);
//	sprintf(str,"%6d",disp_count);
//	timCnt=0;
//	LCD_ShowString(0,287,240,32,32,str);
	delay_ms(10);
}

void Move_Init(void)
{
	Motor_PIDInit();
}

void Move_Forward(u8 mode)
{
	if(mode==1)
	{
		motor1_PWM+=MOV_ACC;
		motor2_PWM+=MOV_ACC;
		if(motor1_PWM>MOV_SPD) motor1_PWM=MOV_SPD;
		if(motor2_PWM>MOV_SPD) motor2_PWM=MOV_SPD;
	}
	else if(mode==0)
	{
		motor1_PWM-=MOV_ACC;
		motor2_PWM-=MOV_ACC;
		if(motor1_PWM<0) motor1_PWM=0;
		if(motor2_PWM<0) motor2_PWM=0;
	}
	Motor_PID(0);
	Motor_State();
}

void Move_Backward(u8 mode);
void Turn_left(u8 mode);
void Turn_Right(u8 mode);
void Move_To(u8 mode,float target)
{
	int i=0;

	if(mode==0)
	{
		target_count=target*CNT_Pmm;
	}
	else
	{
		target_count=target*CNT_Prd;
	}
	disp_count=target_count;
	while(i<20)
	{
		Motor_PIDc(mode);
		Motor_PID(mode);
		Motor_State();
		if((motor1_count-target_count)<=2 && (motor1_count-target_count)>=-2)
			i++;
		else
			i=0;
	}
	target_count=0;
	disp_count=target_count;
	//Move_Disable();
}
void Move_Disable(void)
{
	Pin_ModeSet(PC0,OUTPUT|OUT_L);
	Pin_ModeSet(PC1,OUTPUT|OUT_L);
	Pin_ModeSet(PC2,OUTPUT|OUT_L);
	Pin_ModeSet(PC3,OUTPUT|OUT_L);
}
