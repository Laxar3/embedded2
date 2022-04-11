/*
 *  anotc.h
 *
 *  Created on: 2021��1��10��
 *      Author: LBQ
 */

#include "anotc.h"

#define UserDataLen 8

uint8_t waveform[6 + UserDataLen] = {0};     // ����֡����

/*
 * @name:       void Wireless_Send(void)
 * @function:   Wireless_Send
 * @param:      none
 * @return:     none
 * @notion:     V7
 * @notion:     ������ߴ���һ�η���������ò�Ҫ����30�ֽ�
 */
void Wireless_Send(void)
{
//    uint8_t waveform[6 + UserDataLen] = {0};    // ����֡����
    uint8_t _cnt = 0;

    memset(waveform, 0, sizeof(waveform));

    waveform[_cnt++] = 0xAA;        // ֡ͷ
    waveform[_cnt++] = 0xFF;        // Ŀ���ַ
    waveform[_cnt++] = 0xF1;        // ������ID
//    waveform[_cnt++] = sizeof(waveform) - 6;  // ��Ч���ݳ���
//    waveform[_cnt++] = UserDataLen;
    waveform[_cnt++] = 0;

    int16_t UserData_1 = (int16_t)(Mortor1.Speed_Read);
    int16_t UserData_2 = (int16_t)(Mortor2.Speed_Read);
    int16_t UserData_3 = (int16_t)(Mortor3.Speed_Read);
    int16_t UserData_4 = (int16_t)(Mortor4.Speed_Read);

//    int32_t UserData_1 = (int32_t)(Gyro_Z_FilterLast[0] * 1000.0f);

    //������ʹ��С��ģʽ, ���ֽ���ǰ��
//    waveform[_cnt++] = int8;
//    waveform[_cnt++] = BYTE0(int16);
//    waveform[_cnt++] = BYTE1(int16);
//    waveform[_cnt++] = BYTE0(int32);
//    waveform[_cnt++] = BYTE1(int32);
//    waveform[_cnt++] = BYTE2(int32);
//    waveform[_cnt++] = BYTE3(int32);
//    waveform[_cnt++] = BYTE0(float * 100.000f);
//    waveform[_cnt++] = BYTE1(float * 100.000f);
//    waveform[_cnt++] = BYTE2(float * 100.000f);
//    waveform[_cnt++] = BYTE3(float * 100.000f);

    waveform[_cnt++] = BYTE0(UserData_1);   // ��������
    waveform[_cnt++] = BYTE1(UserData_1);
//    waveform[_cnt++] = BYTE2(UserData_1);
//    waveform[_cnt++] = BYTE3(UserData_1);

    waveform[_cnt++] = BYTE0(UserData_2);
    waveform[_cnt++] = BYTE1(UserData_2);

    waveform[_cnt++] = BYTE0(UserData_3);
    waveform[_cnt++] = BYTE1(UserData_3);

    waveform[_cnt++] = BYTE0(UserData_4);
    waveform[_cnt++] = BYTE1(UserData_4);

    waveform[3] = _cnt - 4; // д����Ч�����ֽ���

    uint8_t sumcheck = 0;   // ��У��SC
    uint8_t addcheck = 0;   // ����У��AC
    for(uint8_t i = 0; i < waveform[3] + 4; i++) {
      sumcheck += waveform[i];      // ��֡ͷ��ʼ, һֱ�� data ������, ��ÿһ�ֽڽ����ۼӲ���, ֻȡ��8λ
      addcheck += sumcheck;         // �����У��ʱ, ÿ����һ�ֽڵļӷ�����, ͬʱ����һ�� sumcheck ���ۼӲ���, ֻȡ��8λ
    }
    waveform[_cnt++] = sumcheck;
    waveform[_cnt++] = addcheck;

    seekfree_wireless_send_buff(waveform, sizeof(waveform));    //���ڷ�������
}
