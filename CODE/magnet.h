/*
 *  magnet.h
 *
 *  Created on: 2021��1��10��
 *      Author: LBQ
 */

#ifndef _myadc_h
#define _myadc_h

#include "MY_Bsp.h"

/*
 ||-----------------------------��-- --��------------------------------||
 ||---------------------------��---------��----------------------------||
 ||-------------------------��-------------��--------------------------||
 ||---����1�����--------2------------------2--------�Ҳ��1�����---||
 ||----------------------��---------------------��---------------------||
 ||--------------------��--------------------------��------------------||
 ||-----------------��--------------------------------��---------------||
 ||---LLADC0--------------LADC1--------------RADC2------------RRADC3---||
 */

#define LLADC_PIN       ADC_IN9_B1      //����1����У���ֱ����
#define LADC_PIN        ADC_IN6_A6      //����2����У��������н�Լ30��
#define RADC_PIN        ADC_IN8_B0      //�Ҳ��2����У��������н�Լ30��
#define RRADC_PIN       ADC_IN4_A4      //�Ҳ��1����У���ֱ����
//#define Voltage_PIN     ADC_IN9_B1      //��ص�ѹ

#define NUM     4       //��и���
#define Times   10      //�˲����
#define NM      3       //�˲������������

extern  uint16  elc_tmp[NUM][3];        //�ݴ�ԭʼ�ɼ�ֵ
extern  uint16  ELC_Value[NUM];         //�������ƽ��ֵ
extern  uint16  ELC_Slide[NUM][NM];     //�洢�����ƽ�����ֵ
extern  uint16  ELC_KF[NUM];            //�������˲����ֵ
extern  uint16  ELC_Guiyi[NUM];         //��й�һֵ
//extern  float   Battery;              //��ص�ѹ

extern  uint16  MagneticField;          //��������ǿ��
extern  uint8   MaxELCNum;              //���ֵ������
extern  uint16  MaxELC;                 //�����ֵ
extern  uint16  MaxELC_Guiyi, MaxELC_Guiyi_Old; //������ֵ

typedef struct
{
    uint16  ELC_Input;              //����ֵ
    uint16  Priori_Estimation;      //�������
    uint16  Posterior_Estimation;   //�������
    int16   Priori_Convariance;     //���鷽��
    int16   Posterior_Convariance;  //���鷽��
    float   KalmanGain;             //����������
    uint16  Q;                      //��������Э����
    uint16  R;                      //������������Э����
}KFPTypeDef_t;   //�ø���������

extern KFPTypeDef_t ELC_KFP0, ELC_KFP1, ELC_KFP2, ELC_KFP3;

extern  void Magnet_ADC_Init(void);
extern  void ELC_Original(void);
extern  void ELC_Get(void);
extern  void ELC_Filter(void);
extern  void ELC_Analyse(void);
extern  void Max_Sample(void);
extern  void Magnet_KalmanFilter(KFPTypeDef_t *kfp);
extern  void Magnet_KalmanFilter_Init(KFPTypeDef_t *kfp);
extern  void Bubble_Sort(uint16 arr[], uint8 len);
extern  uint16 GetNormalizedADValue(uint16 ADinput, uint16 Min_val, uint16 Max_val, uint16 Normalize_MIN, uint16 Normalize_MAX);
extern  void InductorNormal(void);

void Guiyi(void);
void Bizhifa(void);

#endif /* CODE_myadc_H_ */
