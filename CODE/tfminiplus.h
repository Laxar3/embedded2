/*
 *  tfminiplus.h
 *
 *  Created on: 2021��1��10��
 *      Author: LBQ
 */

#ifndef _TFMINI_PLUS_H_
#define _TFMINI_PLUS_H_

// Includes
#include "My_Bsp.h"
#include <string.h>

// Statement
extern  uint16_t    TFmin_Dist;     //������Ϣ
extern  uint16_t    TFmin_Strength; //�ź�ǿ��
extern  uint16_t    TFmin_Temp;     //оƬ�ڲ��¶�ֵ

extern  uint8_t     TFminiPlus_flag;//�������ݱ�־λ

extern  uint8_t     TFminiPlus_temp;//�ݴ浱ǰ�ֽ�

// Function
extern  void TFminiPlus_Proc (uint8_t *buf, uint8_t len);
extern  void TFminiPlus_Proc2(uint8_t data);
extern  void TFminiPlus_GetOnce(void);

#endif /* CODE_TFMINI_PLUS_ */
