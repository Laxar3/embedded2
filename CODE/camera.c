
#include "My_Bsp.h"
#include "define.h"
#include <math.h>
#include "camera.h"

//0Ϊͼ�����

/*
 * @name: uint8 Get_Valid_Row (void);
 * @function: ��ȡ��Ч��
 * @param: none
 * @return: Valid_Row
 */
uint8 Get_Valid_Row(void)
{
    uint8 valid_row = 0;

    return valid_row;
}

/*
 * @name:void Bin_Image_Filter (void);
 * @function:�˲��������
 * @param:none
 * @return:none
 * @notice:���汻Χ�����ݽ����޸�Ϊͬһ��ֵ
 */
void Bin_Image_Filter (void)
{

}

//Sobel���ӱ�Ե���
uint8 imgbuff_three[MT9V03X_H][MT9V03X_W];
void MT9V032_extraction(uint8 imgbuff_extration[MT9V03X_H][MT9V03X_W],uint8 imgbuff_two[MT9V03X_H][MT9V03X_W])
{

}

#define GrayScale 256
//��򷨼�����ֵ �����䷽��
uint8 OTSU_threshold(uint8 *image, uint16 col, uint16 row)   //ע�������ֵ��һ��Ҫ��ԭͼ��
{
    uint8 threshold = 0;

    return threshold;
}
