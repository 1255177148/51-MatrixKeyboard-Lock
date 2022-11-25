#include <Atmel/REGX52.H>
#include "../headers/Delay.h"

/**
 * 校验每列从上到下哪个键盘被按下
 * @param num 第几列，值从0开始
 */
unsigned char checkKeyNumber(unsigned char num)
{
    unsigned char keyNumber = 0;
    if (P1_7 == 0) {
        /* 看纵向第一个是否是0，也就是S1、S2、S3、S4键是否按下 */
        Delayms(20); // 取消按键抖动
        while (P1_7 == 0)
            ; // 检测是否松手
        Delayms(20);
        keyNumber = 1 + num;
    } else if (P1_6 == 0) {
        /* 看纵向第二个是否是0，也就是S5、S6、S7、S8键是否按下 */
        Delayms(20); // 取消按键抖动
        while (P1_6 == 0)
            ; // 检测是否松手
        Delayms(20);
        keyNumber = 5 + num;
    } else if (P1_5 == 0) {
        /* 看纵向第三个是否是0，也就是S9、S10、S11、S12键是否按下 */
        Delayms(20); // 取消按键抖动
        while (P1_5 == 0)
            ; // 检测是否松手
        Delayms(20);
        keyNumber = 9 + num;
    } else if (P1_4 == 0) {
        /* 看纵向第四个是否是0，也就是S13、S14、S15、S16键是否按下 */
        Delayms(20); // 取消按键抖动
        while (P1_4 == 0)
            ; // 检测是否松手
        Delayms(20);
        keyNumber = 13 + num;
    }
    return keyNumber;
}

/**
 * 扫描按下的是哪个键
 */
unsigned char martrixKey()
{
    unsigned char keyNumber = 0;
    /*
    矩阵键盘是由横向四个针脚和纵向四个针脚连接电路的，
    我们可以先给纵向四个针脚赋0，然后依次检测横向四个针脚是否为0，
    横向第几个针脚为0，则按的就是指定纵向的从上到下第几个键
    */
    unsigned char num = 4;
    while (num) {
        P1 = 0xFF; // 先给P1八个针脚赋高电平，初始
        switch (num) {
            case 1:
                P1_3 = 0;
                break;
            case 2:
                P1_2 = 0;
                break;
            case 3:
                P1_1 = 0;
                break;
            case 4:
                P1_0 = 0;
                break;
            default:
                break;
        }
        keyNumber = checkKeyNumber(num - 1);
        if (keyNumber)
        {
            return keyNumber;
        }
        num--;
    }
    return keyNumber;
}