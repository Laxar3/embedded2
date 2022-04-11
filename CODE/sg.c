/*
 *  sg.c
 *
 *  Created on: 2021��1��10��
 *      Author: LBQ
 */

#include "MY_Bsp.h"
#include "sg.h"

uint8   SG_Test_Num = 0;
int16   SG_KEYTest_Now = 0;     //�ݴ浱ǰ��������ֵ
int16   SG_Test_Temp = 0;

uint16   Servo_Max = 7800;
uint16   Servo_Min = 1400;

uint16   Servo_Center_Front = 4780;
uint16   Servo_Center_Back  = 0;
uint16   Servo_Turn90_Left  = 6940;
//uint16   Servo_Turn90_Left  = 7020;
uint16   Servo_Turn90_Right = 2540;

/*
 * @name:void SG_Init(void);
 * @function: sg pin initialize
 * @param:none
 * @return:none
 * @notice:pwm��ʼ��Ƶ��Ϊ50hz ������� duty = 1.5 * 10000 / 20
 */
void SG_Init(void)
{
    pwm_init(PWM_SG, 300, Servo_Center_Front);
}

/*
 * @name:void ServoCtrl(uint16 duty);
 * @function: SG Dir Change
 * @param:none
 * @return:none
 * @notice:
 * ������λ�ö��λ��   ��0.5ms - 2.5ms��ms/20ms * 10000��10000��PWM����ռ�ձ�ʱ���ֵ��
 */
void ServoCtrl(uint16 duty)
{
    if (duty >= Servo_Max)    duty = Servo_Max;    //���Ʒ�ֵ
    if (duty <= Servo_Min)    duty = Servo_Min;

//    duty = duty * (Servo_Max/Servo_Min);            //���ƽ�������Գ�
//    if (duty >= Servo_Max)    duty = Servo_Max;
//    if (duty <= Servo_Min)    duty = Servo_Min;

    pwm_duty(PWM_SG, duty);
}

/*
 * @name:void SG_Test(void);
 * @function: SG_Test
 * @param:none
 * @return:none
 * @notice: ��һ�������KEY1����ռ�ձ�(5)
 *          ��һ�����ڲ�KEY3��Сռ�ձ�(5)
 *          ��һ���м��KEY2���ת90��
 */
void SG_Test(void)
{
    uint8 increment = 20;

    SG_KEYTest_Now = KEY_Scan();

    if(SG_KEYTest_Now == 1) {
        SG_Test_Temp += increment;
//        ServoCtrl(Servo_Center + SG_Duty_Test);
        pwm_duty(PWM_SG, SG_Test_Temp);
        Beep_Buzzing(20, 1);
    } else if(SG_KEYTest_Now == 2) {
        SG_Test_Num++;
        if (SG_Test_Num > 4) SG_Test_Num = 1;
        switch (SG_Test_Num) {
            case 1: SG_Test_Temp = Servo_Center_Front;  break;
            case 2: SG_Test_Temp = Servo_Turn90_Left;   break;
            case 3: SG_Test_Temp = Servo_Turn90_Right;  break;
            case 4: SG_Test_Temp = Servo_Center_Back;   break;
            default:    break;
        }
        pwm_duty(PWM_SG, SG_Test_Temp);
        Beep_Buzzing(50, 1);
    } else if(SG_KEYTest_Now == 3) {
        SG_Test_Temp -= increment;
//        ServoCtrl(Servo_Center + SG_Duty_Test);
        pwm_duty(PWM_SG, SG_Test_Temp);
        Beep_Buzzing(20, 1);
    }
    lcd_showint16(0, 4, SG_Test_Temp);
    if (Photo_Finsh_Flag == 1) {
        lcd_displayimage032(img[0], OV7725_UART_W, OV7725_UART_H);
        midline_show();        //���߸�����ʾ
    }   //����ͷ

//        SG_Test_Temp += increment;
//        pwm_duty(PWM_SG, SG_Test_Temp);
//        lcd_showint16(0, 0, SG_Test_Temp);
//        delay_ms(100);
//        delay_ms(200);
}

void SG_Turn_Front(void) {
    ServoCtrl(Servo_Center_Front);
}

void SG_Turn_Back(void) {
    ServoCtrl(Servo_Center_Back);
}

void SG_Turn90_Left(void) {
    ServoCtrl(Servo_Turn90_Left);
}

void SG_Turn90_Right(void) {
    ServoCtrl(Servo_Turn90_Right);
}
