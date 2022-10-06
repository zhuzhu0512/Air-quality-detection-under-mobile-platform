/*   sensor.c    */


/* -------------------------------包含的头文件 -------------------------------*/
#include "sensor.h"
#include "usart.h"
#include "UI.h"
#include "delay.h"


/***********************************************************************/
//空气传感器接口
//作者：杨赟@上海交通大学
/***********************************************************************/

//粉尘传感器初始化
//使用串口2
//红线->5V,黑线->GND,黄线->PA3,绿线->PA2
void Sensor_PMInit(void)
{
	
}  

//粉尘传感器值
void Sensor_PMValue(u16 PM2_5, u16 PM10, u16 PM1)
{
	unsigned char str[100];
	u8 buffer[4][9]={
		{0xFF, 0x01, 0xA7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x58},//退出休眠
		{0xFF, 0x01, 0x78, 0x41, 0x00, 0x00, 0x00, 0x00, 0x46},//设置问答模式
		{0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79},//询问
		{0xFF, 0x01, 0xA7, 0x01, 0x00, 0x00, 0x00, 0x00, 0x57}//进入休眠
	};
	
	int n,i;
	u8 check=0;
	PM_send:
	USART2_Init(9600);//串口2初始化
	for(n=0;n<4;n++)
	{
		
		usart2_buf_len=0;
		USART_SendBuf(USART2,buffer[n],9);
		i=0;
		delay_ms(20);
		if(n==2)
		{
			//显示返回值
			for(i=0;i<usart2_buf_len;i++)
			{
				sprintf(str+3*i, "%02X ",usart2_buf[i]);
			}
			UI_Error(str);
			//校验返回值
			check=0;
			for(i=1;i<(usart2_buf_len-1);i++)
			{
				check+=usart2_buf[i];
			}
			check=(~check)+1;
			if(check!=usart2_buf[(usart2_buf_len-1)])
			{
				UI_Error("Bad data");
				goto PM_send;
			}
			//pm2
			PM2_5=(usart2_buf[2]<<8)+usart2_buf[3];
			PM10 =(usart2_buf[4]<<8)+usart2_buf[5];
			PM1  =(usart2_buf[6]<<8)+usart2_buf[7];
		}
	}
	USART2_Close();
	sprintf(str, "PM2.5:%5d PM10 :%5d PM1  :%5d",PM2_5,PM10,PM1);
	UI_Error(str);
}

//甲醛传感器初始化
//使用串口3
//红线->5V,黑线->GND,蓝线->PB10,绿线->PB11
void Sensor_CH2OInit(void)
{
	
}  

//甲醛浓度值
void Sensor_CH2OValue(u16 ug_m3, u16 ppb)
{
	unsigned char str[100];
	u8 buffer[4][9]={
		{0xFF, 0x01, 0x78, 0x41, 0x00, 0x00, 0x00, 0x00, 0x46},//设置问答模式
		{0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79}//询问
	};
	
	int n,i;
	u8 check=0;
	CH2O_send:
	USART3_Init(9600);//串口2初始化
	for(n=0;n<2;n++)
	{
		
		usart3_buf_len=0;
		USART_SendBuf(USART3,buffer[n],9);
		i=0;
		delay_ms(100);
		if(n==1)
		{
			//显示返回值
			for(i=0;i<usart3_buf_len;i++)
			{
				sprintf(str+3*i, "%02X ",usart3_buf[i]);
			}
			UI_Error(str);
			//校验返回值
			check=0;
			for(i=1;i<(usart3_buf_len-1);i++)
			{
				check+=usart3_buf[i];
			}
			check=(~check)+1;
			if(check!=usart3_buf[(usart3_buf_len-1)])
			{
				UI_Error("Bad data");
				goto CH2O_send;
			}
			//pm2
			ug_m3=(usart3_buf[2]<<8)+usart3_buf[3];
			ppb  =(usart3_buf[6]<<8)+usart3_buf[7];
		}
	}
	USART3_Close();
	sprintf(str, "CH2O:       %5d ug/m^3%5d ppb",ug_m3,ppb);
	UI_Error(str);
}


