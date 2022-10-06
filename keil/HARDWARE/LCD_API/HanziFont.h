/*   HanziFont.h    */

/* ------------------------------定义防止递归包含 ----------------------------*/
#ifndef __HANZI_FONT_H_
#define __HANZI_FONT_H_

/* -------------------------------包含的头文件 -------------------------------*/
#include "sys.h"



// ------------------  汉字字模的数据结构定义 ------------------------ //



typedef struct                   // 汉字字模数据结构 
{
  unsigned char  Index[3];       // 汉字内码索引	
  unsigned char   Msk[24];       // 点阵码数据 
}typFNT_GB12;


typedef struct                   // 汉字字模数据结构 
{
  unsigned char  Index[3];       // 汉字内码索引	
  unsigned char   Msk[32];       // 点阵码数据 
}typFNT_GB16;

typedef struct                  // 汉字字模数据结构 
{
  unsigned char  Index[3];      // 汉字内码索引	
  unsigned char   Msk[72];      // 点阵码数据 
}typFNT_GB24;


//PC2LCD2002取模方式设置：阴码+逐列式+顺向+C51格式
const typFNT_GB24 codeGB_24[]={//数据表 
	
{"七",0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x08,0x00,0x00,0x08,0x00,0x00,0x08,0x00,0x00,0x08,0x00,0x00,0x10,0x00,0x00,0x10,0x00,0x00,0x10,0x00,0x3F,0xFF,0xF8,0x1F,0xFF,0xFC,0x00,0x20,0x04,0x00,0x20,0x04,0x00,0x20,0x04,0x00,0x40,0x04,0x00,0x40,0x04,0x00,0x40,0x04,0x00,0x40,0x04,0x00,0x80,0x04,0x01,0x80,0x0C,0x00,0x80,0xFC,0x00,0x00,0x08,0x00,0x00,0x00},/*"七",0*/
{"彩",0x00,0x00,0x00,0x00,0x10,0x08,0x10,0x10,0x10,0x14,0x10,0x20,0x13,0x90,0xC0,0x11,0x91,0x80,0x10,0x1E,0x00,0x18,0x7F,0xFE,0x27,0x7F,0xFC,0x20,0x12,0x00,0x20,0xD1,0x02,0x23,0x11,0x82,0x6E,0x10,0xE4,0x28,0x90,0x04,0x01,0x02,0x08,0x01,0x04,0x08,0x02,0x04,0x10,0x04,0x08,0x20,0x08,0x10,0x60,0x18,0x30,0xC0,0x30,0x61,0x80,0x00,0x43,0x80,0x00,0x01,0x00,0x00,0x00,0x00},/*"彩",1*/
{"光",0x00,0x00,0x00,0x00,0x20,0x02,0x00,0x20,0x02,0x00,0x20,0x04,0x00,0x20,0x04,0x08,0x20,0x08,0x04,0x20,0x10,0x03,0x20,0x60,0x01,0xBF,0xC0,0x00,0x3C,0x00,0x00,0x20,0x00,0x3F,0xE0,0x00,0x3F,0xE0,0x00,0x00,0x3F,0xF0,0x00,0x3F,0xFC,0x00,0xE0,0x04,0x03,0x20,0x04,0x0E,0x20,0x04,0x04,0x20,0x04,0x00,0x20,0x04,0x00,0x60,0x04,0x00,0x20,0xFC,0x00,0x00,0x08,0x00,0x00,0x00},/*"光",2*/
{"子",0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x10,0x00,0x00,0x10,0x00,0x10,0x10,0x00,0x10,0x10,0x00,0x10,0x10,0x00,0x10,0x10,0x08,0x10,0x10,0x08,0x10,0x10,0x04,0x10,0x10,0x06,0x10,0xFF,0xFE,0x10,0xFF,0xFC,0x11,0x10,0x00,0x11,0x10,0x00,0x12,0x10,0x00,0x14,0x10,0x00,0x18,0x10,0x00,0x18,0x10,0x00,0x10,0x10,0x00,0x00,0x30,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"子",3*/
{"太",0x00,0x00,0x00,0x00,0x00,0x02,0x01,0x00,0x02,0x01,0x00,0x04,0x01,0x00,0x08,0x01,0x00,0x10,0x01,0x00,0x30,0x01,0x00,0x60,0x01,0x01,0x80,0x01,0x07,0x80,0x01,0x7C,0x40,0x7F,0xE0,0x60,0x21,0x00,0x38,0x01,0xF0,0x18,0x01,0x0C,0x00,0x01,0x03,0x00,0x01,0x00,0xC0,0x01,0x00,0x60,0x01,0x00,0x30,0x01,0x00,0x18,0x03,0x00,0x0C,0x01,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00},/*"太",4*/
{"极",0x00,0x00,0x00,0x02,0x00,0x40,0x02,0x01,0x80,0x02,0x06,0x00,0x02,0x78,0x00,0x7F,0xFF,0xFE,0x22,0x40,0x1C,0x02,0x20,0x02,0x02,0x18,0x04,0x12,0x18,0x18,0x10,0x00,0x62,0x10,0x03,0x84,0x1F,0xFC,0x04,0x10,0x38,0x08,0x10,0x06,0x10,0x10,0x41,0xB0,0x10,0xE0,0xE0,0x13,0xC1,0xE0,0x1E,0x43,0x30,0x18,0x5E,0x18,0x10,0x70,0x0C,0x00,0x40,0x0C,0x00,0x00,0x00,0x00,0x00,0x00},/*"极",5*/
{"开",0x00,0x00,0x00,0x00,0x10,0x00,0x10,0x10,0x02,0x10,0x10,0x04,0x10,0x10,0x08,0x10,0x10,0x18,0x10,0x10,0x30,0x10,0x11,0xC0,0x1F,0xFF,0x00,0x10,0x10,0x00,0x10,0x10,0x00,0x10,0x10,0x00,0x10,0x10,0x00,0x10,0x10,0x00,0x10,0x10,0x00,0x1F,0xFF,0xFE,0x10,0x10,0x00,0x10,0x10,0x00,0x10,0x10,0x00,0x30,0x10,0x00,0x10,0x30,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"开",6*/
{"发",0x00,0x00,0x00,0x00,0x00,0x02,0x01,0x00,0x04,0x03,0x80,0x08,0x0F,0x00,0x10,0x19,0x00,0x62,0x11,0x01,0xC2,0x01,0x07,0x02,0x01,0x7C,0x04,0x1F,0xF0,0x04,0x79,0x1C,0x08,0x01,0x12,0x18,0x01,0x11,0x90,0x01,0x10,0x60,0x41,0x10,0x60,0x21,0x11,0xB0,0x31,0x13,0x18,0x1D,0x1E,0x18,0x0D,0x18,0x0C,0x01,0x00,0x0C,0x03,0x00,0x06,0x01,0x00,0x04,0x00,0x00,0x04,0x00,0x00,0x00},/*"发",7*/
{"板",0x00,0x00,0x00,0x02,0x00,0x40,0x02,0x01,0x80,0x02,0x0E,0x00,0x02,0xF0,0x00,0x7F,0xFF,0xFF,0x02,0x20,0x00,0x02,0x30,0x02,0x02,0x1C,0x05,0x00,0x00,0x1A,0x10,0x07,0xE2,0x0F,0xFE,0x04,0x08,0x80,0x0C,0x08,0xF8,0x08,0x10,0x87,0x30,0x10,0x81,0xE0,0x10,0x81,0xF0,0x30,0x87,0x18,0x20,0xBC,0x0C,0x60,0xE0,0x0E,0x00,0x80,0x06,0x00,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00},/*"板",8*/


};
//

const typFNT_GB16 codeGB_16[] = {// 数据表 

{"七",0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x02,0x00,0xFF,0xFC,0x02,0x02,0x02,0x02,0x02,0x02,0x04,0x02,0x04,0x02,0x04,0x02,0x04,0x1E,0x00,0x00,0x00,0x00},/*"七",0*/
{"彩",0x00,0x02,0x28,0x84,0x26,0x88,0x20,0xB0,0x30,0xC0,0x4D,0xFF,0x40,0xA0,0xC4,0x90,0x58,0x88,0x00,0x01,0x04,0x21,0x08,0x42,0x10,0x84,0x61,0x08,0x06,0x30,0x00,0x00},/*"彩",1*/
{"光",0x02,0x01,0x02,0x01,0x42,0x02,0x22,0x04,0x1A,0x18,0x03,0xE0,0x02,0x00,0xFE,0x00,0x02,0x00,0x03,0xFC,0x0A,0x02,0x12,0x02,0x62,0x02,0x02,0x02,0x02,0x1E,0x00,0x00},/*"光",2*/
{"子",0x01,0x00,0x41,0x00,0x41,0x00,0x41,0x00,0x41,0x00,0x41,0x02,0x41,0x01,0x47,0xFE,0x45,0x00,0x49,0x00,0x51,0x00,0x61,0x00,0x41,0x00,0x01,0x00,0x01,0x00,0x00,0x00},/*"子",3*/
{"太",0x04,0x01,0x04,0x01,0x04,0x02,0x04,0x04,0x04,0x08,0x04,0x30,0x04,0xC8,0xFF,0x06,0x04,0xC0,0x04,0x30,0x04,0x08,0x04,0x04,0x04,0x02,0x04,0x01,0x04,0x01,0x00,0x00},/*"太",4*/
{"极",0x08,0x20,0x08,0xC0,0x0B,0x00,0xFF,0xFF,0x09,0x00,0x08,0xC2,0x40,0x0C,0x40,0xF1,0x7F,0x01,0x40,0xC2,0x40,0x34,0x46,0x08,0x5A,0x34,0x63,0xC2,0x00,0x01,0x00,0x00},/*"极",5*/
{"开",0x01,0x00,0x41,0x01,0x41,0x02,0x41,0x0C,0x7F,0xF0,0x41,0x00,0x41,0x00,0x41,0x00,0x41,0x00,0x41,0x00,0x7F,0xFF,0x41,0x00,0x41,0x00,0x41,0x00,0x01,0x00,0x00,0x00},/*"开",6*/
{"发",0x00,0x00,0x00,0x04,0x18,0x08,0x68,0x31,0x08,0xC1,0x0B,0x01,0x1D,0x82,0xE9,0x62,0x09,0x14,0x09,0x08,0x09,0x14,0x49,0x22,0x29,0xC2,0x08,0x01,0x00,0x01,0x00,0x00},/*"发",7*/
{"板",0x08,0x20,0x08,0xC0,0x0B,0x00,0xFF,0xFF,0x09,0x00,0x08,0xC1,0x00,0x06,0x3F,0xF8,0x24,0x01,0x27,0x82,0x24,0x64,0x44,0x18,0xC4,0x64,0x47,0x82,0x00,0x01,0x00,0x00},/*"板",8*/

};

//

const typFNT_GB12 codeGB_12[] = {// 数据表 
{"七",0x04,0x00,0x04,0x00,0x04,0x00,0x04,0x00,0xFF,0xE0,0x08,0x10,0x08,0x10,0x08,0x10,0x08,0x10,0x08,0x10,0x08,0x70,0x00,0x00},/*"七",0*/
{"彩",0x52,0x20,0x4A,0x40,0x62,0x80,0x97,0xF0,0x8A,0x80,0xB2,0x40,0x00,0x10,0x11,0x10,0x22,0x20,0xC4,0x40,0x18,0x80,0x00,0x00},/*"彩",1*/
{"光",0x04,0x10,0x44,0x20,0x24,0x40,0x17,0x80,0x04,0x00,0xFC,0x00,0x04,0x00,0x17,0xE0,0x24,0x10,0x44,0x10,0x04,0x70,0x00,0x00},/*"光",2*/
{"子",0x02,0x00,0x02,0x00,0x42,0x00,0x42,0x10,0x42,0x10,0x4F,0xF0,0x52,0x00,0x62,0x00,0x42,0x00,0x02,0x00,0x02,0x00,0x00,0x00},/*"子",3*/
{"太",0x10,0x10,0x10,0x20,0x10,0x40,0x11,0x80,0x16,0x40,0xF8,0x20,0x17,0x00,0x10,0xC0,0x10,0x20,0x10,0x10,0x10,0x10,0x00,0x00},/*"太",4*/
{"极",0x11,0x00,0x16,0x00,0xFF,0xF0,0x12,0x10,0x40,0x60,0x7F,0x80,0x41,0x10,0x40,0xA0,0x4C,0x40,0x74,0xA0,0x07,0x10,0x00,0x00},/*"极",5*/
{"开",0x02,0x00,0x42,0x10,0x42,0x60,0x7F,0x80,0x42,0x00,0x42,0x00,0x42,0x00,0x7F,0xF0,0x42,0x00,0x42,0x00,0x02,0x00,0x00,0x00},/*"开",6*/
{"发",0x70,0x20,0x10,0x40,0x11,0x90,0x1E,0x10,0xF3,0x20,0x12,0xA0,0x12,0x40,0x92,0xA0,0x53,0x20,0x10,0x10,0x10,0x10,0x00,0x00},/*"发",7*/
{"板",0x11,0x00,0x16,0x00,0xFF,0xF0,0x14,0x10,0x02,0x20,0x7F,0xC0,0x48,0x10,0x4F,0xA0,0x48,0x40,0x89,0xA0,0x8E,0x10,0x00,0x00},/*"板",8*/
};
//













#endif /*  */


