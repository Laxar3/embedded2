/*
 *  pid.c
 *
 *  Created on: 2021��1��10��
 *      Author: LBQ
 */

#include "MY_Bsp.h"
#include "define.h"
#include "pid.h"

//PID Statement
Motor_PIDTypeDef_t Mortor1_PID, Mortor2_PID, Mortor3_PID, Mortor4_PID;
PIDTypeDef_t Angle, Gyro_Angle;
FFCTypeDef_t FFC;

float   ki_index = 1.000f;      //���ַ��뱶��
int16   Dead_zone = 15;         //��������
//��������Ӧ��ͨ��ʵ�ʹ����п����̵��������������
//Ҳ���Բ��Ͻ����Ե���ȶ����к󣬴�ʱ���������С��Ϊ��������

/*
 * @name:void PID_Init(void);
 * @function: PID initialize
 * @param:none
 * @return:none
 */
void PID_Init(void)
{
    /* ����� */
    Motor_PID_Parameter_Init(&Mortor1_PID);
    Motor_PID_Parameter_Init(&Mortor2_PID);
    Motor_PID_Parameter_Init(&Mortor3_PID);
    Motor_PID_Parameter_Init(&Mortor4_PID);
    Mortor1_PID.i_Max = Mortor1_PID.i_Max
    = Mortor1_PID.i_Max = Mortor1_PID.i_Max = 1000;

    /* �����ǻ� */
    PID_Parameter_Init(&Gyro_Angle);
    GyroOutPut = 0;

    /* ת�� */
    FusionErr = 0.000f;
    PID_Parameter_Init(&Angle);
    AngleOutPut = 0;
    Angle.i_Max = 400.0f;
    Angle.out_Max = (float)Mortor_RPM_Max;

    /* ǰ������ */
    FFC.Rin = FFC.LastRin = FFC.PerrRin = 0.000f;
    FFC.FOutput = 0.000f;

    /* PID������ʼ��  */
    MortorPID_Parameter_Write(PID1_Parameter_M1, PID1_Parameter_M2, PID1_Parameter_M3, PID1_Parameter_M4);
    AnglePID_Parameter_Write(Angle1_PID1_40_Parameter);
}

/*
 * @name:void Motor_Realize_PID(PIDTypeDef_t *pid);
 * @function: λ��ʽPID����
 * @param:none
 * @return:none
 */
void Motor_Realize_PID(Motor_PIDTypeDef_t *pid, uint8 type)
{
    int16 Mid_Err = 3;      //�е����
    float Kif = 0.0f;       //Ki
    float Online_K = 1.070f;

//    if (Mortor1.Speed_Idealy == 0) {
        if (type == 1) {
            Kif = 4.8289;
        } else if (type == 2) {
            Kif = 5.2741;
        } else if (type == 3) {
            Kif = 4.9904;
        } else if (type == 4) {
            Kif = 5.1102;
        }
//    } else {
//        if (type == 1) {
//            Kif = 5.5101;
//        } else if (type == 2) {
//            Kif = 4.6743;
//        } else if (type == 3) {
//            Kif = 4.9406;
//        } else if (type == 4) {
//            Kif = 4.3160;
//        }
//    }

    /* �����ȡ */
    pid->Err_Now = pid->EX_Val - pid->Now_Val;    //���㵱ǰ���
    pid->Err_ABS = ABS(pid->Err_Now);

    /* ����޷� */
    if(pid->Err_ABS > 64) {
        pid->Err_Now = pid->Err_Now >  64 ?  64 : pid->Err_Now;
        pid->Err_Now = pid->Err_Now < -64 ? -64 : pid->Err_Now;
    }

    pid->Err_ABS = ABS(pid->Err_Now);
    pid->Err_Sum += pid->Err_Now;

    /* �����޷� */
    if (ABS(pid->Err_Sum) > pid->i_Max) {
        if (pid->Err_Sum > 0) {
            pid->Err_Sum = pid->i_Max;
        } else {
            pid->Err_Sum = -pid->i_Max;
        }
    }

    /* ר��PID */
    //ƫ���ڳ���ƫ�����ֵ����ķ���仯(ƫ��Խ��Խ��), ����ƫ��һֱΪĳһ�̶�ֵ
    if ((pid->Err_Now * (pid->Err_Now - pid->Err_Last) > 0 &&
            pid->Err_Last * (pid->Err_Last - pid->Err_LastLast) > 0) ||
            (pid->Err_Now - pid->Err_Last) == 0) {
        if (pid->Err_ABS >= Mid_Err) {
            pid->Output = pid->Kp * pid->Err_Now
                        + pid->Err_Sum * Kif
                        + pid->Kd * (pid->Err_Now - pid->Err_Last);
            pid->Output = pid->Output * Online_K;
        }
        //ƫ���������ֵ����ķ���仯, ����ƫ�����ֵ�������Ǻܴ�
        else if (pid->Err_ABS < Mid_Err) {
            pid->Output = pid->Kp * pid->Err_Now
                        + pid->Err_Sum * Kif
                        + pid->Kd * (pid->Err_Now - pid->Err_Last);
        }
    }
    //ƫ��ľ���ֵ���С�ķ���仯
//        else if(pid->Err_Now * (pid->Err_Now - pid->Err_Last) < 0 &&
//                 (pid->Err_Now - pid->Err_Last) * (pid->Err_Last - pid->Err_LastLast) > 0) {
//            //��ʱ���ֿ�����������伴��
//        }
    //ƫ��ڼ���״̬
    else if(pid->Err_Now * (pid->Err_Now - pid->Err_Last) < 0 &&
             ((pid->Err_Now - pid->Err_Last) * (pid->Err_Last - pid->Err_LastLast) < 0)) {

        if (pid->Err_Now > Mid_Err || pid->Err_Now < -Mid_Err) {
            pid->Output = pid->Kp * pid->Err_Now
                        + pid->Err_Sum * Kif
                        + pid->Kd * (pid->Err_Now - pid->Err_Last);
            pid->Output = pid->Output * Online_K;
        } else {
            pid->Output = pid->Kp * pid->Err_Now
                        + pid->Err_Sum * Kif
                        + pid->Kd * (pid->Err_Now - pid->Err_Last);
        }
    }
    //�������
    else {
        pid->Output = pid->Kp * pid->Err_Now
                    + pid->Err_Sum * Kif
                    + pid->Kd * (pid->Err_Now - pid->Err_Last);
    }

    /* ����޷� */
    pid->Output = pid->Output > Mortor_PWM_Max ? Mortor_PWM_Max : pid->Output;
    pid->Output = pid->Output < Mortor_PWM_Min ? Mortor_PWM_Min : pid->Output;

    /* �����ϴ�ֵ */
    pid->Err_Last = pid->Err_Now;       //�����ϴ����
    pid->Err_LastLast = pid->Err_Last;
    pid->Output_Last = pid->Output;
}

/*
 * @name:void Realize_PID(PIDTypeDef_t *pid);
 * @function: λ��ʽPID����(�ǶȻ�
 * @param:none
 * @return:none
 * @notion: P����I����D΢��
 */
void Realize_PID(PIDTypeDef_t *pid)
{
    float   StaticDif_Err = 3.0f;       //����(���)
    float   StaticDif_Out = 3.0f;       //�������
    float   Lpf1Factor_d = 0.700f;      //΢�����ͨ�˲�ϵ��
    float   Lpf1Factor_Out = 0.850f;    //������ͨ�˲�ϵ��
    float   Online_K = 1.075f;
    float   Offine_K = 0.65f;
    float   S_Err = 20.0f;              //С���
    float   Mid_Err = 35.0f;            //�е����
    float   L_Err = 75.0f;              //�����

    pid->Err_Now = FusionErr;
    pid->Err_ABS = fabsf(pid->Err_Now);

    /* ����޷� */
//    if(pid->Err_ABS > 45) {
//        pid->Err_Now = pid->Err_Now >  45 ?  45 : pid->Err_Now;
//        pid->Err_Now = pid->Err_Now < -45 ? -45 : pid->Err_Now;
//    }

    /* ����Сʱȡ�����(��������) */
    if(pid->Err_ABS < StaticDif_Err) {
        pid->Err_Now = 0;
    }

    pid->Err_ABS = fabsf(pid->Err_Now);
    pid->Err_Sum += pid->Err_Now;

    /* ������Ļ��ʾ��ǰ״̬ */
    if(pid->Err_Now < -8.0f) {
        Car_State_Flag = 4;         //��ת
    } else if(pid->Err_Now > 8.0f) {
        Car_State_Flag = 5;         //��ת
    } else {
        Car_State_Flag = 1;
    }

    /* ״̬�л��������� */
    //���л�PIDģʽ�����������������Ա�����ֱ�

    /* ����ʽ���ַ��� */
//    if(pid->Err_ABS > 30 & pid->Err_ABS < 35) {
//        ki_index = 0.600f;
//    } else if(pid->Err_ABS > 25 & pid->Err_ABS < 30) {
//        ki_index = 0.900f;
//    } else {
//        ki_index = 1.000f;
//    }

    /* ������������ */
//    if(pid->Err_ABS > 35) {
//        ki_index = 0.000f;
//    }

    /* ���ٻ��� */

    /* ���ֿ����� */
    pid->Err_Sum = pid->Err_Sum >  pid->i_Max ?  pid->i_Max : pid->Err_Sum;
    pid->Err_Sum = pid->Err_Sum < -pid->i_Max ? -pid->i_Max : pid->Err_Sum;
//    pid->Output_i = pid->Output_i >  pid->i_Max ?  pid->i_Max : pid->Output_i;
//    pid->Output_i = pid->Output_i < -pid->i_Max ? -pid->i_Max : pid->Output_i;

    /* ����ȫ΢��(΢����) */
    pid->Output_d = pid->Kd * (pid->Err_Now - pid->Err_Last) * Lpf1Factor_d + pid->Output_dd * (1.000f - Lpf1Factor_d);

    if (isnanf(pid->Output_d) || isinff(pid->Output_d)) {
        if (isnanf(pid->Output_dd) || isinff(pid->Output_dd)) {
            pid->Output_d = 0;
        } else {
            pid->Output_d = pid->Output_dd;
        }
    }

    pid->Output_dd = pid->Output_d;

    /* PID���� */
//    pid->Output = pid->Kp * pid->Err_Now
//                    + ki_index * pid->Err_Sum
//                    + pid->Output_d;

    /* ר��PID */
    //Сƫ��
    if (pid->Err_ABS < S_Err) {
        //Сƫ������ ����С, ��С����
        pid->Output = Offine_K * pid->Kp * pid->Err_Now
                    + Offine_K * ki_index * pid->Ki * pid->Err_Sum
                    + Offine_K * pid->Output_d;
    }
    //��ƫ��
    else if (pid->Err_ABS > L_Err) {
        pid->Output = pid->Kp * pid->Err_Now
                    + ki_index * pid->Ki * pid->Err_Sum
                    + pid->Output_d;
    }
    //����ƫ��
    else {
        //ƫ���ڳ���ƫ�����ֵ����ķ���仯(ƫ��Խ��Խ��), ����ƫ��һֱΪĳһ�̶�ֵ
        if (((int16)pid->Err_Now * ((int16)pid->Err_Now - (int16)pid->Err_Last) > 0 &&
                (int16)pid->Err_Last * ((int16)pid->Err_Last - (int16)pid->Err_LastLast) > 0) ||
                ((int16)pid->Err_Now - (int16)pid->Err_Last) == 0) {

            if (pid->Err_Now > Mid_Err || pid->Err_Now < -Mid_Err) {
                pid->Output = Online_K * pid->Kp * pid->Err_Now
                            + Online_K * ki_index * pid->Ki * pid->Err_Sum
                            + Online_K * pid->Output_d;
            }
            //ƫ���������ֵ����ķ���仯, ����ƫ�����ֵ�������Ǻܴ�
            else if (pid->Err_Now < Mid_Err && pid->Err_Now > -Mid_Err) {
                pid->Output = pid->Kp * pid->Err_Now
                            + ki_index * pid->Ki * pid->Err_Sum
                            + pid->Output_d;
            }
        }
        //�������
        else {
            pid->Output = pid->Kp * pid->Err_Now
                        + ki_index * pid->Ki * pid->Err_Sum
                        + pid->Output_d;
        }
    }


    /* ����޷� */
    if (fabsf(pid->Output) > pid->out_Max) {
        pid->Output = pid->Output >  pid->out_Max ?  pid->out_Max : pid->Output;
        pid->Output = pid->Output < -pid->out_Max ? -pid->out_Max : pid->Output;
    }

    /* ����ȫ΢��(���) */
    pid->Output = Lpf1Factor_Out * pid->Output + (1.000f - Lpf1Factor_Out) * pid->Output_Last;

    if (isnanf(pid->Output) || isinff(pid->Output)) {
        if (isnanf(pid->Output_Last) || isinff(pid->Output_Last)) {
            pid->Output = 0;
        } else {
            pid->Output = pid->Output_Last;
        }
    }

    /* �������� */
    if(fabs(pid->Output) < StaticDif_Out) {
        pid->Output = 0.0f;
    }

    AngleOutPut = (int16)(pid->Output);

    /* �����ϴ�ֵ */
    pid->Err_Last = pid->Err_Now;         // �����ϴ����
    pid->Err_LastLast = pid->Err_Last;
    pid->Output_Last = pid->Output;
}

/*
 * @name:void Realize_PID(PIDTypeDef_t *pid);
 * @function: λ��ʽPID����(������
 * @param:none
 * @return:none
 */
void Gyro_Realize_PID(PIDTypeDef_t *pid, float Expect)
{
    float StaticDif_Err = 2.0f;     //����(���)
    float StaticDif_Out = 3.0f;

    /* ����д�� */
    AnglePID_Parameter_Write(Gyro_PID_Parameter);

    /* �����ȡ */
    pid->Now_Val = ICM_Treated.gyro.z * Gyro_K;
    pid->EX_Val = (float)Expect;
    pid->Err_Now = pid->EX_Val - (float)pid->Now_Val;
    pid->Err_ABS = fabsf(pid->Err_Now);

    /* ����޷� */

    /* ����Сʱȡ����� */
    if (pid->Err_ABS < StaticDif_Err) {
        pid->Err_Now = 0.0f;
    }

    pid->Err_Sum += pid->Err_Now;

    /* PID���� */
    pid->Output = -(pid->Kp * pid->Err_Now
                    + pid->Ki* ki_index * pid->Err_Sum
                    + pid->Kd * (pid->Err_Now - pid->Err_Last));

    /* ����޷� */

    /* �����һ�׵�ͨ�˲� */
    pid->Output = 0.800f * pid->Output + 0.200f * pid->Output_Last;

    /* �������� */
    if(fabs(pid->Output) < StaticDif_Out) {
        pid->Output = 0.0f;
    }

    GyroOutPut = (int16)(pid->Output);

    /* �����ϴ�ֵ */
    pid->Err_Last = pid->Err_Now;         // �����ϴ����
    pid->Output_Last = pid->Output;
}

/*
 * @name:void DynamicRealize_PID(PIDTypeDef_t *pid);
 * @function: λ��ʽ��̬PID����(�Ǽ��ٶ�
 * @param:none
 * @return:none
 */
void DynamicRealize_PID(PIDTypeDef_t *pid)
{
    float StaticDif_Err = 2.0f;        //����(���)
    float StaticDif_Out = 3.0f;

    /* ����Ԫ�صĲ���д�� */
    AnglePID_Parameter_Write(Angle2_PID1_Parameter);

    /* �����ȡ */
    Sensor_Tracking();

    pid->Err_Now = FusionErr;
    pid->Err_ABS = fabsf(pid->Err_Now);

    /* ����Сʱȡ����� */
    if(pid->Err_ABS < StaticDif_Err) {
        pid->Err_Now = 0.0f;
    }

    /* ����޷� */
//    if(pid->Err_ABS > 45.0f) {
//        pid->Err_Now = pid->Err_Now>  45.0f ?  45.0f : pid->Err_Now;
//        pid->Err_Now = pid->Err_Now< -45.0f ? -45.0f : pid->Err_Now;
//    }

    /* ���㶯̬DKp */
    pid->DKp = 0.000f;
    pid->DKp = 1.0f * pid->Err_Now * pid->Err_Now / pid->Kp + pid->Ki;
    //Pֵ���ֵ�ɶ��κ�����ϵ���˴�P��I����PID���������Ƕ�̬PID����

    /* PID���� */
    pid->Output = 0.000f;
    pid->Output = pid->DKp * pid->Err_Now
                    + pid->Kd * (0.800f * pid->Err_Now + 0.800f * pid->Err_Last);    //ֻ��PD

    /* ����޷� */
    if (fabsf(pid->Output) > pid->out_Max) {
        pid->Output = pid->Output >  pid->out_Max ?  pid->out_Max : pid->Output;
        pid->Output = pid->Output < -pid->out_Max ? -pid->out_Max : pid->Output;
    }

    /* �������� */
    if(fabs(pid->Output) < StaticDif_Out) {
        pid->Output = 0.0f;
    }

    AngleOutPut = (int16)(pid->Output);

    /* �����ϴ�ֵ */
    pid->Err_Last = pid->Err_Now;
}


/*
 * @name:void MortorPID_Parameter_Write(float *Mx_Param);
 * @function:PID Parameter Write
 * @param:parameter
 * @return:none
 */
void MortorPID_Parameter_Write(int16 *M1_Param, int16 *M2_Param, int16 *M3_Param, int16 *M4_Param)
{
    Mortor1_PID.Kp = M1_Param[Param_Kp];
    Mortor1_PID.Ki = M1_Param[Param_Ki];
    Mortor1_PID.Kd = M1_Param[Param_Kd];

    Mortor2_PID.Kp = M2_Param[Param_Kp];
    Mortor2_PID.Ki = M2_Param[Param_Ki];
    Mortor2_PID.Kd = M2_Param[Param_Kd];

    Mortor3_PID.Kp = M3_Param[Param_Kp];
    Mortor3_PID.Ki = M3_Param[Param_Ki];
    Mortor3_PID.Kd = M3_Param[Param_Kd];

    Mortor4_PID.Kp = M4_Param[Param_Kp];
    Mortor4_PID.Ki = M4_Param[Param_Ki];
    Mortor4_PID.Kd = M4_Param[Param_Kd];
}

/*
 * @name:void AnglePID_Parameter_Write(float *Mx_Param);
 * @function:PID Parameter Write
 * @param:parameter
 * @return:none
 */
void AnglePID_Parameter_Write(float *Param)
{
    Angle.Kp        = Param[Param_Kp];
    Angle.Ki        = Param[Param_Ki];
    Angle.Kd        = Param[Param_Kd];
    Angle.out_Max   = Param[Param_Kl];
}

/*
 * @name:void PID_Parameter_Init(float *Mx_Param);
 * @function:PID Parameter Write
 * @param:parameter
 * @return:none
 */
void PID_Parameter_Init(PIDTypeDef_t *pid)
{
    pid->Now_Val        = 0.0f;
    pid->EX_Val         = 0.0f;
    pid->Err_Now        = 0.0f;
    pid->Err_ABS        = 0.0f;
    pid->Err_Last       = 0.0f;
    pid->Err_LastLast   = 0.0f;
    pid->Err_Sum        = 0.0f;
    pid->Kp             = 0.0f;
    pid->Ki             = 0.0f;
    pid->Kd             = 0.0f;
    pid->Output_p       = 0.0f;
    pid->Output_i       = 0.0f;
    pid->Output_d       = 0.0f;
    pid->Output_dd      = 0.0f;
    pid->Output         = 0.0f;
    pid->Output_Last    = 0.0f;
}

void Motor_PID_Parameter_Init(Motor_PIDTypeDef_t *pid)
{
    pid->Now_Val        = 0;
    pid->EX_Val         = 0;
    pid->Err_Now        = 0;
    pid->Err_ABS        = 0;
    pid->Err_Last       = 0;
    pid->Err_LastLast   = 0;
    pid->Err_Sum        = 0;
    pid->Kp             = 0;
    pid->Ki             = 0;
    pid->Kd             = 0;
    pid->Output         = 0;
    pid->Output_Last    = 0;
}

//////////////////////////////////////////////////////////////////////
////////////////////////////////û�õ�////////////////////////////////
//////////////////////////////////////////////////////////////////////



/*
 * @name:void Incremental_PID(PIDTypeDef_t *pid);
 * @function: ����ʽPID����
 * @param:none
 * @return:none
 */
void Incremental_PID(PIDTypeDef_t *pid)
{
    float StaticDif_Err = 1.0f;     //����(���)
    float StaticDif_Out = 1.0f;     //����

    /* �����ȡ */
    pid->Err_Now = pid->EX_Val - pid->Now_Val;    //���㵱ǰ���
    pid->Err_ABS = ABS(pid->Err_Now);

    /* ����Сʱȡ����� */
    if(pid->Err_ABS < StaticDif_Err) {
        pid->Err_Now = 0;
    }

    /* �ٶ�����޷� */
    if(pid->Err_ABS > 64) {
        pid->Err_Now = pid->Err_Now >  64 ?  64 : pid->Err_Now;
        pid->Err_Now = pid->Err_Now < -64 ? -64 : pid->Err_Now;
    }

    /* PID���� */
    pid->Output += pid->Kp * (pid->Err_Now - pid->Err_Last)
                      + pid->Ki * (pid->Err_Now)
                      + pid->Kd * (pid->Err_Now - 2 * pid->Err_Last + pid->Err_LastLast);

    //���Դ���BangBang_PID

    /* ����޷� */
    pid->Output = pid->Output > Mortor_PWM_Max ? Mortor_PWM_Max : pid->Output;
    pid->Output = pid->Output < Mortor_PWM_Min ? Mortor_PWM_Min : pid->Output;

    /* �������� */
    if(fabs(pid->Output) < StaticDif_Out) {
        pid->Output = 0.0f;
    }

    /* �����ϴ�ֵ */
    pid->Err_Last = pid->Err_Now;       //�����ϴ����
    pid->Err_LastLast = pid->Err_Last;  //�������ϴ����
}

/*
 * @name:void Nonlinear_Realize_PID(PIDTypeDef_t *pid);
 * @function: ������PID����
 * @param:none
 * @return:none
 */
void Nonlinear_Realize_PID(PIDTypeDef_t *pid)
{
    uint16  errabs = 0;
    float   e = 2.71828183f;
    int8    Nonlinear_Kp1 = 0;
    int8    Nonlinear_Kd1 = 0;
    int8    Nonlinear_Kd2 = 1;
    float   Nonlinear_Kd3 = 0.15f;

    int8    StaticDif_Out = 1;     //����(���)

    /* ����Ԫ�صĲ���д�� */
//    Angle_ElementBase_WritePID();

    /* �����ȡ */
    Angle_Part_Process();

    pid->Err_Now = AngleErr;
    pid->Err_ABS = fabsf(pid->Err_Now);
    errabs = (uint16)pid->Err_ABS;

    /* ����޷� */
    if(pid->Err_ABS > 45) {
        pid->Err_Now = pid->Err_Now>= 45? 45:pid->Err_Now;
        pid->Err_Now = pid->Err_Now<=-45?-45:pid->Err_Now;
    }

    /* PID���� */
    pid->Output = -(Nonlinear_Kp1 + pid->Kp * (float)(10000 - SechErr[errabs]) / 10000.0f
                 + pid->Ki * (SechErr[errabs] / 10000.0f)
                 + Nonlinear_Kd1 + pid->Kd / (1.000f + Nonlinear_Kd2 * pow(e, Nonlinear_Kd3 * (Nonlinear_Kd3 * pid->Err_Now))));

    /* ����޷� */
    pid->Output = pid->Output >  pid->out_Max ?  pid->out_Max : pid->Output;
    pid->Output = pid->Output < -pid->out_Max ? -pid->out_Max : pid->Output;

    /* �������� */
    if(fabsf(pid->Output) < StaticDif_Out) {
        pid->Output = 0;
    }

    /* �Լ����� */
    AngleOutPut = (int16)(0.8f * pid->Output + 0.2f * AngleOutPut);     //Angle_Last
}

/*
 * @name:void Changable_PID(PIDTypeDef_t *pid);
 * @function: �����PID
 * @param:none
 * @return:none
 * @notion:e��iС
 */
void Changable_PID(PIDTypeDef_t *pid)
{
    float change_kib = 4;

    ki_index = pid->Ki;

    if (pid->Err_Now +  pid->Err_Last > 0)
    {
        ki_index = (pid->Ki) - (pid->Ki) / (1 + exp(change_kib - 0.2 * fabs(pid->Err_Now)));    //����ֿ���
    }

    pid->Output = pid->Kp * (pid->Err_Now - pid->Err_Last)
                      + pid->Ki * ki_index * (pid->Err_Now)
                      + pid->Kd * (pid->Err_Now - 2 * pid->Err_Last + pid->Err_LastLast);
}

/*
 * @name:void DA_Incremental_PID(PIDTypeDef_t *pid);
 * @function: ΢������ʽ����ʽPID����
 * @param:none
 * @return:none
 */
void DA_Incremental_PID(PIDTypeDef_t *pid)
{
//    float c1, c2, c3, temp;
//
//    float gama = 0.8f; //΢�������˲�ϵ��, ��0~1֮��
//
//    pid->Error_Now = pid->EX_Val - pid->Now_Val;
//
//    temp = gama * pid->Kd + pid->Kp;
//    c3 = pid->Kd / temp;
//    c2 = (pid->Kd +pid->Kp) / temp;
//    c1 = gama * c3;
//
//    pid->DeltaPv = pid->Now_Val - pid->LastDeltaPv;
//
//    pid->Incr_Val = pid->Kp * (pid->Error_Now - pid->Err_Last)
//                      + pid->Ki * pid->Error_Now
//                      + c1 * pid->Error_d + c2 * pid->DeltaPv * c3 * pid->LastDeltaPv;
//
//    pid->Output_Val += pid->Incr_Val;
//
//    pid->LastDeltaPv = pid->DeltaPv;
//    pid->Err_Last = pid->Error_Now;
}

/*
 * @name:void FeedForwardController(FFCTypeDef_t *pid);
 * @function: ǰ����������
 * @param:none
 * @return:none
 */
void FeedforwardController(FFCTypeDef_t *pid)
{
    float FFCa = 1.0f, FFCb = 1.0f;

    pid->FOutput = FFCa * (pid->Rin - pid->LastRin) + FFCb * (pid->Rin - 2 * pid->LastRin + pid->PerrRin);

    pid->PerrRin= pid->LastRin;
    pid->LastRin= pid->Rin;
}
