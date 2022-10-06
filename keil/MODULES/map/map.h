/*   map.h    */

/* ------------------------------定义防止递归包含 ----------------------------*/
#ifndef  __MAP_H_
#define  __MAP_H_
#define  MAP_BIT 3
/* -------------------------------包含的头文件 -------------------------------*/
#include "sys.h"


/***********************************************************************/
//地图接口
//作者：朱庆倩
//最多支持9地图
//每地图最多30点
/***********************************************************************/
extern float map_pointsX[30];
extern float map_pointsY[30];
extern int map_pointsS[30];
extern u16 map_pointcount;
extern u16 map_num;

void test_SD(void);											
void List_Maps(void);	
void Read_Map(u16 mapid);	
void Save_Map(u16 mapid);
void Exct_Map(void);	








#endif /*  */




