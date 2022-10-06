/*   UI.c    */

/* -------------------------------包含的头文件 -------------------------------*/
#include "LcdBsp.h"
#include "UI.h"
#include "key.h"
#include "delay.h"
#include "stdio.h"
#include "map.h"
/***********************************************************************/
//LCD显示屏UI接口
//作者：朱庆倩
/***********************************************************************/

//显示菜单
//*p,为菜单所有项目的字符串数组;
//selectedID,为选中的项目。
void UI_Option(u8 **p, u16 num, int *selectedID)
{
	u16 i,h=40;
	u16 start=0,t;
//	LCD_Clear(BACK_COLOR);
	if(*selectedID>=num)
	{
		*selectedID=0;
	}
	else if(*selectedID<0)
	{
		*selectedID=num-1;
	}
	if(*selectedID>6)
	{
		start=*selectedID-5;
	}
	LCD_DrawLine(0, 0, 240-1, 0);
	for(i=0;i<6;i++)
	{
		t=i+start;
		if(t<num)
		{
			if(t==*selectedID)
			{
				BACK_COLOR=BLACK;
				POINT_COLOR=WHITE;
				LCD_Fill(0,i*h+4,239,i*h+35,BACK_COLOR);
				LCD_ShowString(15,i*h+4,240-15,32,32,p[t]);
				BACK_COLOR=WHITE;
				POINT_COLOR=BLACK;
			}
			else
			{
				LCD_Fill(0,i*h+4,239,i*h+35,BACK_COLOR);
				LCD_ShowString(15,i*h+4,240-15,32,32,p[t]);
			}
		}
		LCD_DrawLine(0, i*h+h-1, 240-1, i*h+h-1);
		LCD_DrawLine(0, i*h+h, 240-1, i*h+h);
	}
	UI_Operate();
}	

//操作指南
void UI_Operate(void)					
{
	u16 a,b,h;
	h=40;
	//UP
	b=240+24;
	a=31;
	LCD_Draw_Circle(a,b,12);
	LCD_DrawLine(a, b-12, a, b+12);
	LCD_DrawLine(a, b-12, a-8, b);
	LCD_DrawLine(a, b-12, a+8, b);
	LCD_ShowString(15+a,b-12,240-15,24,24,"UP");
	//DOWN
	b=240+h+20;
	a=31;
	LCD_Draw_Circle(a,b,12);
	LCD_DrawLine(a, b-12, a, b+12);
	LCD_DrawLine(a, b+12, a-8, b);
	LCD_DrawLine(a, b+12, a+8, b);
	LCD_ShowString(15+a,b-12,240-15,24,24,"DOWN");
	//RIGHT
	b=240+24;
	a=120+15;
	LCD_Draw_Circle(a,b,12);
	LCD_DrawLine(a-12, b, a+12, b);
	LCD_DrawLine(a, b+8, a+12, b);
	LCD_DrawLine(a, b-8, a+12, b);
	LCD_ShowString(15+a,b-12,240-15,24,24,"SELECT");
	//LEFT
	b=240+h+20;
	a=120+15;
	LCD_Draw_Circle(a,b,12);
	LCD_DrawLine(a-12, b, a+12, b);
	LCD_DrawLine(a, b+8, a-12, b);
	LCD_DrawLine(a, b-8, a-12, b);
	LCD_ShowString(15+a,b-12,240-15,24,24,"BACK");
}

//绘制地图
void UI_Map(void)
{
	float max_x=0,max_y=0,min_x=0,min_y=0,size_x,size_y,size_all;
	u16 i,j=0,margin_side=8,margin_top=48,side_len,o_x,o_y;
	u32 scale;
	u8 str[10];
	LCD_Clear(BACK_COLOR);
	
	if(map_pointcount<2)
	{
		return;
	}
	

	//搜索地图边界
	for(i=1;i<map_pointcount;i++)
	{
		if(map_pointsX[i]>max_x) max_x=map_pointsX[i];
		if(map_pointsX[i]<min_x) min_x=map_pointsX[i];
		if(map_pointsY[i]>max_y) max_y=map_pointsY[i];
		if(map_pointsY[i]<min_y) min_y=map_pointsY[i];
	}
	size_x=max_x-min_x;
	size_y=max_y-min_y;
	
	//确定比例尺(mm/px)
	size_all=size_x;
	if(size_y>size_x) size_all=size_y;
	side_len=240-margin_side*2;
	scale=1;
	while((scale*side_len)<=(size_all*1.1))
	{
		scale=scale<<1;
	}
	
	//画边框
	LCD_ShowString(margin_side-1,margin_top-31,240-margin_side,32,32,"MAP");
	LCD_DrawRectangle(margin_side-1, margin_top-1, margin_side+side_len, margin_top+side_len);
	//画比例尺
	LCD_DrawLine(margin_side-1, margin_top+side_len+15, margin_side-1, margin_top+side_len+19);
	LCD_DrawLine(margin_side-1, margin_top+side_len+19, margin_side-1+40, margin_top+side_len+19);
	LCD_DrawLine(margin_side-1+40, margin_top+side_len+15, margin_side-1+40, margin_top+side_len+19);
	sprintf(str,"%dmm",scale*40);
	LCD_ShowString(margin_side+40,margin_top+side_len+3,240-margin_side-40,24,24,str);
	
	//画地图
	//计算原点
	o_x=240/2-(max_x+min_x)/2/scale;
	o_y=margin_top+side_len/2+(max_x+min_x)/2/scale;
	for(i=0;i<map_pointcount-1;i++)
	{
		LCD_DrawLine(o_x+map_pointsX[i]/scale, o_y-map_pointsY[i]/scale, o_x+map_pointsX[i+1]/scale, o_y-map_pointsY[i+1]/scale);
		if(map_pointsS[i]>0 || i==0)
		{
			sprintf(str,"%d",j);
			LCD_ShowString(o_x+map_pointsX[i]/scale-3,o_y-map_pointsY[i]/scale-6,12,12,12,str);
			j++;
		}
	}
	LCD_ShowString(o_x+map_pointsX[i]/scale-9,o_y-map_pointsY[i]/scale-6,18,12,12,"end");
}	

//地图指南
void UI_MapHelp(void)
{
}	

//关于
void UI_AboutMACM(void)
{
}

//Error
void UI_Error(u8 *p)
{
	LCD_Clear(BACK_COLOR);
	LCD_ShowString(15,15,240-15,32,32,"NOTICE!");
	LCD_DrawRectangle(15, 47, 240-16, 320-16);
	LCD_ShowString(23,55,240-24*2,32*6,32,p);
	while(!UI_WaitKey(0))
	{
	}
	LCD_Clear(BACK_COLOR);
}

//等待获取按键操作
//低4位返回二进制按键值
//       UP    LEFT  DOWN  RIHGT 
//       X     X     X     X
//按下   1     1     1     1
//未按   0     0     0     0
//高4位返回操作类型				响应速度
//0x00XX:up								瞬间
//0x01XX:click						延时
//0x02XX:long press				延时
u16 UI_WaitKey(u16 time)
{
	u16 keys,keys_t,i,j;
	//获取之前的按键状态
	for(i=0;i<4;i++)
	{
		if(Key_Sta[i]==1)
		{
			keys_t=keys_t|(1<<i);
		}
		Key_Sta[i]=0;
	}
	
	//第一次扫描，直到状态变化,或超时
	j=0;
	do
	{
		//超时
		if(time!=0 && (j*20)>=time)
		{
			return (0x0200+keys_t);
		}
		
		//获取当前按键状态
		keys=0;
		if(Key_ScanPro(0))
		{
			for(i=0;i<4;i++)
			{
				if(Key_Sta[i]==1)
				{
					keys=keys|(1<<i);
				}
			}
		}
		j++;
	}
	while(keys==keys_t);
		
	//如果全部按钮松开
	if(keys==0)
	{
		return 0;
	}
	
	//持续扫描200ms
	for(j=0;j<10;j++)
	{
		//获取当前按键状态
		if(Key_ScanPro(0))
		{
			for(i=0;i<4;i++)
			{
				if(Key_Sta[i]==1)
				{
					keys=keys|(1<<i);
				}
			}
		}
	}
	keys_t=keys;
	
	//第3次扫描
	while(Key_ScanPro(0)==0);
	keys=0;
	for(i=0;i<4;i++)
	{
		if(Key_Sta[i]==1)
		{
			keys=keys|(1<<i);
		}
	}
	if(keys==0)//所有按钮松开->click
	{
		keys=0x0100+keys_t;
	}
	else			//按钮未松开->long press
	{
		keys+=0x0200;
	}
	
	return 	keys;
}
