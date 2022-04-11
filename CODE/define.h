/*
 *  define.h
 *
 *  Created on: 2021��1��12��
 *      Author: LBQ
 */

#ifndef _DEFINE_H
#define _DEFINE_H

#include "My_Bsp.h"

#define PartUsed        15      //ͼ�񲿷����ʹ�õ�����
#define PartUsed_X      15      //����    ͼ�񲿷����ʹ�õ�����

/**********************PID***********************/

extern  int16   PID1_Parameter_M1[3];
extern  int16   PID1_Parameter_M2[3];
extern  int16   PID1_Parameter_M3[3];
extern  int16   PID1_Parameter_M4[3];

extern  int16   PID2_Parameter_M1[3];
extern  int16   PID2_Parameter_M2[3];
extern  int16   PID2_Parameter_M3[3];
extern  int16   PID2_Parameter_M4[3];

extern  float   Angle1_PID1_40_Parameter[4];    //����
extern  float   Angle1_PID1_45_Parameter[4];    //����
extern  float   Angle1_PID1_50_Parameter[4];    //����
extern  float   Angle1_PID1_55_Parameter[4];    //����
extern  float   Angle1_PID1_60_Parameter[4];    //����
extern  float   Angle1_PID1_65_Parameter[4];    //����
extern  float   Angle1_PID1_70_Parameter[4];    //����
extern  float   Angle1_PID1_Parameter[4];       //����
extern  float   Angle1_PID2_35_Parameter[4];    //����
extern  float   Angle1_PID2_40_Parameter[4];    //����
extern  float   Angle1_PID2_45_Parameter[4];    //����
extern  float   Angle1_PID2_50_Parameter[4];    //����
extern  float   Angle1_PID2_55_Parameter[4];    //����
extern  float   Angle1_PID2_60_Parameter[4];    //����
extern  float   Angle1_PID2_Parameter[4];       //����
extern  float   Angle1_PID3_45_Parameter[4];    //����
extern  float   Angle1_PID3_50_Parameter[4];    //����
extern  float   Angle1_PID3_55_Parameter[4];    //����
extern  float   Angle1_PID3_60_Parameter[4];    //����
extern  float   Angle1_PID3_65_Parameter[4];    //����
extern  float   Angle1_PID3_70_Parameter[4];    //����
extern  float   Angle1_PID3_Parameter[4];       //����
extern  float   Angle1_PID4_45_Parameter[4];    //�뻷
extern  float   Angle1_PID4_50_Parameter[4];    //�뻷
extern  float   Angle1_PID4_55_Parameter[4];    //�뻷

extern  float   Angle1_PID6_Parameter[4];       //���

extern  float   Angle2_PID1_Parameter[4];

extern  float   Gyro_PID_Parameter[4];

extern  int16   Mortor_PWM_Max;
extern  int16   Mortor_PWM_Min;

/**********************CONTROL***********************/

extern  uint8 weight1[60];
/*****����*****/

extern  int8    Speed_Set_y;            //���������ٶ�
extern  int8    Speed_Set_x;            //�����ٶ�
extern  int8    Speed_Set_c;            //�����ٶ�
extern  int8    Speed_Set_in;           //�뻷�ٶ�
extern  uint8   Speed_Set_y_Flag;       //���������ٶ� ��λ
extern  uint8   Speed_Set_x_Flag;       //�����ٶ� ��λ
extern  uint8   Speed_Set_c_Flag;       //�����ٶ� ��λ
extern  uint8   ELC_Protect_Flag;       //��ų�����·������־λ
extern  int8    Speed_Set;              //�趨�ٶ�
extern  int16   Speed_CircleIn;         //�뻷�ٶ�
extern  uint8   middle_standard;        //����ͷ������ֵ
extern  uint8   Car_Direction;          //ǰ������ 1Ϊ����2Ϊ����
extern  float   AngleErr0, AngleErr1, AngleErr2;
extern  float   AngleErr;               //ͼ�����������
extern  float   FusionErr;              //����ͷ�����ں����
extern  float   FusionErr_Last;         //�ϴδ��ں����
extern  int16   AngleOutPut;            //ת��ת�����
extern  int16   Gyro_K;                 //�����ǷŴ�ϵ��
extern  int16   GyroOutPut;             //�Ǽ��ٶ����
//Angle_Part_Process()
extern  uint8   Start_Part;             //����ͼ�����ƫ�ʼ��
extern  uint8   End_Part;               //����ͼ�����ƫ�������
extern  float   Part_Err[PartUsed];     //ͼ�񲿷����
extern  uint8   Improper_Row[PartUsed]; //���Ʋ����õ�ͼ����
extern  uint8   Improper_Row_Count;     //���Ʋ����õ�ͼ��������
//Angle_All_Process()
extern  float   midlinenow;             //ȫͼ�������ĵ�ǰ���
extern  float   midline_f, midline_ff, midline_fff;
extern  float   Slope;                  //��С���˷�����ؾ�ֵ(ûɶ����)
extern  float   Regression_A, Regression_B;
//Gear
extern  int8    MidlineGear;            //Midline_Change����
extern  int8    SlGear;                 //Speed_Change����
extern  int8    SnGear;                 //Speed_Change_Near����
extern  int8    DisGear;                //Dis_Control����
extern  int8    VrGear;                 //ValidRow_Change����
extern  int8    GearCount;              //ƽ������
extern  int8    Gear;                   //����
extern  uint8   Fork_Count;             //�������
extern  uint8   Fork_Gear_Flag;         //�����ʻ��־λ
extern  int8    FrontErr;               //ǰ1/3�������(���ڼӼ���
extern  uint16  Dis_Acc_Count;          //������Ƽ��ٱ�
//Angle_Process()
extern  uint8   aim_line;               //�����
extern  uint8   speed_line;             //���ȡֵ��
extern  uint8   stright_speed_line;     //ֱ��������
extern  uint8   circle_aim_line;        //Բ���Ĵ����
extern  uint8   prospect_row;           //ǰհλ��
extern  uint8   aim_line1;
extern  uint8   speedline_err_abs;

//ELC
extern  int16   sumOutside, subOutside; //������� ����
extern  int16   sumInside, subInside;   //����ڲ�� �ڲ��
extern  float   ELCErr;                 //������
//Others
extern  uint8   Beep_Flag;              //���������ر�־λ
extern  uint8   Ramp_Flag;              //�µ�����־λ
extern  uint8   Ramp_TimeCount;         //�µ����ʱ��
extern  uint8   Gyro_Start_Flag;        //���������Ǳ�־λ(һֱ��
extern  uint8   Gyro_Integral;          //�����ǿ�ʼ���ֱ�־λ
extern  uint8   ELC_ClaerGuiyi_Flag;    //��Ź�һ����׼ֵ��ر�־λ
extern  int16   Attitude_Err;           //������ת�����
extern  uint8   Gyro_Repair_End_Flag;   //�����ǳ�����־λ
extern  uint8   Gyro_StartIdOutCir_Flag;//�����Ǹ�����־λ��ʼʶ�����
extern  uint8   Gyro_TimeOutCir_Flag;   //�����Ǹó����˱�־λ
extern  uint8   Gyro_Trans_Flag;        //����ƽ�Ʊ�־λ
extern  uint8   Gyro_OutCircle_Flag;    //�����ǳ�����־λ
extern  uint8   ELC_Circle_Flag;        //����жϻ�����־λ
extern  uint8   Car_Protect_Flag;       //ͣ��������־λ
extern  uint8   Car_Protect;            //ͣ������״̬
extern  uint8   ELC_Protect_Count;      //��ų�����·����
extern  uint8   ELC_Protect_State;      //��ų�����·������־λ
extern  float   OutCircle_Inertial;     //������ƽ�����
extern  int16   OutCircle_InertialCount;//������ƽ����Ǽ���
extern  int16   OutCircle_Time;         //���������ʱ��

/*****��־λ*****/
extern  uint8   Photo_Finsh_Flag;       //����ͷ������ɱ�־λ
extern  uint8   Car_State_Flag;         //��ǰ״̬
extern  uint8   Fork_Road_Count;        //�ڼ��ν��������һ�߱�־λ
extern  uint8   Fork_Road_Step;
//Others
extern  uint8   Out_Garage;             //�����־λ
extern  uint8   Out_Garage_Dir;         //���ⷽ��
extern  uint8   Gear_Flag;              //����ȫ�ֱ�־λ
extern  uint8   Car_AdvanceX_Flag;      //ǰ��һ�ξ����־λ
extern  uint8   Car_AdvanceY_Flag;      //ǰ��һ�ξ����־λ
extern  uint8   Car_Turn_Flag;          //ת��һ���Ƕȱ�־λ
//Useless


/*****����*****/
extern  uint16  System_Time;            //ϵͳ����ʱ��
extern  uint32  Tim_Count;              //��¼����ʱ��
extern  uint8   PID_Count;              //PID�жϼ���
extern  uint8   Collection_Count;       //�ɼ��жϼ���
extern  uint8   Screen_Slow_Start;      //��ʱ1s������Ļ��־λ
extern  int8    KEY_Change_Count;       //��������
extern  uint8   KEY_Change_Param;       //��������ѡ����
extern  uint16  SechErr[41];            //Sech(Err)���0-40��Ӧ��0-6, ���Ŵ�10000��

/**********************OTHER***********************/

#endif  /* CODE_DEFINE_H_ */
