#include <Atmel/REGX52.H>
#include <STRING.H>
#include "headers/LCD1602.h"
#include "headers/MatrixKeyboard.h"

void main()
{
    unsigned int password;
    // char password[7];
    // char initPassword[7] = "000000";
    unsigned int realPassword = 4567;
    unsigned char martrixKeyNumber;
    char count = 0;
    LCD_Init();
    LCD_ShowString(1, 1, "PassWord:");
    while (1) {
        martrixKeyNumber = martrixKey();
        if (martrixKeyNumber) {
            if (martrixKeyNumber <= 10) {
                if (count < 4) {
                    password *= 10;                    // 密码向左移动一位
                    password += martrixKeyNumber % 10; // 获取一位密码，这里余10，是因为S10按键要算作0
                    count++;
                }
                LCD_ShowNum(2, 1, password, 4);
            }
            if (martrixKeyNumber == 11) {
                if (password == realPassword) {
                    LCD_ShowString(1, 14, "OK ");
                    password = 0;
                    count    = 0;
                    LCD_ShowNum(2, 1, password, 4);
                } else {
                    LCD_ShowString(1, 14, "ERR");
                    password = 0;
                    count    = 0;
                    LCD_ShowNum(2, 1, password, 4);
                }
            }
            if (martrixKeyNumber == 12) {
                LCD_ShowString(1, 14, "   ");
                password = 0;
                count    = 0;
                LCD_ShowNum(2, 1, password, 4);
            }
        }
    }
}