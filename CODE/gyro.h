/*
 *  gyro.h
 *
 *  Created on: 2021��1��10��
 *      Author: LBQ
 */

#ifndef GYRO_H_
#define GYRO_H_

#include "MY_Bsp.h"
#include "SEEKFREE_ICM20602.h"
#include "SEEKFREE_IIC.h"

typedef struct
{
    int16   x;
    int16   y;
    int16   z;
}ICMDATA;

typedef struct
{
    ICMDATA accdata;
    ICMDATA gyro;
}ICM20602;

typedef struct
{
    float   x;
    float   y;
    float   z;
}ICMDATA_Treated;

typedef struct
{
  ICMDATA_Treated  accdata; //���ٶȼ�
  ICMDATA_Treated  gyro;    //���ٶ�
}ICM20602_Treated;

extern ICM20602 ICM_Offset;                 //��Ưֵ
extern ICM20602 ICM_State;                  //ԭʼֵ
extern ICM20602_Treated ICM_Treated;        //�����������������

extern  uint8   ICM20602_Offset_Finished;   //��������ƫ������ɱ�־λ
extern  uint8   Offect_Count;               //��ƫ�ɼ�����Ч����
extern  uint8   Offect_Time;                //��ƫ�ɼ�������
extern  int32   offect_temp6;
extern  int32   data_temp6;

extern  int16   ICM_TreatedGyroZ2;
extern  float   Gyro_Z_Last[3];             //�������ϴ�ֵ (0�Ǳ���1���ϴ�

extern  int16   GYRO_Z_BUF[3];

extern  float   Gyro_Z_FilterLast[3];

extern  int32   Attitude_Angel_X2;
extern  float   GyroZProtect;
extern  int16   Attitude_Yaw;
extern  double  Attitude_Angel_X;

extern  void Gyro_Init(void);
extern  void Gyro_Type_Init(void);
extern  void ICM20602_Offset(void);
extern  void Gyro_Offset(void);
extern  void Gyro_Data_Filter(void);
extern  void Get_Attitude(void);
extern  void Get_Attitude_Kalman(void);
extern  void KalmanFilter(float ACC_Angle,float Gyro_y);
extern  void IMUupdate(float gx, float gy, float gz, float ax, float ay, float az);

extern  void Gyro_Data_Filter2(void);
extern  void Get_Attitude2(void);

#endif /* CODE_GYRO_H_ */
