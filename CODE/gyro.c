/*
 *  gyro.c
 *
 *  Created on: 2021��1��10��
 *      Author: LBQ
 */

#include "MY_Bsp.h"
#include "gyro.h"
#include "SEEKFREE_ICM20602.h"

ICM20602 ICM_Offset;            //��Ưֵ
ICM20602 ICM_State;             //ԭʼ����ֵ
ICM20602_Treated ICM_Treated;   //�����������������

#define AcceRatio   (4096.000f)
#define GyroRatio   (16.384f)
#define ACC_FILTER_NUM  5   // ���ٶȼ��˲����
#define GYRO_FILTER_NUM 3   // �������˲����

uint8 ICM20602_Offset_Finished = 0; //��������ƫ������ɱ�־λ
uint8 Offect_Count = 0;             //��ƫ�ɼ�����Ч����
uint8 Offect_Time = 0;              //��ƫ�ɼ�������
//int32 offect_temp1, offect_temp2, offect_temp3, offect_temp4, offect_temp5;
int32 offect_temp6 = 0;       //��ƫ����
int32 data_temp6 = 0;

float   Gyro_Z_Last[3] = {0.000f};          //�������ϴ�ֵ (0�Ǳ���1���ϴ�

//int16   ACC_X_BUF[ACC_FILTER_NUM], ACC_Y_BUF[ACC_FILTER_NUM], ACC_Z_BUF[ACC_FILTER_NUM];        //�˲���������
//int16   GYRO_X_BUF[GYRO_FILTER_NUM], GYRO_Y_BUF[GYRO_FILTER_NUM];
int16   GYRO_Z_BUF[GYRO_FILTER_NUM];

float   Gyro_Z_FilterLast[3] = {0.000f};    //�������˲����ϴ�ֵ (0�Ǳ���1���ϴ�
                                            //ע��С���������������

int16   ICM_TreatedGyroZ2 = 0;
int32   Attitude_Angel_X2 = 0;
double  Attitude_Angel_X = 0.0000;  //z�����ֵ
int16   Attitude_Yaw = 0;           //z�����ֵ�鵽3600
float   GyroZProtect = 0;

/*
 * @name: void Gyro_Init(void)
 * @function: Gyro_Init
 * @param:none
 * @return:none
 */
void Gyro_Init(void)
{
    uint8 i = 0;

    Gyro_Type_Init();

    icm20602_init_spi();    //��ʼ��ICM20602

    Gyro_Type_Init();

    ICM20602_Offset();      //����ƫ

    for (i = 0; i < 10; i++) {
//        delay_ms(2);            //���жϲɼ�ʱ����ͬ
//        Gyro_Data_Filter();
    }

    for (i = 0; i < 5; i++) {
//        systick_delay_ms(2);           //���жϲɼ�ʱ����ͬ
//        Gyro_Data_Filter();
//        Get_Attitude_Kalman();
    }
}

/*
 * @name: void Gyro_Type_Init(void)
 * @function: Gyro_Type_Init
 * @param:none
 * @return:none
 */
void Gyro_Type_Init(void)
{
    ICM_Offset.accdata.x = ICM_Offset.accdata.y = ICM_Offset.accdata.z = 0;
    ICM_Offset.gyro.x = ICM_Offset.gyro.y = ICM_Offset.gyro.z = 0;

    ICM_State.accdata.x = ICM_State.accdata.y = ICM_State.accdata.z = 0;
    ICM_State.gyro.x = ICM_State.gyro.y = ICM_State.gyro.z = 0;

    ICM_Treated.accdata.x = ICM_Treated.accdata.y = ICM_Treated.accdata.z = 0;
    ICM_Treated.gyro.x = ICM_Treated.gyro.y = ICM_Treated.gyro.z = 0;

    Attitude_Angel_X = 0.0;
    Attitude_Angel_X2 = 0;
    Attitude_Yaw = 0;
}

/*
 * @name: void ICM20602_Offset(void)
 * @function: ICM20602��ƫ
 * @param:none
 * @return:none
 * @notice: ��ƫ����Ҫ��������ֵ���ж�ʱ����ͬ
 */
void ICM20602_Offset(void)
{
    uint8   i = 0;
    uint8   Offect_Degree = 200;
    int8    GyroZ_Range = 16;

    while (!ICM20602_Offset_Finished) {
        if (Offect_Count == 0) {
            ICM_Treated.accdata.x = ICM_Treated.accdata.y = ICM_Treated.accdata.z = 0;
            ICM_Treated.gyro.x = ICM_Treated.gyro.y = ICM_Treated.gyro.z = 0;
            ICM_Offset.accdata.x = ICM_Offset.accdata.y = ICM_Offset.accdata.z = 0;
            ICM_Offset.gyro.x = ICM_Offset.gyro.y = ICM_Offset.gyro.z = 0;
//            offect_temp1 = offect_temp2 = offect_temp3
//            = offect_temp4 = offect_temp5 = 0;
            offect_temp6 = 0;
        }

        for (i = 0; i < MAX(ACC_FILTER_NUM, GYRO_FILTER_NUM); i++) {
            delay_ms(2);            //���жϲɼ�ʱ����ͬ
            Gyro_Data_Filter();
//            Gyro_Data_Filter2();
        }   //��������������

        for (i = 0; i < Offect_Degree + 1; i++) {
            delay_ms(2);            //���жϲɼ�ʱ����ͬ
            Gyro_Data_Filter();
//            Gyro_Data_Filter2();

            if (ABS((int16)(ICM_Treated.gyro.z)) > GyroZ_Range || ABS((int16)(Gyro_Z_Last[1] - ICM_Treated.gyro.z)) > GyroZ_Range) {
                //�����ǰֵ����/���β���������, ����ȥ����
                ICM_Treated.accdata.x = ICM_Treated.accdata.y = ICM_Treated.accdata.z = 0;
                ICM_Treated.gyro.x = ICM_Treated.gyro.y = ICM_Treated.gyro.z = 0;
//                Offect_Degree++;
            } else {
                Offect_Count++;
            }

//            offect_temp1 += ICM_State.accdata.x;      //ʹ��ԭʼֵ
//            offect_temp2 += ICM_State.accdata.y;
//            offect_temp3 += ICM_State.accdata.z;
//            offect_temp4 += ICM_State.gyro.x;
//            offect_temp5 += ICM_State.gyro.y;
//            offect_temp6 += ICM_State.gyro.z;

//            offect_temp1 += ICM_Treated.accdata.x;    //ʹ���˲���ֵ
//            offect_temp2 += ICM_Treated.accdata.y;
//            offect_temp3 += ICM_Treated.accdata.z;
//            offect_temp4 += ICM_Treated.gyro.x;
//            offect_temp5 += ICM_Treated.gyro.y;
            offect_temp6 += (int16)(ICM_Treated.gyro.z);
        }

//        ICM_Offset.accdata.x = offect_temp1 / Offect_Count;
//        ICM_Offset.accdata.y = offect_temp2 / Offect_Count;
//        ICM_Offset.accdata.z = offect_temp3 / Offect_Count;
//        ICM_Offset.gyro.x = offect_temp4 / Offect_Count;
//        ICM_Offset.gyro.y = offect_temp5 / Offect_Count;
        ICM_Offset.gyro.z = offect_temp6 / Offect_Count;

        Attitude_Yaw = Attitude_Angel_X = Attitude_Angel_X2 = 0;
        ICM20602_Offset_Finished = 1;
    }
}

/*
 * @name: void Gyro_Offset(void)
 * @function: ����������ϲ�д�ڳ�ʼ����Ϳ���, ��ֵ����⵼��ֻ�ֿܷ�д
 * @param:none
 * @return:none
 */
void Gyro_Offset(void)
{
    int8 GyroZ_Range = 16;

    if (Offect_Time < 50) {
//        ICM_Offset.accdata.x = offect_temp1 / Offect_Count;
//        ICM_Offset.accdata.y = offect_temp2 / Offect_Count;
//        ICM_Offset.accdata.z = offect_temp3 / Offect_Count;
//        ICM_Offset.gyro.x = offect_temp4 / Offect_Count;
//        ICM_Offset.gyro.y = offect_temp5 / Offect_Count;
        ICM_Offset.gyro.z = offect_temp6 / Offect_Count;

        if (ABS(ICM_Offset.gyro.z) > GyroZ_Range) {
            //��ƫֵ����������\�ز�
            ICM_Offset.accdata.x = ICM_Offset.accdata.y = ICM_Offset.accdata.z = 0;
            ICM_Offset.gyro.x = ICM_Offset.gyro.y = ICM_Offset.gyro.z = 0;
        }

        Offect_Time++;
    }

    if (ICM20602_Offset_Finished == 1) {
        ICM_Treated.accdata.x = ICM_Treated.accdata.y = ICM_Treated.accdata.z = 0;
        ICM_Treated.gyro.x = ICM_Treated.gyro.y = ICM_Treated.gyro.z = 0;
        Attitude_Yaw = Attitude_Angel_X = Attitude_Angel_X2 = 0;
    }   //�ж����ʼ��û���֮ǰ��֮����

    if (Offect_Time >= 50) {
        ICM20602_Offset_Finished = 2;
    }
}

/*
 * @name: void Gyro_Data_Filter(void)
 * @function: ���ݻ����˲�
 * @param:none
 * @return:none
 */
void Gyro_Data_Filter(void)  // �����ǲɼ����ݲ������˲�
{
    uint8 i;
//    int32 temp[6] = {0};
//    int32 temp1 = 0, temp2 = 0, temp3 = 0, temp4 = 0, temp5 = 0;
    data_temp6 = 0;


//    float lpf_factor = 0.300f;    //һ��RC��ͨ�˲����� �����²���ֵ���˲�����е�Ȩ��
                                    //һ�������ǵĵ�ͨ�˲��ľ���ֵ������30-50Hz(��ֹƵ��fc
                                    //lpf_factor = 1.0 / (1.0 + (1.0 / 2Pi * T(s) * fc));
                                    //�˲�ϵ��ԽС, �˲����Խƽ��, ������Խ��
                                    //�����˳�Ƶ�ʸ��ڲ���Ƶ�ʵĶ���֮һ�ĸ���
//    float B[3] = {0.04613f, 0.09226f, 0.04613f};//����IIR�˲�������
//    float A[3] = {1.0000f, -1.30729f, 0.49181f};
//                                                //��Matlab������FilterDesign�������
//                                                //�����Ż���int�ͻ�������λ���ͼӷ���������˷�

    //��ȡԭʼֵ
//    get_icm20602_accdata_spi();     //��ȡ���ٶȼ�����
    get_icm20602_gyro_spi();        //��ȡ����������

    for (i = 0; i < ACC_FILTER_NUM - 1; i++) {
//        ACC_X_BUF[ACC_FILTER_NUM-1-i] = ACC_X_BUF[ACC_FILTER_NUM-2-i];
//        ACC_Y_BUF[ACC_FILTER_NUM-1-i] = ACC_Y_BUF[ACC_FILTER_NUM-2-i];
//        ACC_Z_BUF[ACC_FILTER_NUM-1-i] = ACC_Z_BUF[ACC_FILTER_NUM-2-i];
    }   //���ƾ�ֵ
    for (i = 0; i < GYRO_FILTER_NUM - 1; i++) {
//        GYRO_X_BUF[GYRO_FILTER_NUM-1-i] = GYRO_X_BUF[GYRO_FILTER_NUM-2-i];
//        GYRO_Y_BUF[GYRO_FILTER_NUM-1-i] = GYRO_Y_BUF[GYRO_FILTER_NUM-2-i];
        GYRO_Z_BUF[GYRO_FILTER_NUM-1-i] = GYRO_Z_BUF[GYRO_FILTER_NUM-2-i];
    }

//    ACC_X_BUF[0] = ICM_State.accdata.x; // ���»�����������
//    ACC_Y_BUF[0] = ICM_State.accdata.y;
//    ACC_Z_BUF[0] = ICM_State.accdata.z;
//    GYRO_X_BUF[0] = ICM_State.gyro.x;
//    GYRO_Y_BUF[0] = ICM_State.gyro.y;
    GYRO_Z_BUF[0] = ICM_State.gyro.z;

    for(i = 0; i < ACC_FILTER_NUM; i++) {
//        temp1 += ACC_X_BUF[i];
//        temp2 += ACC_Y_BUF[i];
//        temp3 += ACC_Z_BUF[i];
    }
    for(i = 0; i < GYRO_FILTER_NUM; i++) {
//        temp4 += GYRO_X_BUF[i];
//        temp5 += GYRO_Y_BUF[i];
        data_temp6 += GYRO_Z_BUF[i];
    }

    if (ICM20602_Offset_Finished) {
        //ת��Ϊʵ������ֵ
        //��λg/s
//        ICM_Treated.accdata.x = ((float)temp1 / ACC_FILTER_NUM - ICM_Offset.accdata.x) * 8.0f / AcceRatio;
//        ICM_Treated.accdata.y = ((float)temp2 / ACC_FILTER_NUM - ICM_Offset.accdata.y) * 8.0f / AcceRatio;
//        ICM_Treated.accdata.z = ((float)temp3 / ACC_FILTER_NUM - ICM_Offset.accdata.z) * 8.0f / AcceRatio;
        //�����ǽǶ�ת����
//        ICM_Treated.gyro.x = ((float)temp4 / GYRO_FILTER_NUM - ICM_Offset.gyro.x) * Pi / 180.0f  / GyroRatio;
//        ICM_Treated.gyro.y = ((float)temp5 / GYRO_FILTER_NUM - ICM_Offset.gyro.y) * Pi / 180.0f  / GyroRatio;
        GyroZProtect = 0.000f;
        Gyro_Z_Last[0] = Gyro_Z_FilterLast[0] = 0.000f;
        ICM_Treated.gyro.z = 0.000f;

        GyroZProtect = ((float)data_temp6 / 3.000f - (float)ICM_Offset.gyro.z) * Pi / 180.0f  / GyroRatio;
        Gyro_Z_Last[0] = ((float)data_temp6 / 3.000f - (float)ICM_Offset.gyro.z) * Pi / 180.0f  / GyroRatio;
//        Gyro_Z_FilterLast[0] = Gyro_Z_Last[0];
//        ICM_Treated.gyro.z = Gyro_Z_FilterLast[0];
        Gyro_Z_FilterLast[0] = ((float)data_temp6 / 3.000f - (float)ICM_Offset.gyro.z) * Pi / 180.0f  / GyroRatio;
        ICM_Treated.gyro.z = ((float)data_temp6 / 3.000f - (float)ICM_Offset.gyro.z) * Pi / 180.0f  / GyroRatio;
        /* �˲� */
        //һ��RC��ͨ�˲�
//        Gyro_Z_FilterLast[0] = lpf_factor * Gyro_Z_Last[0] + (1.000f - lpf_factor) * Gyro_Z_FilterLast[1];
//        ICM_Treated.gyro.z = Gyro_Z_FilterLast[0];
        //����IIR�˲���
//        Gyro_Z_FilterLast[0] = (B[0] * Gyro_Z_Last[0] + B[1] * Gyro_Z_Last[1] + B[2] * Gyro_Z_Last[2]
//                                - A[1] * Gyro_Z_FilterLast[1] - A[2] * Gyro_Z_FilterLast[2]) / A[0];
//        ICM_Treated.gyro.z = Gyro_Z_FilterLast[0];
        if (isnanf(Gyro_Z_FilterLast[0]) || isinff(Gyro_Z_FilterLast[0])) {
            if (isnanf(Gyro_Z_FilterLast[1]) || isinff(Gyro_Z_FilterLast[1])) {
                if (isnanf(Gyro_Z_FilterLast[2]) || isinff(Gyro_Z_FilterLast[2])) {
                    if (isnanf(Gyro_Z_Last[0]) || isinff(Gyro_Z_Last[0])) {
                        if (isnanf(Gyro_Z_Last[1]) || isinff(Gyro_Z_Last[1])) {
                            if (isnanf(Gyro_Z_Last[2]) || isinff(Gyro_Z_Last[2])) {
                                if (isnanf(ICM_Treated.gyro.z) || isinff(ICM_Treated.gyro.z)) {
                                    if (isnanf(GyroZProtect) || isinff(GyroZProtect)) {
                                        get_icm20602_gyro_spi();    //�ٴβ�������������
                                        GyroZProtect = ((float)ICM_State.gyro.z / 3.000f - (float)ICM_Offset.gyro.z) * Pi / 180.0f  / GyroRatio;
                                         Gyro_Z_FilterLast[0] = Gyro_Z_FilterLast[1] = Gyro_Z_FilterLast[2] = Gyro_Z_Last[0] = Gyro_Z_Last[1] = Gyro_Z_Last[2] = ICM_Treated.gyro.z = GyroZProtect;
                                        if (isnanf(GyroZProtect) || isinff(GyroZProtect)) {
                                            if (Mortor1.Speed_Idealr > 0) {
                                                Gyro_Z_FilterLast[0] = Gyro_Z_FilterLast[1] = Gyro_Z_FilterLast[2] = Gyro_Z_Last[0] = Gyro_Z_Last[1] = Gyro_Z_Last[2] = ICM_Treated.gyro.z = GyroZProtect = -12.0f;
                                            } else {
                                                Gyro_Z_FilterLast[0] = Gyro_Z_FilterLast[1] = Gyro_Z_FilterLast[2] = Gyro_Z_Last[0] = Gyro_Z_Last[1] = Gyro_Z_Last[2] = ICM_Treated.gyro.z = GyroZProtect = 12.0f;
                                            }
                                        }
                                    } else {
                                        Gyro_Z_FilterLast[0] = Gyro_Z_FilterLast[1] = Gyro_Z_FilterLast[2] = Gyro_Z_Last[0] = Gyro_Z_Last[1] = Gyro_Z_Last[2] = ICM_Treated.gyro.z = GyroZProtect;
                                    }
                                } else {
                                    Gyro_Z_FilterLast[0] = Gyro_Z_FilterLast[1] = Gyro_Z_FilterLast[2] = Gyro_Z_Last[0] = Gyro_Z_Last[1] = Gyro_Z_Last[2] = ICM_Treated.gyro.z;
                                }
                            } else {
                                Gyro_Z_FilterLast[0] = Gyro_Z_FilterLast[1] = Gyro_Z_FilterLast[2] = Gyro_Z_Last[0] = Gyro_Z_Last[1] = Gyro_Z_Last[2];
                                ICM_Treated.gyro.z = Gyro_Z_FilterLast[0];
                            }
                        } else {
                            Gyro_Z_FilterLast[0] = Gyro_Z_FilterLast[1] = Gyro_Z_FilterLast[2] = Gyro_Z_Last[0] = Gyro_Z_Last[1];
                            ICM_Treated.gyro.z = Gyro_Z_FilterLast[0];
                        }
                    } else {
                        Gyro_Z_FilterLast[0] = Gyro_Z_FilterLast[1] = Gyro_Z_FilterLast[2] = Gyro_Z_Last[0];
                        ICM_Treated.gyro.z = Gyro_Z_FilterLast[0];
                    }
                } else {
                    Gyro_Z_FilterLast[0] = Gyro_Z_FilterLast[1] = Gyro_Z_FilterLast[2];
                    ICM_Treated.gyro.z = Gyro_Z_FilterLast[0];
                }
            } else {
                Gyro_Z_FilterLast[0] = Gyro_Z_FilterLast[1];
                ICM_Treated.gyro.z = Gyro_Z_FilterLast[0];
            }
        }
    } else {
//        ICM_Treated.accdata.x = temp1 / ACC_FILTER_NUM;     //�ɼ���������ƫֵ
//        ICM_Treated.accdata.y = temp2 / ACC_FILTER_NUM;
//        ICM_Treated.accdata.z = temp3 / ACC_FILTER_NUM;
//        ICM_Treated.gyro.x = temp4 / GYRO_FILTER_NUM;
//        ICM_Treated.gyro.y = temp5 / GYRO_FILTER_NUM;
        ICM_Treated.gyro.z = data_temp6 / GYRO_FILTER_NUM;
    }

    //�����ϴ�ֵ
    for (i = 0; i < 2; i++) {
        Gyro_Z_Last[i+1] = Gyro_Z_Last[i];
        Gyro_Z_FilterLast[i+1] = Gyro_Z_FilterLast[i];
    }
}

void Gyro_Data_Filter2(void)
{
    get_icm20602_gyro_spi();        //��ȡ����������

    if (ICM20602_Offset_Finished) {
        ICM_TreatedGyroZ2 = (ICM_State.gyro.z - ICM_Offset.gyro.z);
    } else {
        ICM_Treated.gyro.z = ICM_State.gyro.z;
    }
}

/*
 * @name:void Get_Attitude(void)
 * @function: ֱ�ӻ���
 * @param: none
 * @return: none
 */
void Get_Attitude(void)
{
    float Gyro_DeadZone = 0.065f;
    float Gyro_Rate = 1.1557f;

    if ((fabsf(Gyro_Z_FilterLast[0]) - Gyro_DeadZone) > 0.0f) {
        Attitude_Angel_X += Gyro_Z_FilterLast[0];
//        Attitude_Angel_X += ICM_Treated.gyro.z;
        Attitude_Yaw = (int16)(Gyro_Rate * Attitude_Angel_X);
    }

//    if (Attitude_Yaw > 4000) {
//        Attitude_Yaw = 0;
//        Attitude_Angel_X = 0;
//        Gyro_Z_FilterLast[0] = 0;
//    }   //��ֹ���
}

void Get_Attitude2(void)
{
    int16 Gyro_DeadZone = 9;
    float Gyro_Rate = 0.012245f;

    if ((ABS(ICM_TreatedGyroZ2) - Gyro_DeadZone) > 0) {
        Attitude_Angel_X2 += ICM_TreatedGyroZ2;
        Attitude_Yaw = (int16)(Gyro_Rate * (float)Attitude_Angel_X2);
    }
}

/*
 * @name: void KalmanFilter(float ACC_Angle,float Gyro_y);
 * @function: �������˲�
 * @param:none
 * @return:none
 * @notice: �������Բ��ø�
 */
#define Peried 3/500.0f     //��������������
#define Gyro_Q 3.0f         //��������Э����2.0       ԽС����Խ��, ���ټ��ٶȼ�Խ��Խƽ��
#define Gyro_R 1500.0f      //��������Э����5000.0    ԽС���ټ��ٶȼ�Խ��
float Gyro_KalmanGain = 1.000f;    //����������

void KalmanFilter(float ACC_Angle,float Gyro_y)
{
    //�������˲��ֲ�����
    static float Priori_Estimation = 0.000f;     //�������
    static float Posterior_Estimation = 0.000f;  //�������
    static float Priori_Convariance = 0.000f;    //���鷽��
    static float Posterior_Convariance = 0.000f; //���鷽��

    //�������˲�
    //1.ʱ�����(Ԥ��) : X(k|k-1) = A(k,k-1)*X(k-1|k-1) + B(k)*u(k)
    //Ԥ��״̬���̡�Ŀ���� ϵͳ״̬����k-1ʱ�̵�����ֵ �� ϵͳ���� �����kʱ�̵� ϵͳԤ��ֵ��
    //X(k|k-1)������K-1ʱ��Ԥ��ĵ�ǰ״̬���; X(k-1|k-1)��K-1ʱ������ֵ(�����ֵ)
    //A��������X(k|k-1)״̬�µı任���������㷨��״̬��������Ԥ������ݡ���XΪһά����ʱ��A��ֵ��1
    //Bk�������ڿ������ϵı任�����ڴ����ʵ������²�û�п�������; uk�ǵ�ǰ״̬�Ŀ������棬һ��û�����������������Ϊ0
    Priori_Estimation = Posterior_Estimation - Gyro_y * Peried;     //������ƣ����ֻ�ýǶ�
    if (Priori_Estimation != Priori_Estimation) {
        Priori_Estimation = 0.000f;
    }

    //2.��������Э����  : P(k|k-1) = A(k,k-1)*P(k-1|k-1)*A(k,k-1)'+Q(k)
    //Ԥ��Э����̡���Ŀ�ĸ��� k-1ʱ�̵�ϵͳЭ���� Ԥ�� kʱ��ϵͳЭ���
    //P(k|k-1)��kʱ��ϵͳЭ�������; P(k-1|k-1)��k-1ʱ��ϵͳЭ�������
    //Q(k)��ϵͳ����������Э���Э�������ֻҪȷ����һ��ʼ��P0�����涼���Ե��Ƴ��������ҳ�ʼЭ�������PֻҪ����Ϊ0������ȡֵ���˲�Ч��Ӱ���С�����ܺܿ�����
    Priori_Convariance = (float)sqrt( Posterior_Convariance * Posterior_Convariance + Gyro_Q * Gyro_Q );
    if (Priori_Convariance != Priori_Convariance) {
        Priori_Convariance = 0.000f;
    }

    //  ������������ƣ���������
    // 1.���㿨��������  : K(k) = P(k|k-1)*H(k)' / (H(k)*P(k|k-1)*H(k)' + R(k))
    //Ŀ�ĸ��ݣ�kʱ�̣� Э��������Ԥ��ֵ ���� ����������
    //K(k)�ǿ��������棬���˲����м���
    //H(k)�Ƕ����Ԥ����󡣵� Pk|k-1 Ϊһ��һά����ʱ��Hk ��1
    //R(k)�Ƕ������������Э�����������һ����ֵ����Ϊ��֪���������˲�����ע�⣬���ֵ�����С����ʹ�˲�Ч���� ��RkȡֵԽС����Խ�죬���Կ���ͨ��ʵ���ֶ�Ѱ�Һ��ʵ�R��ֵ��������������ʵ���˲���
    Gyro_KalmanGain = (float)sqrt( Priori_Convariance * Priori_Convariance / ( Priori_Convariance * Priori_Convariance + Gyro_R * Gyro_R ) );
    if (Gyro_KalmanGain != Gyro_KalmanGain) {
        Gyro_KalmanGain = 1.000f;
    }

    //2.��������(У��): X(k|k) = X(k|k-1)+K(k)*(Z(k)-H(k)*X(k|k-1))
    //��������ֵ���̣��������˲����������Ŀ�ĸ��� ״̬������Ԥ��ֵ �� ϵͳ����ֵ ����� kʱ��״̬����������ֵ
    //X(k|k)��kʱ��״̬�������Ź���ֵ
    //Z(k)�Ƕ���Ĳ���ֵ
    Posterior_Estimation  = Priori_Estimation + Gyro_KalmanGain * (ACC_Angle - Priori_Estimation );
    if (Posterior_Estimation != Posterior_Estimation) {
        Posterior_Estimation = 0.000f;
    }

    // 3.���º���Э����  : P(k|k) =��I-K(k)*H(k)��*P(k|k-1)
    //����Э����̡�Ŀ��Ϊ���� kʱ�̵�Э������󡣣�Ϊ�õ�k+1ʱ�̵Ŀ��������ֵ��׼����
    //P(k|k)Ϊkʱ��Э������� IΪ��λ����
    //�� Pk|k-1 Ϊһ��һά����ʱ��Hk ��1
    Posterior_Convariance = (float)sqrt(( 1.000f - Gyro_KalmanGain ) * Priori_Convariance * Priori_Convariance );
    if (Posterior_Convariance != Posterior_Convariance) {
        Posterior_Convariance = 0.000f;
    }

    //�õ����սǶ�
    Attitude_Angel_X = Posterior_Estimation;
}

void Get_Attitude_Kalman(void)
{
    KalmanFilter(ICM_Treated.accdata.x*90.0f/8.0f, ICM_Treated.gyro.x/Pi/180.0f);
}

//===============================��Ԫ��===============================//
#define GKp 1.6f //10.0f                    // proportional gain governs rate of convergence to accelerometer/magnetometer
#define GKi 0.001f//1.2f // //0.008f        // integral gain governs rate of convergence of gyroscope biases
#define halfT 0.005f                        // half the sample period �������ڵ�һ��
float Gq0 = 1, Gq1 = 0, Gq2 = 0, Gq3 = 0;   // quaternion elements representing the estimated orientation
float exInt = 0, eyInt = 0, ezInt = 0;      // scaled integral error
/*
 * ��������IMUupdate
 * ����  ����Ԫ�ؽ���ŷ����
 * ����  �������� ���ٶȼ�
 * ���  ����
 * ����  ���ڲ�����
 */
void IMUupdate(float gx, float gy, float gz, float ax, float ay, float az)
{
    float norm;
    float vx, vy, vz;
    float ex, ey, ez;

    // �Ȱ���Щ�õõ���ֵ���
    float q0q0 = Gq0*Gq0;
    float q0q1 = Gq0*Gq1;
    float q0q2 = Gq0*Gq2;
    float q1q1 = Gq1*Gq1;
    float q1q3 = Gq1*Gq3;
    float q2q2 = Gq2*Gq2;
    float q2q3 = Gq2*Gq3;
    float q3q3 = Gq3*Gq3;

    if (ax*ay*az == 0)
    {
        return;
    }

    norm = sqrt(ax*ax + ay*ay + az*az); // acc���ݹ�һ��
    ax = ax / norm;
    ay = ay / norm;
    az = az / norm;

    // estimated direction of gravity and flux (v and w)    �����������������/��Ǩ
    vx = 2*(q1q3 - q0q2);                                   // ��Ԫ����xyz�ı�ʾ
    vy = 2*(q0q1 + q2q3);
    vz = q0q0 - q1q1 - q2q2 + q3q3 ;

    // error is sum of cross product between reference direction of fields and direction measured by sensors
    ex = (ay*vz - az*vy) ;      // �������������õ���־������
    ey = (az*vx - ax*vz) ;
    ez = (ax*vy - ay*vx) ;

    exInt = exInt + ex * GKi;    // �������л���
    eyInt = eyInt + ey * GKi;
    ezInt = ezInt + ez * GKi;

    // adjusted gyroscope measurements
    gx = gx + GKp*ex + exInt;    // �����PI�󲹳��������ǣ����������Ư��
    gy = gy + GKp*ey + eyInt;
    gz = gz + GKp*ez + ezInt;    // �����gz����û�й۲��߽��н��������Ư�ƣ����ֳ����ľ��ǻ����������Լ�

    // integrate quaternion rate and normalise  // ��Ԫ�ص�΢�ַ���
    Gq0 = Gq0 + (-Gq1*gx - Gq2*gy - Gq3*gz)*halfT;
    Gq1 = Gq1 + (Gq0*gx + Gq2*gz - Gq3*gy)*halfT;
    Gq2 = Gq2 + (Gq0*gy - Gq1*gz + Gq3*gx)*halfT;
    Gq3 = Gq3 + (Gq0*gz + Gq1*gy - Gq2*gx)*halfT;

    // normalise quaternion
    norm = sqrt(Gq0*Gq0 + Gq1*Gq1 + Gq2*Gq2 + Gq3*Gq3);
    Gq0 = Gq0 / norm;
    Gq1 = Gq1 / norm;
    Gq2 = Gq2 / norm;
    Gq3 = Gq3 / norm;

//    Attitude_Angel_Y = asin(-2*Gq1*Gq3 + 2*Gq0*Gq2) * 57.3; // pitch
//    Attitude_Angel_X = atan2(2*q2*q3 + 2*q0*q1, -2*q1*q1 - 2*q2*q2 + 1)*57.3; // roll
//    Attitude_Angel_Z = atan2(2*q1*q2 + 2*q0*q3, -2*q2*q2 - 2*q3*q3 + 1)*57.3; // yaw
}

//һ�׻����˲�
//����ļ��ٶ�ֵû���ۻ����, ��ͨ����tan()���Եõ���ǣ� ����������������̫�࣬ ����ֱ��ʹ�ã���Ϊ�������˶�ʱ��������ٶȣ��������ʱ�񶯻�������ٶȵȣ�
//�����Ƕ������Ӱ��С, ���ȸ�, ͨ���Խ��ٶȻ��ֿ��Եõ���ǣ����ǻ�����ۻ������Բ��ܵ���ʹ�� MPU6050 �ļ��ٶȼƻ����������õ���ǣ���Ҫ����
//һ�׻����㷨��˼����Ǹ����ٶȺ������ǲ�ͬ��Ȩֵ�������ǽ�ϵ�һ�𣬽�������

float K1 = 0.100f;  //�Լ��ٶȼ�ȡֵ��Ȩ��
float dt = 0.001f;  //dt��ȡֵΪ�˲�������ʱ��

//angle_ax = atan(ICM_Treated.accdata.x/ICM_Treated.accdata.z)*57.3;     //���ٶȵõ��ĽǶ�
//gy = (float)ICM_Treated.gyro.y/7510.0;       //�����ǵõ��Ľ��ٶ�
//Angle_Pitch = yijiehubu(angle_ax,gy);

float yijiehubu(float angle_m, float gyro_m)    //�ɼ������ĽǶȺͽǼ��ٶ�
{
    float angle = 0.000f;
    angle = K1 * angle_m + (1-K1) * (angle + gyro_m * dt);
    return angle;   //���Լ���pitch(����)��(x), roll(��ת)��(y)
}
