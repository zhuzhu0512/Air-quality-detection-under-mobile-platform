/*   sensor.c    */


/* -------------------------------������ͷ�ļ� -------------------------------*/
#include "sensor.h"
#include "usart.h"
#include "UI.h"
#include "delay.h"


/***********************************************************************/
//�����������ӿ�
//���ߣ����S@�Ϻ���ͨ��ѧ
/***********************************************************************/

//�۳���������ʼ��
//ʹ�ô���2
//����->5V,����->GND,����->PA3,����->PA2
void Sensor_PMInit(void)
{
	
}  

//�۳�������ֵ
void Sensor_PMValue(u16 PM2_5, u16 PM10, u16 PM1)
{
	unsigned char str[100];
	u8 buffer[4][9]={
		{0xFF, 0x01, 0xA7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x58},//�˳�����
		{0xFF, 0x01, 0x78, 0x41, 0x00, 0x00, 0x00, 0x00, 0x46},//�����ʴ�ģʽ
		{0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79},//ѯ��
		{0xFF, 0x01, 0xA7, 0x01, 0x00, 0x00, 0x00, 0x00, 0x57}//��������
	};
	
	int n,i;
	u8 check=0;
	PM_send:
	USART2_Init(9600);//����2��ʼ��
	for(n=0;n<4;n++)
	{
		
		usart2_buf_len=0;
		USART_SendBuf(USART2,buffer[n],9);
		i=0;
		delay_ms(20);
		if(n==2)
		{
			//��ʾ����ֵ
			for(i=0;i<usart2_buf_len;i++)
			{
				sprintf(str+3*i, "%02X ",usart2_buf[i]);
			}
			UI_Error(str);
			//У�鷵��ֵ
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

//��ȩ��������ʼ��
//ʹ�ô���3
//����->5V,����->GND,����->PB10,����->PB11
void Sensor_CH2OInit(void)
{
	
}  

//��ȩŨ��ֵ
void Sensor_CH2OValue(u16 ug_m3, u16 ppb)
{
	unsigned char str[100];
	u8 buffer[4][9]={
		{0xFF, 0x01, 0x78, 0x41, 0x00, 0x00, 0x00, 0x00, 0x46},//�����ʴ�ģʽ
		{0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79}//ѯ��
	};
	
	int n,i;
	u8 check=0;
	CH2O_send:
	USART3_Init(9600);//����2��ʼ��
	for(n=0;n<2;n++)
	{
		
		usart3_buf_len=0;
		USART_SendBuf(USART3,buffer[n],9);
		i=0;
		delay_ms(100);
		if(n==1)
		{
			//��ʾ����ֵ
			for(i=0;i<usart3_buf_len;i++)
			{
				sprintf(str+3*i, "%02X ",usart3_buf[i]);
			}
			UI_Error(str);
			//У�鷵��ֵ
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


