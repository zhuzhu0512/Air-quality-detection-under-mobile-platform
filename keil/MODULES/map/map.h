/*   map.h    */

/* ------------------------------�����ֹ�ݹ���� ----------------------------*/
#ifndef  __MAP_H_
#define  __MAP_H_
#define  MAP_BIT 3
/* -------------------------------������ͷ�ļ� -------------------------------*/
#include "sys.h"


/***********************************************************************/
//��ͼ�ӿ�
//���ߣ�����ٻ
//���֧��9��ͼ
//ÿ��ͼ���30��
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




