/*
 *  tfminiplus.c
 *
 *  Created on: 2021��1��10��
 *      Author: LBQ
 */

#include "My_Bsp.h"
#include "tfminiplus.h"

// Statement
#define TFMINI_DATA_Len     9
#define TFMINT_DATA_HEAD    (0x59)

uint16_t TFmin_Dist = 0;    // ������Ϣ ��λ cm
uint16_t TFmin_Strength = 0;// �ź�ǿ�� С�� 100 ����� 65535 ʱ, Dist �Ĳ���ֵ����Ϊ�����������0
uint16_t TFmin_Temp = 0;    // ����оƬ�ڲ��¶�ֵ ���϶� = Temp / 8 - 256

uint8_t TFminiPlus_flag = 0;                    // �������ݱ�־λ 1-�ɹ�;2-֡ͷ����;3-SCУ�����

uint8_t TFminiPlus_buf[TFMINI_DATA_Len] = {0};  // �ݴ�����֡
uint8_t TFminiPlus_temp = 0;                    // �ݴ浱ǰ�ֽ�
uint8_t TFminiPlus_num = 0;                     // �ݴ汾�ֽ����ݱ���
uint8_t TFminiPlus_cmd[4] = {0};                // �ݴ�����֡


/*
 * @name:       void TFminiPlus_Proc (uint8_t *buf, uint8_t len)
 * @function:   TFminiPlus_Proc
 * @param:      none
 * @return:     none
 * @notion:     Standard Data Format(89BYTE)
 */
void TFminiPlus_Proc (uint8_t *buf, uint8_t len)
{
    uint8_t i = 0;
    uint8_t checksum = 0;

    if (TFMINI_DATA_Len == len)                                         // ��֤���յ�����֡������Э��涨������ͬ
    {
        if (TFMINT_DATA_HEAD == buf[0] && TFMINT_DATA_HEAD == buf[1])   // У��֡ͷ
        {
            for (i = 0; i < (TFMINI_DATA_Len - 1); i++) {
                checksum += buf[i];                                     // ��֡ͷ��ʼ������������, ��sumcheckУ��
            }

            if (checksum == buf[TFMINI_DATA_Len - 1]) {                 // У��Checksum
                // ����ΪС��ģʽ, ���ֽڱ���������֡�ĵ͵�ַ��
                TFmin_Dist = buf[2] | (buf[3] << 8);
                TFmin_Strength = buf[4] | (buf[5] << 8);
                TFmin_Temp = buf[6] | (buf[7] << 8);
                TFminiPlus_flag = 1;
            } else {
                TFminiPlus_flag = 3;
            }
        } else {
            TFminiPlus_flag = 2;
        }
    }
}

/*
 * @name:       void TFminiPlus_Proc2(uint8_t date)
 * @function:   TFminiPlus_Proc2
 * @param:      none
 * @return:     none
 * @example:    TFminiPlus_Proc2(TFminiPlus_temp);
 * @notion:     ���ֽڽ��շ�ʽ
 */
void TFminiPlus_Proc2(uint8_t data)
{
    uint8_t i = 0;
    uint8_t checksum = 0;

    if (TFminiPlus_num == 0 && data == TFMINT_DATA_HEAD) {                      // У�鲢��¼֡ͷ
        TFminiPlus_buf[0] = TFMINT_DATA_HEAD;
        TFminiPlus_num = 1;
    } else if (TFminiPlus_num == 1 && data == TFMINT_DATA_HEAD) {               // У�鲢��¼֡ͷ
        TFminiPlus_buf[1] = TFMINT_DATA_HEAD;
        TFminiPlus_num = 2;
    } else if (TFminiPlus_num >= 2 && TFminiPlus_num <= (TFMINI_DATA_Len - 2)) {
        TFminiPlus_buf[TFminiPlus_num] = data;
        TFminiPlus_num++;
    } else if (TFminiPlus_num == (TFMINI_DATA_Len - 1)) {
        for (i = 0; i < (TFMINI_DATA_Len - 1); i++) {
            checksum += TFminiPlus_buf[i];                                      // ��֡ͷ��ʼ������������, ��checksumУ��
        }

        if (checksum == data) {                                                 // У��Checksum
            //����ΪС��ģʽ, ���ֽ���ǰ����������֡�ĵ͵�ַ��
            TFmin_Dist = TFminiPlus_buf[2] | (TFminiPlus_buf[3] << 8);
            TFmin_Strength = TFminiPlus_buf[4] | (TFminiPlus_buf[5] << 8);
            TFmin_Temp = TFminiPlus_buf[6] | (TFminiPlus_buf[7] << 8);
            TFminiPlus_flag = 1;
        } else {
            TFminiPlus_flag = 3;
        }

        TFminiPlus_num = 0;
    } else {
        TFminiPlus_flag = 2;
        TFminiPlus_num = 0;
    }
}

/*
 * @name:       void TFminiPlus_GetOnce(void)
 * @function:   TFminiPlus_GetOnce
 * @param:      none
 * @return:     ����֡
 * @notion:     �����֡������Ϊ0��, �ſ�ʹ�õ��δ���ָ��
 */
void TFminiPlus_GetOnce(void)
{
    memset(TFminiPlus_cmd, 0, sizeof(TFminiPlus_cmd));

    TFminiPlus_cmd[0] = 0x5A;    //ָ��֡֡ͷ
    TFminiPlus_cmd[1] = 0x04;    //ָ��֡�ܳ���
    TFminiPlus_cmd[2] = 0x04;    //ID
    TFminiPlus_cmd[3] = 0x62;    //Data

    uart_putbuff(UART_3, TFminiPlus_cmd, sizeof(TFminiPlus_cmd)); //���ڷ���ָ��
}
