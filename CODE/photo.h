#ifndef _PHOTO_H_
#define _PHOTO_H_

#include "My_Bsp.h"
#include "math.h"

#define white 255
#define black 0

extern uint8 flag_a;
extern uint8 flag_b;
extern uint8 flag_c;
extern uint8 stop_flag;
extern uint8 stop_count;
//extern uint8 left_lose_near_num;             //��������
//extern uint8 right_lose_near_num;             //�����Ҷ���
//extern uint8 all_lose_near_num;               //����ȫ����
//
//extern uint8 left_lose_far_num;             //Զ������
//extern uint8 right_lose_far_num;             //Զ���Ҷ���
//extern uint8 all_lose_far_num;               //Զ��ȫ����

extern uint8 right_circle_flag;
extern uint8 left_circle_flag;
extern uint8 projecting_point_row;
extern uint8 flag_test;
extern uint8 flag_y;
//extern uint8 flag_wider;
//extern int left_near_notwhite_row;
//extern int right_near_notwhite_row;
//extern uint8 flag_cross_switch;
//extern uint8 flag_circle_switch;
extern uint8 circle_flag;
extern uint8 flag_y_cross;
extern uint8 left_turning_point;
extern uint8 right_turning_point;
//extern uint8 flag_outbound;
//extern uint8 flag_put_in;
extern uint8 flag_y_cross_special;

extern uint8 flag_circle_elc;
extern uint8 flag_err_special;

//��������ṹ��
typedef struct
{
    uint8 x;
    uint8 y;
} Site_t;

//������δ�С�ṹ��
typedef struct
{
    uint8 W;       //��
    uint8 H;       //��
} Size_t;

typedef enum {left=1,right=2}LeOrRi;   //����������߻����ұ�

extern uint8 img[60][80];
extern uint8 left_black[60];
extern uint8 right_black[60];
extern uint8 middle_line[60];
extern uint8 img_real_width[60];
extern uint8 valid_row;
extern uint8 start_row;

/**********��������********/
void get_mid_line(int a);//ͼ������
void find(int dir_num );//��ȡ��������һ��������
int get_direction(Site_t A1,Site_t A2,LeOrRi a);//��ȡ��������ʼλ�÷�λ
int find_valid_row( );//��Ч��ʶ��
void set_valid_val();//�ж����ұ߽��Ƿ���Ч
void set_midline();//�������ߣ���Ѱ�ҵ����ұ߽�����
void init_point();//�����ʼ��
void get_turning_point();//��ѯ�յ�


float  guai_pls(uint8 *array,int row_start,int row_end,char *valid );//��������б��
void lian_xian_zhi(int column1,int row1,int column2,int row2,uint8 *c);//����

void  cross_check1();
void  new_deal_circle_right();
void  scan_circle_right();
void get_ring_point(uint8 a);
void deal_circle_right();


void midline_show();
void img_test();

#endif  //__PHOTO_H__

