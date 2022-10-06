/*   motor.h    */

/* ------------------------------定义防止递归包含 ----------------------------*/
#ifndef  __MOTOR_H_
#define  __MOTOR_H_
/* -------------------------------包含的头文件 -------------------------------*/
#include "sys.h"


/***********************************************************************/
//电机控制接口
//作者：朱庆倩
/***********************************************************************/
#define MOV_SPD 800
#define MOV_ACC 20
#define ECD_DIV 64
#define MOT_RAT 90
#define WHL_DMT 96
#define WHL_DIS 232.8
#define CNT_Pmm (MOT_RAT*ECD_DIV)/(WHL_DMT*3.1415926)
#define CNT_Prd  (MOT_RAT*ECD_DIV)/WHL_DMT*WHL_DIS/3.1415926/2

extern int motor1_PWM;
extern int motor1_speed,motor1_speed_l;
extern int motor1_acce,motor1_acce_l;
extern int motor2_PWM;
extern long motor2_count,motor2_count_l;
extern int motor2_speed,motor2_speed_l;
extern int motor2_acce,motor2_acce_l;
extern u32 timCnt;

void Motor_PWM_Init(u16 arr,u16 psc);
//void Motor1_EncoderInit(void);							//电机初始化
//void Motor1_EncoderEnable(void);
//void Motor1_EncoderDisable(void);
//void Motor2_EncoderInit(void);	
//void Motor2_EncoderEnable(void);
//void Motor2_EncoderDisable(void);
//void Motor_PIDInit(void);
//void Motor_PID(void);
//void Motor_PIDr(void);

//调试界面
void Motor_State(void);

//每次运动前都要初始化
void Move_Init(void);   				

//mode  1:加速   0:减速
//运行结束后调用Move_Disable
void Move_Forward(u8 mode);
void Move_Backward(u8 mode);
void Turn_left(u8 mode);
void Turn_Right(u8 mode);

//mode:0 直线, 1 旋转; target: 目标距离(mm||rad) >0: 前进(右转) <0: 后退(左转)
void Move_To(u8 mode,float target);

//停止
void Move_Disable(void);







#endif /*  */




