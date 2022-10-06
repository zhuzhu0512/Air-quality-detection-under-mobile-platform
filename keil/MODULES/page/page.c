/*   page.c    */

/* -------------------------------包含的头文件 -------------------------------*/
#include "LcdBsp.h"
#include "page.h"
#include "UI.h"
#include "stdio.h"
#include "map.h"
#include "key.h"
/***********************************************************************/
//页面
//作者：朱庆倩
/***********************************************************************/


//RunOnce菜单
void Page_Run(u8 autorun)
{
	int selectedID;
	u16 keyflag=0,returnflag=0;
	u8 *list[10];
	u8 list_buf[100];
	List_Maps();
	for(selectedID=0;selectedID<map_num;selectedID++)
	{
		list[selectedID]=list_buf+10*selectedID;
		sprintf(list[selectedID],"MAP%02d",selectedID+1);
	}
	selectedID=0;
	LCD_Clear(BACK_COLOR);
	while(!returnflag)
	{
		UI_Option(list, map_num, &selectedID);
		keyflag=0;
		while(!keyflag)
		{
			switch(UI_WaitKey(0))
			{
				case 0x101://右单击
					keyflag=1;
					Read_Map(selectedID+1);	
					UI_Map();
					Exct_Map();
					Key_Init(); 
					LCD_Clear(BACK_COLOR);
					break;
				case 0x102://下单击
					keyflag=1;
					selectedID++;
					break;
				case 0x104://左单击
					keyflag=1;
					returnflag=1;
					LCD_Clear(BACK_COLOR);
					break;
				case 0x108://上单击
					keyflag=1;
					selectedID--;
					break;
				case 0x202://上长按
					keyflag=1;
					do
					{
						selectedID++;
						UI_Option(list, map_num, &selectedID);
					}
					while(UI_WaitKey(100));
					break;
				case 0x208://下长按
					keyflag=1;
					do
					{
						selectedID--;
						UI_Option(list, map_num, &selectedID);
					}
					while(UI_WaitKey(100));
					break;
				default:
					keyflag=0;
			}
		}
	}
}


//主菜单
//selectedID,选中的参数；
//operate,操作：0无,1确认,2返回
void Page_Main(void)
{
	int selectedID=0;
	u16 keyflag=0,returnflag=0;
	u8 *list[]={"Run Once", "Auto Run", "Create Map" , "Settings" ,"About Us"};
	LCD_Clear(BACK_COLOR);
	while(!returnflag)
	{
		UI_Option(list, 5, &selectedID);
		keyflag=0;
		while(!keyflag)
		{
			switch(UI_WaitKey(0))
			{
				case 0x101://右单击
					keyflag=1;
					switch(selectedID)
					{
						case 0:
							Page_Run(0);
							break;
						case 1:
							Page_Run(1);
							break;
						case 2:
							test_SD();
							break;
						default: 
							break;
					}
					break;
				case 0x102://下单击
					keyflag=1;
					selectedID++;
					break;
				case 0x104://左单击
					keyflag=1;
					returnflag=1;
					LCD_Clear(BACK_COLOR);
					break;
				case 0x108://上单击
					keyflag=1;
					selectedID--;
					break;
				case 0x202://上长按
					keyflag=1;
					do
					{
						selectedID++;
						UI_Option(list, 5, &selectedID);
					}
					while(UI_WaitKey(100));
					break;
				case 0x208://下长按
					keyflag=1;
					do
					{
						selectedID--;
						UI_Option(list, 5, &selectedID);
					}
					while(UI_WaitKey(100));
					break;
				default:
					keyflag=0;
			}
		}
	}
}	



