/*
 *  pid.h
 *
 *  Created on: 2021��1��10��
 *      Author: LBQ
 */
#ifndef _PID_H_
#define _PID_H_

#include "MY_Bsp.h"

//Structure
typedef struct {
    float   Now_Val;            //��ǰֵ
    float   Last_Val;           //�ϴ�ֵ
    float   EX_Val;             //����ֵ

    float   Err_Now;            //��ǰ���
    float   Err_ABS;            //��ǰ������ֵ
    float   Err_Last;           //�ϴ����
    float   Err_LastLast;       //���ϴ����
    float   Err_Sum;            //����ۻ�

    float   Kp;                 //����ϵ��
    float   Ki;                 //����ϵ��
    float   Kd;                 //΢��ϵ��

    float   Output_p;           //���������
    float   Output_i;           //���������
    float   Output_d;           //΢�������
    float   Output_dd;          //�ϴ�΢�������
    float   p_Max;              //����������޷�
    float   i_Max;              //�������޷�
    float   d_Max;              //΢��������޷�
    float   out_Max;            //����޷�
    float   Output;             //���
    float   Output_Last;        //�ϴ����ֵ

    float   DKp;                //��̬KP
} PIDTypeDef_t;

typedef struct {
    int16   Now_Val;            //��ǰ�ٶ�
    int16   EX_Val;             //�����ٶ�
    int16   Err_Now;            //��ǰ���
    int16   Err_ABS;            //��ǰ���
    int16   Err_Last;           //�ϴ����
    int16   Err_LastLast;       //���ϴ����
    int16   Err_Sum;            //����ۻ�
    int16   Kp;                 //����ϵ��
    int16   Ki;                 //����ϵ��
    int16   Kd;                 //΢��ϵ��
    int16   i_Max;              //�������޷�
    int16   Output;             //���ռ�ձ�
    int16   Output_Last;        //�ϴ����ֵ
} Motor_PIDTypeDef_t;
//�������ͺ��ַ��ͱ�������������ٶ�

typedef struct {
    float Rin;
    float LastRin;
    float PerrRin;
    float FOutput;
} FFCTypeDef_t;

//Parameter
extern  Motor_PIDTypeDef_t Mortor1_PID, Mortor2_PID, Mortor3_PID, Mortor4_PID;
extern  PIDTypeDef_t Angle, Gyro_Angle;
extern  FFCTypeDef_t FFC;

#define Param_Kp    0
#define Param_Ki    1
#define Param_Kd    2
#define Param_Kl    3

extern  float   ki_index;  //���ַ��뱶��

//Function
extern  void PID_Init(void);
extern  void PID_Parameter_Init(PIDTypeDef_t *pid);
extern  void Motor_PID_Parameter_Init(Motor_PIDTypeDef_t *pid);

extern  void MortorPID_Parameter_Write(int16 *M1_Param, int16 *M2_Param, int16 *M3_Param, int16 *M4_Param);
extern  void AnglePID_Parameter_Write(float *Param);

extern  void Motor_Realize_PID(Motor_PIDTypeDef_t *pid, uint8 type); //λ��ʽPID(���
extern  void Realize_PID(PIDTypeDef_t *pid);             //λ��ʽPID
extern  void Gyro_Realize_PID(PIDTypeDef_t *pid, float Expect); //λ��ʽPID(������
extern  void DynamicRealize_PID(PIDTypeDef_t *pid);      //λ��ʽ��̬PID

extern  void Incremental_PID(PIDTypeDef_t *pid);         //����ʽPID
extern  void Nonlinear_Realize_PID(PIDTypeDef_t *pid);   //������PID
extern  void Changable_PID(PIDTypeDef_t *pid);           //�����PID
extern  void DA_Incremental_PID(PIDTypeDef_t *pid);      //΢������ʽ����ʽPID
extern  void FeedforwardController(FFCTypeDef_t *pid);   //ǰ����������

#endif /* CODE_PID_H_ */
