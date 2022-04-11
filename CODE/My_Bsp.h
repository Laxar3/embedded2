/*
 *  My_Bsp.h
 *
 *  Created on: 2021��1��10��
 *      Author: LBQ
 */

#ifndef CODE_MY_BSP_H_
#define CODE_MY_BSP_H_

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//library h
#include "headfile.h"

//user library h
#include "anotc.h"      //������λ��
#include "tfminiplus.h" //TfMiniPlus�����״�
//#include "SEEKFREE_7725.h"

//user h
#include "define.h"     //��������
#include "magnet.h"     //���
#include "pid.h"        //PID
#include "control.h"    //����
#include "encoder.h"    //������
#include "motor.h"      //���
#include "screen.h"     //��Ļ
#include "gyro.h"       //������
#include "sg.h"         //���
#include "key.h"        //����
#include "beep.h"       //��������LED
#include "camera.h"     //����ͷ��ֵ��
#include "photo.h"      //����ͷ����

#define Pi  (3.14159265f)
#define ONE_PI  (3.14159265f)
#define TWO_PI  (2.000f * 3.14159265f)
#define ANGLE_UNIT  (TWO_PI / 10.0f)
#define EPS (1e-6)

#define mian main   // :D

//Define
#define ABS(x)  (((x) > 0) ? (x) : (-(x)))                                                  //�궨��ʵ�ַ��ؾ���ֵ(x�ﲻ�����Լ��Լ�����䣬�����������)
#define LIMIT(x, min, max)  (((x) < (min)) ? (min) : ( ((x) > (max)) ? (max) : (x)))        //�޷�
#define RANGE(x, max, min)  (((x) <= (min)) ? (min) : ( ((x) >= (max)) ? (max) : (x)))      //ȷ��x�ķ�ΧΪmin~max
#define MIN(x, y)   (((x) < (y)) ? (x) : (y))                                               //ȡСֵ
#define MAX(x, y)   (((x) > (y)) ? (x) : (y))                                               //ȡ��ֵ
#define SIGN(x) (((x) > 0) ? 1 :-1) //((int32)(((x)>0?1:-1)*ceil(ABS((x)))))                //ȡ����
#define INT(x)  ((int)(x))   //((int32)(((x)>0?1:-1)*ceil(ABS((x)))))                       //ǿ������
#define SWAP(x, y)   do{(x) ^= (y); (y) ^= (x); (x) ^= (y);} while(0)                       //���� x, y ��ֵ
#define ARR_SIZE(a) ( sizeof( (a) ) / sizeof( ((a)[0]) ) )                                  //��������Ԫ�صĸ���
#define OFFSET(type, member)    ((uint32)(&(((type *)0)->member)))                          //��ȡ�ṹ��ĳ��Աƫ��


//Function
unsigned char My_Bsp_Init(void);
void delay_ms(uint64 ms);
void delay_us(uint64 us);
void My_swap(int *x, int *y);
float My_sqrt(float number);
float InvSqrt(float x);
int My_pow(int x, int y);
//float mx_sin(float rad);
float My_sin(float rad);
float My_cos(float rad);
char Get_State(char x);



// ����16λ���ݵ�2�ֽ�˳��
#if 1                   //���ַ���, ��һ����CMSIS���Դ�
#define SWAP16(data)    __REVSH(data)
#else
#define SWAP16(data)    (uint32)((((uint16)(data) & (0xFF<<0 ))<<8)      \
                          | (((uint32)(data) & (0xFF<<8))>>8)            \
                        )
#endif


// ����32λ���ݵ�4�ֽ�˳��
#if 1                    //���ַ���, ��һ����CMSIS���Դ�
#define SWAP32(data)    __REV(data)
#else
#define SWAP32(data)    (uint32)((((uint32)(data) & (0xFFu<<0 ))<<24)      \
                          | (((uint32)(data) & (0xFFu<<8 ))<<8)            \
                          | (((uint32)(data) & (0xFFu<<16))>>8)            \
                          | (((uint32)(data) & (0xFFu<<24))>>24)           \
                        )
#endif


// ��ӡ�궨��չ�����
#define _MKSTR(str)  #str
#define MKSTR(str)  _MKSTR(str)                       // �Ѻ궨��չ�����ת��Ϊ�ַ���
#define DEFINE_PRINTF(def)  printf(MKSTR(def)"\n")    // ���ڴ�ӡ�궨��չ�����


#endif
