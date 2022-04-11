/*
 *  define.c
 *
 *  Created on: 2021��1��12��
 *      Author: LBQ
 */

#include "MY_Bsp.h"
#include "define.h"

/**********************PID***********************/
//PIDi_Parameter_Mx[3] = {Kp, Ki, Kd};
//Matlab���� 0.2s
int16   PID1_Parameter_M1[3] = { 327 , 1 , 0 };
int16   PID1_Parameter_M2[3] = { 356 , 1 , 0 };
int16   PID1_Parameter_M3[3] = { 337 , 1 , 0 };
int16   PID1_Parameter_M4[3] = { 345 , 1 , 0 };
//����PID
int16   PID2_Parameter_M1[3] = { 291 , 1 , 0 };
int16   PID2_Parameter_M2[3] = { 247 , 1 , 0 };
int16   PID2_Parameter_M3[3] = { 211 , 1 , 0 };
int16   PID2_Parameter_M4[3] = { 184 , 1 , 0 };

//int16   PID1_Parameter_M1[3] = { 436 , 47 , 23 };
//int16   PID1_Parameter_M1[3] = { 273 , 54 , 21 };
//int16   PID1_Parameter_M2[3] = { 273 , 54 , 21 };
//int16   PID1_Parameter_M3[3] = { 273 , 54 , 21 };
//int16   PID1_Parameter_M4[3] = { 273 , 54 , 21 };

//Anglei_PIDj_Parameter[4] = {Kp, Ki, Kd, Kl};
//Angle1�ǶȻ�

///////////////////////////////////����//////////////////////////////////////////
/* ���� 40 Start_Part,45 PartUsed,15 */
float   Angle1_PID1_40_Parameter[4] = { 0.605f , 0 , 0.235f , 77 };     //����1 40
/* ���� 45 Start_Part,40 PartUsed,15 */
float   Angle1_PID1_45_Parameter[4] = { 0.505f , 0 , 0.115f , 77 };     //����2 45
/* ���� 50 Start_Part,38 PartUsed,15 */
float   Angle1_PID1_50_Parameter[4] = { 0.515f , 0 , 0.085f , 77 };     //����3 50
/* ���� 55 Start_Part,36 PartUsed,15 */
float   Angle1_PID1_55_Parameter[4] = { 0.465f , 0 , 0.075f , 77 };     //����4 55
/* ���� 60 Start_Part,34 PartUsed,15 */
float   Angle1_PID1_60_Parameter[4] = { 0.435f , 0 , 0.055f , 77 };     //����5 60
/* ���� 65 Start_Part,35 PartUsed,15 */
float   Angle1_PID1_65_Parameter[4] = { 0.415f , 0 , 0.045f , 77 };     //����6 65
/* ���� 70 Start_Part,35 PartUsed,15 */
float   Angle1_PID1_70_Parameter[4] = { 0.415f , 0 , 0.045f , 77 };     //����7 70
//�ٶȲ�����������λʱ
float   Angle1_PID1_Parameter[4] = { 0.335f , 0 , 0.155 , 77 };         //����

///////////////////////////////////����//////////////////////////////////////////
/* ���� 35 Start_Part,49 PartUsed,15 */
float   Angle1_PID2_35_Parameter[4] = { 0.565f , 0 , 0.185f , 77 };     //����1  35
/* ���� 40 Start_Part,49 PartUsed,15 */
float   Angle1_PID2_40_Parameter[4] = { 0.555f , 0 , 0.175f , 77 };     //����2  40
/* ���� 45 Start_Part,49 PartUsed,15 */
float   Angle1_PID2_45_Parameter[4] = { 0.795f , 0 , 0.085f , 77 };     //����3  45
/* ���� 50 Start_Part,49 PartUsed,15 */
float   Angle1_PID2_50_Parameter[4] = { 0.880f , 0 , 0.065f , 77 };     //����4  50
/* ���� 55 Start_Part,49 PartUsed,15 */
float   Angle1_PID2_55_Parameter[4] = { 0.815f , 0 , 0.055f , 77 };     //����5  55
/* ���� 60 Start_Part,49 PartUsed,15 */
float   Angle1_PID2_60_Parameter[4] = { 0.755f , 0 , 0.045f , 77 };     //����6  60
//�ٶȲ�����������λʱ
float   Angle1_PID2_Parameter[4] = { 0.340f , 0 , 0.145f , 77 };        //����

///////////////////////////////////����//////////////////////////////////////////
/* ������ 45 Start_Part,40 PartUsed,15 */
float   Angle1_PID3_45_Parameter[4] = { 0.475f , 0 , 0.165f , 77 };     //������1 45
/* ������ 50 Start_Part,38 PartUsed,15 */
float   Angle1_PID3_50_Parameter[4] = { 0.505f , 0 , 0.085f , 77 };     //������2 50
/* ������ 55 Start_Part,38 PartUsed,15 */
float   Angle1_PID3_55_Parameter[4] = { 0.495f , 0 , 0.085f , 77 };     //������3 55
/* ������ 60 Start_Part,38 PartUsed,15 */
float   Angle1_PID3_60_Parameter[4] = { 0.485f , 0 , 0.065f , 77 };     //������4 60
/* ������ 65 Start_Part,38 PartUsed,15 */
float   Angle1_PID3_65_Parameter[4] = { 0.455f , 0 , 0.055f , 77 };     //������5 65
/* ������ 70 Start_Part,38 PartUsed,15 */
float   Angle1_PID3_70_Parameter[4] = { 0.455f , 0 , 0.055f , 77 };     //������6 70
//�������ٶȲ�����������λʱ
float   Angle1_PID3_Parameter[4] = { 0.435f , 0 , 0.255f , 77 };        //������
//�뻷 45
float   Angle1_PID4_45_Parameter[4] = { 0.385f , 0 , 0.185f , 77 };     //�뻷 45
//�뻷 50
float   Angle1_PID4_50_Parameter[4] = { 0.365f , 0 , 0.165f , 77 };     //�뻷 50
//�뻷 55
float   Angle1_PID4_55_Parameter[4] = { 0.525f , 0 , 0.115f , 77 };     //�뻷 55

///////////////////////////////////���//////////////////////////////////////////
float   Angle1_PID6_Parameter[4] = { 0.485f , 0 , 0.285f , 77 };        //��� 40



///////////////////////////////////û�õ�//////////////////////////////////////////
//Angle2�Ǽ��ٶȻ�
float   Angle2_PID1_Parameter[4] = { 80.0f , 6.0f , 2.0f , 1000};

//Gyro_PID_Parameter[3] = {Kp, Ki, Kd};
float   Gyro_PID_Parameter[4] = { 3.0f , 0 , 0 , 1000};

int16   Mortor_PWM_Max =  9500;
int16   Mortor_PWM_Min = -9500;

/**********************CONTROL***********************/

uint8   weight1[60]={                       //0Ϊͼ�����
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         1, 1, 3, 3, 5, 5,10,10,10,10,
        10,10,10,10,10,10,10,10,10,10,
        10,10,10,10,10,10,10,10,10,10,
        10,10,10,10,10, 5, 5, 5, 5, 5,
         3, 3, 3, 1, 1, 1, 0, 0, 0, 0,};    //����    //ע��б�ʱ仯���������,Ҫƽ��

/*****����*****/
int8    Speed_Set_y = 0;            //���������ٶ�
int8    Speed_Set_x = 0;            //�����ٶ�
int8    Speed_Set_c = 0;            //�����ٶ�
int8    Speed_Set_in = 0;           //�뻷�ٶ�
uint8   Speed_Set_y_Flag = 4;       //���������ٶ� ��λ
uint8   Speed_Set_x_Flag = 4;       //�����ٶ� ��λ
uint8   Speed_Set_c_Flag = 4;       //�����ٶ� ��λ
uint8   ELC_Protect_Flag = 0;       //��ų�����·������־λ
int8    Speed_Set = 0;              //�趨�ٶ�
int16   Speed_CircleIn = 0;         //�뻷�ٶ�
uint8   middle_standard = 39;       //����ͷ��ֵ
uint8   Car_Direction = 1;          //ǰ������ ����Ϊ����, ż��Ϊ����
float   AngleErr0 = 0.000f, AngleErr1 = 0.000f, AngleErr2 = 0.000f;
float   AngleErr = 0.000f;          //ͼ�����������
int16   AngleOutPut = 0;            //ת��ת�����
float   FusionErr = 0.000f;         //����ͷ�����ں����
float   FusionErr_Last = 0.000f;    //�ϴδ��ں����
int16   Gyro_K = 2;                 //�����ǷŴ�ϵ��
int16   GyroOutPut = 0;             //�Ǽ��ٶ����
//Angle_Part_Process()
uint8   Start_Part = 45;             //����ͼ�����ƫ����ʼ��
uint8   End_Part = 30;               //����ͼ�����ƫ�������
float   Part_Err[PartUsed] = {0.000f};  //ͼ�񲿷���� 0���õ������
uint8   Improper_Row[PartUsed] = {0};   //���Ʋ����õ�ͼ����
uint8   Improper_Row_Count = 0;     //���Ʋ����õ�ͼ��������
//Angle_All_Process()
float   midlinenow = 0.000f;        //ȫͼ�������ĵ�ǰ���
float   midline_f = 0.000f, midline_ff = 0.000f, midline_fff = 0.000f;
float   Slope = 0.000f;             //��С���˷�����ؾ�ֵ(ûɶ����
float   Regression_A = 0.000f, Regression_B = 0.000f;
//Gear
int8    MidlineGear = 0;            //Midline_Change����
int8    SlGear = 0;                 //Speed_Change����
int8    SnGear = 0;                 //Speed_Change_Near����
int8    DisGear = 0;                //Dis_Control����
int8    VrGear = 0;                 //ValidRow_Change����
int8    GearCount = 0;              //ƽ������
int8    Gear = 0;                   //����
uint8   Fork_Count = 0;             //�������
uint8   Fork_Gear_Flag = 0;         //�����ʻ��־λ
int8    FrontErr = 0;               //ǰ1/3�������(���ڼӼ���
uint16  Dis_Acc_Count = 0;          //������Ƽ��ٱ�
//Angle_Process()
uint8   aim_line = 27;              //����� ԭ27
uint8   speed_line = 20;            //���ȡֵ�� ԭ20
uint8   stright_speed_line = 25;    //ֱ�������� ԭ25
uint8   circle_aim_line = 29;       //Բ���Ĵ����
uint8   prospect_row = 0;           //ǰհλ��
uint8   aim_line1 = 0;
uint8   speedline_err_abs = 0;
//ELC
int16   sumOutside = 0, subOutside = 0; //������� ����
int16   sumInside = 0, subInside = 0;   //����ڲ�� �ڲ��
float   ELCErr = 0.000f;            //������
//Others
uint8   Beep_Flag = 0;              //���������ر�־λ
uint8   Ramp_Flag = 0;              //�µ�����־λ
uint8   Ramp_TimeCount = 0;         //�µ����ʱ��
uint8   Gyro_Start_Flag = 1;        //���������Ǳ�־λ(һֱ��
uint8   Gyro_Integral = 0;          //�����ǿ�ʼ���ֱ�־λ
uint8   ELC_ClaerGuiyi_Flag = 0;    //��Ź�һ����׼ֵ��ر�־λ
int16   Attitude_Err = 0;           //������ת�����
uint8   Gyro_Repair_End_Flag = 0;   //������ֹͣ�뻷���߱�־λ
uint8   Gyro_StartIdOutCir_Flag = 0;//�����Ǹ�����־λ��ʼʶ�����
uint8   Gyro_TimeOutCir_Flag = 0;   //�����Ǹó����˱�־λ
uint8   Gyro_Trans_Flag = 0;        //����ƽ�Ʊ�־λ
uint8   Gyro_OutCircle_Flag = 0;    //�����ǳ�����־λ
uint8   ELC_Circle_Flag = 0;        //����жϻ�����־λ
uint8   Car_Protect_Flag = 0;       //ͣ��������־λ
uint8   Car_Protect = 0;            //ͣ������״̬
uint8   ELC_Protect_Count = 0;      //��ų�����·����
uint8   ELC_Protect_State = 0;      //��ų�����·����
float   OutCircle_Inertial = 0;     //������ƽ�����
int16   OutCircle_InertialCount = 0;//������ƽ����Ǽ���
int16   OutCircle_Time = 0;         //���������ʱ��


/*****��־λ*****/
uint8   Photo_Finsh_Flag = 0;       //����ͷ������ɱ�־λ
uint8   Car_State_Flag = 0;         //��ǰ״̬
uint8   Fork_Road_Count = 1;        //�ڼ��ν��������һ�߱�־λ
uint8   Fork_Road_Step = 0;
//Others
uint8   Out_Garage = 1;             //�����־λ
uint8   Out_Garage_Dir = left;      //���ⷽ��
//uint8   Out_Garage_Dir = right;     //���ⷽ��
uint8   Gear_Flag = 0;              //����ȫ�ֱ�־λ
uint8   Car_AdvanceX_Flag = 0;      //ǰ��һ�ξ����־λ
uint8   Car_AdvanceY_Flag = 0;      //ƽ��һ�ξ����־λ
uint8   Car_Turn_Flag = 0;          //ת��һ���Ƕȱ�־λ
//Useless


/*****����*****/
uint16  System_Time = 0;            //ϵͳ����ʱ��
uint32  Tim_Count = 0;              //��¼����ʱ��
uint8   PID_Count = 0;              //PID�жϼ���
uint8   Collection_Count = 0;       //�ɼ��жϼ���
uint8   Screen_Slow_Start = 0;      //��ʱ1s������Ļ��־λ
int8    KEY_Change_Count = 0;       //��������
uint8   KEY_Change_Param = 1;       //��������ѡ����

/**********************OTHER***********************/

uint16  SechErr[41] = {
    10000, 9888, 9566, 9066, 8435, 7723, 6977, 6235, 5522, 4858, 4250,
    3704, 3218, 2789, 2412, 2084, 1799, 1552, 1338, 1153, 993,
    855, 736, 634, 546, 470, 404, 348, 299, 258, 222,
    191, 164, 141, 121, 104,  90,  77,  66,  57,  49};  //Sech(Err)���0-40��Ӧ��0-6, ���Ŵ�10000��
