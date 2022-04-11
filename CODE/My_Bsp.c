/*
 *  My_Bsp.c
 *
 *  Created on: 2021��1��10��
 *      Author: LBQ
 */

#include "MY_Bsp.h"

/*
 * @name: unsigned char My_Bsp_Init(void)
 * @function: initial
 * @param: none
 * @return: 1 for success ; 0 for not
 */
unsigned char My_Bsp_Init(void)
{
    /* ��ʼ�� */
    SG_Init();
    Beep_Init();
    KEY_Init();
    LED_Init();
    /* ��ʼ������ */
    Speed_Control_Init();
    Magnet_ADC_Init();
    Gyro_Type_Init();
    /* �ⲿӲ����ʼ�� */
    lcd_init();             //���ûװ��ʾ����Ҫ��ʼ��,�������Ῠ����ʾ����ʼ��
    Gyro_Init();            //���ûװ�����ǲ�Ҫ��ʼ��,�������Ῠ�������ǳ�ʼ��
    Encoder_Init();         //���ûװ��������Ҫ��ʼ��,�������Ῠ�ڱ�������ʼ��
    ov7725_uart_init();     //���ûװ����ͷ��Ҫ��ʼ��,�������Ῠ������ͷ��ʼ��

    TFmin_Dist = 40;
//    TFminiPlus_Init();      //�ǵùص��жϵķ���ָ��
    /* ���ߴ��ڳ�ʼ�� */
//    seekfree_wireless_init();

    /* ��ֹ�����ʼ����ת */
    EncoderType_Init();
    MortorType_Init();
    Mortor_Prevent_Madness();

    /* PIT�ж� */
//    systick_start();
    Tim_Count = 0;
    PID_Count = 0;
    timer_pit_interrupt_ms(TIMER_3, 2);

    /* ȫ���豸��ʼ���ɹ�, ����1 */
    return 1;
}



void delay_ms(uint64 ms)
{
    systick_delay_ms(ms);
}
void delay_us(uint64 us)
{
    systick_delay_us(us);
}

void My_swap(int *x, int *y) {
    int t = 0;
    t = *x;
    *x = *y;
    *y = t;
//    *y ^= *x;
//    *x ^= *y;
//    *y ^= *x;
}

//����ƽ�����㷨
float My_sqrt(float number)
{
    long i;
    float x, y;
    const float f = 1.5F;
    float my_sqrt_reciprocal;

    x = number * 0.5F;
    y = number;
    i = * ( long * ) &y;
    i = 0x5f3759df - ( i >> 1 );

    y = * ( float * ) &i;
    y = y * ( f - ( x * y * y ) );
    y = y * ( f - ( x * y * y ) );

    my_sqrt_reciprocal = y;

    return number * my_sqrt_reciprocal;
}

//ţ�ٵ��������ټ��� 1.0/sqrt(x)��ƽ����
float InvSqrt(float x)
{
    float xhalf = 0.5f * x;
    int i = * (int* ) & x;  // get bits for floating VALUE
    i = 0x5f375a86- (i>>1); // gives initial guess y0
    x = * (float* )&i;      // convert bits BACK to float
    x = x * (1.5f - xhalf * x * x); // Newton step, repeating increases accuracy
    return x;
}

int My_pow(int x, int y)
{
    int i;
    int z=1;

    for(i=1;i<=y;i++) z=z*x;
    return z;
}

float mx_sin(float rad)
{
    float sine;
    if (rad < 0) {
        sine = rad*(1.27323954f + 0.405284735f * rad);
    } else {
        sine = rad * (1.27323954f - 0.405284735f * rad);
    }
    if (sine < 0) {
        sine = sine*(-0.225f * (sine + 1) + 1);
    } else {
        sine = sine * (0.225f *( sine - 1) + 1);
    }
    return sine;
}

float My_sin(float rad)
{
    int8 flag = 1;
    if (rad >= ONE_PI) {
        rad -= ONE_PI;
        flag = -1;
    }
    return mx_sin(rad) * flag;
}
float My_cos(float rad)
{
    int8 flag = 1;
    rad += ONE_PI/2.0;
    if (rad >= ONE_PI){
        flag = -1;
        rad -= ONE_PI;
    }
    return My_sin(rad)*flag;
}

//��ȡ״̬
char Get_State(char x)
{
    if(x == 1) {
        return 1;
    }
    if(x == 0) {
        return 0;
    }
    return 0;
}
