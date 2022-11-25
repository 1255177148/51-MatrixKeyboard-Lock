#include <Atmel/REGX52.H>
#include <STRING.H>
#include "headers/LCD1602.h"
#include "headers/MatrixKeyboard.h"

void main()
{
    char password[7]     = "000000";
    char initPassword[7] = "000000";
    char realPassword[]  = "456789";
    unsigned char martrixKeyNumber;
    char count = 6;
    LCD_Init();
    LCD_ShowString(1, 1, "PassWord:");
    while (1) {
        martrixKeyNumber = martrixKey();
        if (martrixKeyNumber) {
            if (martrixKeyNumber <= 10) {
                if (count > 0) {
                    password[count] = martrixKeyNumber % 10; // 密码向左移动一位，这里余10，是因为S10按键要算作0
                    count--;
                }
                LCD_ShowNum(2, 1, password, 4);
            }
            if (martrixKeyNumber == 11) {
                if (strcmp(password, realPassword) == 0) {
                    LCD_ShowString(1, 14, "OK ");
                    count = 6;
                    strcpy(password, initPassword);
                    LCD_ShowString(2, 1, initPassword);
                } else {
                    LCD_ShowString(1, 14, "ERR");
                    count = 6;
                    strcpy(password, initPassword);
                    LCD_ShowString(2, 1, initPassword);
                }
            }
            if (martrixKeyNumber == 12) {
                LCD_ShowString(1, 14, "   ");
                count = 6;
                strcpy(password, initPassword);
                LCD_ShowString(2, 1, initPassword);
            }
        }
    }
}