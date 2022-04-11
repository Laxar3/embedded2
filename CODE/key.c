/*
 *  key.c
 *
 *  Created on: 2021��1��10��
 *      Author: LBQ
 */

#include "MY_Bsp.h"
#include "key.h"

/**********************KEY***********************/

void KEY_Init(void)
{
    //keys
    gpio_init(KEY_1_PIN, GPI, 1, GPIO_INT_CONFIG);
    gpio_init(KEY_2_PIN, GPI, 1, GPIO_INT_CONFIG);
    gpio_init(KEY_3_PIN, GPI, 1, GPIO_INT_CONFIG);
//    gpio_init(KEY_4_PIN, GPI, 1, GPIO_INT_CONFIG);
//    gpio_init(KEY_5_PIN, GPI, 1, GPIO_INT_CONFIG);

    //dips
//    gpio_init(DIP_1_PIN, GPI, 1, GPIO_INT_CONFIG);
//    gpio_init(DIP_2_PIN, GPI, 1, GPIO_INT_CONFIG);
//    gpio_init(DIP_3_PIN, GPI, 1, GPIO_INT_CONFIG);
}

uint8 KEY_Scan(void)
{
    if(KEY_1_GEt == 0) {
        systick_delay_ms(10);  //ȥ����
        if(KEY_1_GEt == 0)
        {
          while(!KEY_1_GEt);
          systick_delay_ms(5);
          return 1;
        }
    } else if(KEY_2_GEt == 0) {
        systick_delay_ms(10);
        if(KEY_2_GEt == 0)
        {
          while(!KEY_2_GEt);
          systick_delay_ms(5);
          return 2;
        }
    } else if(KEY_3_GEt == 0) {
        systick_delay_ms(10);
        if(KEY_3_GEt == 0)
        {
          while(!KEY_3_GEt);
          systick_delay_ms(5);
          return 3;
        }
    }
//    else if(KEY_4_GEt == 0) {
//        systick_delay_ms(10);
//        if(KEY_4_GEt == 0)
//        {
////          while(!KEY_4_GEt);
////          systick_delay_ms(5);
//            return 4;
//        }
//    } else if(KEY_5_GEt == 0) {
//        systick_delay_ms(10);
//        if(KEY_5_GEt == 0)
//        {
////          while(!KEY_5_GEt);
////          systick_delay_ms(5);
//            return 5;
//        }
//    }
    return 0;   // �ް�������
}

int8 KEY_Scan_Screen(void)
{
    if(KEY_1_GEt == 0)
    {
        systick_delay_ms(10);
        if(KEY_1_GEt == 0)
        {
          while(!KEY_1_GEt);
          systick_delay_ms(10);
          return 1;
        }
    } else if(KEY_2_GEt == 0) {
        systick_delay_ms(10);
        if(KEY_2_GEt == 0)
        {
          while(!KEY_2_GEt);
          systick_delay_ms(10);
          return 10;
        }
    } else if(KEY_3_GEt == 0) {
        systick_delay_ms(10);
        if(KEY_3_GEt == 0)
        {
          while(!KEY_3_GEt);
          systick_delay_ms(5);
          return -1;
        }
    }
    return 0;   // �ް�������
}

uint8 KEY_Scan_Long(void)
{
    if(KEY_1_GEt == 0)
    {
        systick_delay_ms(100);
        if(KEY_1_GEt == 0)
        {
//          while(!KEY_1_GEt);
//          systick_delay_ms(10);
            return 11;
        }
    }
    else if(KEY_2_GEt == 0)
    {
        systick_delay_ms(100);
        if(KEY_2_GEt == 0)
        {
//          while(!KEY_2_GEt);
//          systick_delay_ms(10);
            return 12;
        }
    }
    else if(KEY_3_GEt == 0)
    {
        systick_delay_ms(100);
        if(KEY_3_GEt == 0)
        {
//          while(!KEY_3_GEt);
//          systick_delay_ms(10);
            return 13;
        }
    }
    return 0;   // �ް�������
}

void KEY_Test(void)
{
//    if(KEY_1_GEt == 0)  Beep_Buzzing(25, 1);
//    if(KEY_2_GEt == 0)  Beep_Buzzing(25, 1);
//    if(KEY_3_GEt == 0)  Beep_Buzzing(25, 1);
//    if(KEY_4_GEt == 0)  Beep_Buzzing(25, 1);
//    if(KEY_5_GEt == 0)  Beep_Buzzing(25, 1);
}

/**********************DIP***********************/

///*
// * @name:void Boot_DIP_Scan(void)
// * @function:��ʼ��ģʽ��⣬ÿ��DIP���������Լ�������
// *           ���п������ ִ��һ��
// * @param:none
// * @return:none
// */
//void Boot_DIP_Scan(void)
//{
//    if(DIP_1_GEt == 0)
//    {
//        systick_delay_ms(10);   //ȥ����
//        if(DIP_1_GEt == 0)
//        {
//            systick_delay_ms(1);
//        }
//    }
//    if(DIP_2_GEt == 0)
//    {
//        systick_delay_ms(10);
//        if(DIP_2_GEt == 0)
//        {
//            systick_delay_ms(1);
//        }
//    }
//    if(DIP_3_GEt == 0)
//    {
//        systick_delay_ms(10);
//        if(DIP_3_GEt == 0)
//        {
//            systick_delay_ms(1);
//        }
//    }
//}
//
///*
// * @name:uint8 DIP_Scan(void)
// * @function: DIP_Scan
// * @param:none
// * @return:none
// */
//uint8 DIP_Scan(void)
//{
//    if(DIP_1_GEt == 0) {
//        systick_delay_ms(5);   //ȥ����
//        if(DIP_1_GEt == 0)
//        {
//            return 1;
//        }
//    } else if(DIP_2_GEt == 0) {
//        systick_delay_ms(5);
//        if(DIP_2_GEt == 0)
//        {
//            return 2;
//        }
//    } else if(DIP_3_GEt == 0) {
//        systick_delay_ms(5);
//        if(DIP_3_GEt == 0)
//        {
//            return 3;
//        }
//    }
//    return 0;
//}
//
///*
// * @name:
// * @function:DIP������⣬������1 �ط���0
// * @param:��Ҫ���Ŀ���
// * @return:����״̬
// */
//uint8 Dial_Read(void)
//{
//    uint8 value = 0x00;
//    value = (DIP_1_GEt) + (DIP_2_GEt) + (DIP_3_GEt);
//    return value;
//}
//
//unsigned char Check_DIP_1(void)
//{
//    if(DIP_1_GEt == 0)
//    {
//      systick_delay_ms(5);   //ȥ����
//        if(DIP_1_GEt == 0)
//        {
//            return 1;
//        }
//    }
//    return 0;
//}
//unsigned char Check_DIP_2(void)
//{
//    if(DIP_2_GEt == 0)
//    {
//      systick_delay_ms(5);
//        if(DIP_2_GEt == 0)
//        {
//            return 1;
//        }
//    }
//    return 0;
//}
//unsigned char Check_DIP_3(void)
//{
//    if(DIP_3_GEt == 0)
//    {
//      systick_delay_ms(5);
//        if(DIP_3_GEt == 0)
//        {
//            return 1;
//        }
//    }
//    return 0;
//}
