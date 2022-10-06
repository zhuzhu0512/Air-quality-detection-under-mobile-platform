/*   map.c    */

/* -------------------------------包含的头文件 -------------------------------*/
#include "UI.h"
#include "map.h"
#include "delay.h"
#include "stdio.h"
#include "sdio_sdcard.h"
#include "led.h"
#include "ff.h"
#include "motor.h"
#include "math.h"
/***********************************************************************/
//LCD显示屏UI接口
//作者：朱庆倩
/***********************************************************************/
float map_pointsX[30]={0.0};
float map_pointsY[30]={0.0};
int map_pointsS[30]={0};
float map_pointsAng[30]={0.0};
float map_pointsDis[30]={0.0};
u16 map_pointcount=0;
u16 map_num=0;
u8 Get_MapValue(char *txt,u32 txtsize)
{
	u16 i,lines=0,addr=0;
	for(i=0;i<txtsize;i++)
	{
		if(txt[i]=='\n')
		{
			txt[i]='\0';
			sscanf(txt+addr,"%f,%f,%d",&map_pointsX[lines],&map_pointsY[lines],&map_pointsS[lines]);
			lines++;
			addr=i+1;
		}
	}
	return lines;
}
void test_SD(void)
{
	
	//FatFs变量定义
	FATFS fs; 
	FIL fsrc;
	FILINFO fno;
	const char f_path[]={"Map01.map"};
	const char test_txt[]={"0.0,0.0,0\n0.0,100.0,1\n100.0,100.0,1\n100.0,0.0,1\n"};
	unsigned char error_txt[100];
	u8 test_buf[600];
	u32 txtsize=0;
	u16 i=0;

	u8 t=0,r=0;
	//延时1秒
	UI_Error("SD card test!");

	Start:
	//开始初始化SD卡
	while( SD_OK != SD_Init() ){
		delay_ms(30);
		t++;
		if(t%10==0){
			//BEEP_TOGGLE();
			//LED_TOGGLE(LED1);
		}
		if(t>30){
			t=0;
			UI_Error("SD init failed!");
		}
	}
	//BEEP_OFF();
	UI_Error("SD init secceed!");
	sprintf(error_txt,"SD size: %dMB",(u32)SDCardInfo.CardCapacity/1024/1024);
	UI_Error(error_txt);
	
	//开始初始化文件系统
	while(FR_OK != f_mount(&fs,"0:",1)){
		delay_ms(30);
		t++;
		if(t%10==0){
			//BEEP_TOGGLE();
			LED_TOGGLE(LED1);
		}
		if(t>30){
			t=0;
			UI_Error("SD load failed!");
		}
	}
	//BEEP_OFF();
	UI_Error("SD load succeed!");
	
	
	//开始创建文件
	r=f_open(&fsrc,f_path,FA_CREATE_ALWAYS|FA_READ|FA_WRITE);
	if(FR_OK != r){
		UI_Error("Create failed!");
		goto Start;
	}
	UI_Error("Create succeed!");
	
	
	//开始写入数据
	r=f_write(&fsrc,test_txt,strlen((const char*)test_txt),&txtsize);
	//写入数据完毕，关闭文件
	f_close(&fsrc);
	if(FR_OK != r){
		UI_Error("Write failed!");
		goto Start;
	}
	sprintf(error_txt,"Write %dB!",txtsize);
	UI_Error(error_txt);
	
	sprintf(error_txt,"%s",f_path);
	UI_Error(error_txt);
	r=f_stat (f_path, &fno);
	sprintf(error_txt,"%ld %d %d",fno.fsize,fno.ftime,r);
	UI_Error(error_txt);

	
	//重新打开文件，准备读取数据
	r=f_open(&fsrc,f_path,FA_READ|FA_WRITE);
	if(FR_OK != r){
		UI_Error("Open failed!");
		goto Start;
	}
	UI_Error("Open succeed!");
	
	
	//开始读取数据
	r=f_read(&fsrc,test_buf,strlen((const char*)test_txt),&txtsize);//	
	f_close(&fsrc);
	if(FR_OK != r){
		UI_Error("Read failed!");
		goto Start;
	}
	sprintf(error_txt,"Get %dB data:",txtsize);
	UI_Error(error_txt);
	
	map_pointcount=Get_MapValue(test_buf,txtsize);
	for(i=0;i<map_pointcount;i++)
	{
		sprintf(error_txt,"%f  %f  %d",map_pointsX[i],map_pointsY[i],map_pointsS[i]);
		UI_Error(error_txt);
	}


	//测试完成
	UI_Error("Test finished!");
}

void List_Maps(void)
{
  char f_path[]={"Map01.map"};

	//FatFs变量定义
	FATFS fs; 
	FIL fsrc;
	//const char f_path[]={"Map01.map"};
	//unsigned char error_txt[100];

	u8 t=0,r=0;
	//延时1秒
	//开始初始化SD卡
	while( SD_OK != SD_Init() ){
		delay_ms(30);
		t++;
		if(t%10==0){
			//BEEP_TOGGLE();
			//LED_TOGGLE(LED1);
		}
		if(t>30){
			t=0;
			UI_Error("SD init failed!");
		}
	}
	//BEEP_OFF();
//	UI_Error("SD init secceed!");
//	sprintf(error_txt,"SD size: %dMB",(u32)SDCardInfo.CardCapacity/1024/1024);
//	UI_Error(error_txt);
	
	//开始初始化文件系统
	while(FR_OK != f_mount(&fs,"0:",1)){
		delay_ms(30);
		t++;
		if(t%10==0){
			//BEEP_TOGGLE();
			LED_TOGGLE(LED1);
		}
		if(t>30){
			t=0;
			UI_Error("SD load failed!");
		}
	}
	//BEEP_OFF();
//	UI_Error("SD load succeed!");

	map_num=0;
	do
	{
		sprintf(f_path,"Map%02d.map",++map_num);
	//	UI_Error(f_path);
		//打开文件
		r=f_open(&fsrc,f_path,FA_OPEN_EXISTING|FA_READ);
		if(FR_OK != r){
//			UI_Error("Open failed!");
			break;
		}
		f_close(&fsrc);
//		UI_Error(f_path);
	}
	while(map_num<=10);
	map_num--;
}

void Read_Map(u16 mapid)
{
	char f_path[]={"Map01.map"};
	//FatFs变量定义
	FATFS fs; 
	FIL fsrc;
	//const char f_path[]={"Map01.map"};
	unsigned char error_txt[100];
	u8 test_buf[600];
	u32 txtsize=0;
	u16 i=0;

	u8 t=0,r=0;
	//延时1秒
	//开始初始化SD卡
	while( SD_OK != SD_Init() ){
		delay_ms(30);
		t++;
		if(t%10==0){
			//BEEP_TOGGLE();
			//LED_TOGGLE(LED1);
		}
		if(t>30){
			t=0;
			UI_Error("SD init failed!");
		}
	}
	//BEEP_OFF();
//	UI_Error("SD init secceed!");
//	sprintf(error_txt,"SD size: %dMB",(u32)SDCardInfo.CardCapacity/1024/1024);
//	UI_Error(error_txt);
	
	//开始初始化文件系统
	while(FR_OK != f_mount(&fs,"0:",1)){
		delay_ms(30);
		t++;
		if(t%10==0){
			//BEEP_TOGGLE();
			LED_TOGGLE(LED1);
		}
		if(t>30){
			t=0;
			UI_Error("SD load failed!");
		}
	}
	
	sprintf(f_path,"Map%02d.map",mapid);
	//	UI_Error(f_path);
		//打开文件
	r=f_open(&fsrc,f_path,FA_OPEN_EXISTING|FA_READ);
	if(FR_OK != r){
		UI_Error("Open failed!");
	}
	//开始读取数据
	r=f_read(&fsrc,test_buf,600,&txtsize);//	
	f_close(&fsrc);
	if(FR_OK != r){
		UI_Error("Read failed!");
		return;
	}
//	UI_Error(test_buf);
	//处理数据
	map_pointcount=Get_MapValue(test_buf,txtsize);
//	for(i=0;i<map_pointcount;i++)
//	{
//		sprintf(error_txt,"%f,%f,%d",map_pointsX[i],map_pointsY[i],map_pointsS[i]);
//		UI_Error(error_txt);
//	}
}	

void Save_Map(u16 mapid)
{

}	

void Exct_Map(void)
{
	int i;
	unsigned char error_txt[100];
	float targetAng,targetDis;
	map_pointsAng[0]=3.1415926/2;
	map_pointsDis[0]=0;
	for(i=1;i<map_pointcount;i++)
	{
		if(map_pointsX[i]==map_pointsX[i-1])
		{
			if(map_pointsY[i]>=map_pointsY[i-1])
			{
				map_pointsAng[i]=3.1415926/2;
			}
			else
			{
				map_pointsAng[i]=-3.1415926/2;
			}
		}
		else if(map_pointsX[i]>map_pointsX[i-1])
		{
			map_pointsAng[i]=atan((map_pointsY[i]-map_pointsY[i-1])/(map_pointsX[i]-map_pointsX[i-1]));
		}
		else
		{
			map_pointsAng[i]=atan((map_pointsY[i]-map_pointsY[i-1])/(map_pointsX[i]-map_pointsX[i-1]))+3.1415926;
		}
		map_pointsDis[i]=sqrt(pow((map_pointsY[i]-map_pointsY[i-1]),2)+pow((map_pointsX[i]-map_pointsX[i-1]),2));
	}
	//go
	for(i=1;i<map_pointcount;i++)
	{
		targetAng=map_pointsAng[i-1]-map_pointsAng[i];
		if(targetAng>3.1415926)
		{
			targetAng-=3.1415926*2;
		}
		else if(targetAng<=-3.1415926)
		{
			targetAng+=3.1415926*2;
		}
		targetDis=map_pointsDis[i];
//		sprintf(error_txt,"Ang:%f",targetAng);
//		UI_Error(error_txt);
		Move_Init();
		Move_To(1,targetAng);
		Move_Init();
		Move_To(0,targetDis);
	}
	//back
	Move_Init();
	Move_To(1,3.1415926);
	for(i=map_pointcount-1;i>0;i--)
	{
		targetAng=map_pointsAng[i-1]-map_pointsAng[i];
		if(targetAng>3.1415926)
		{
			targetAng-=3.1415926*2;
		}
		else if(targetAng<=-3.1415926)
		{
			targetAng+=3.1415926*2;
		}
		targetDis=map_pointsDis[i];
//		sprintf(error_txt,"Ang:%f",targetAng);
//		UI_Error(error_txt);
		Move_Init();
		Move_To(0,targetDis);
		Move_Init();
		Move_To(1,-targetAng);
	}
	Move_Init();
	Move_To(1,3.1415926);
}



