#include <Atmel/REGX52.H>
#include <STRING.H>
#include "headers/LCD1602.h"
#include "headers/MatrixKeyboard.h"

char *leftMove(char *str, int len)
{
    int num          = 0;
    while (num < (len - 1)) {
        str[num] = str[num + 1];
        num++;
    }
    return str;
}

void main()
{
    char password[7]     = "000000";
    char initPassword[7] = "000000";
    char realPassword[]  = "456789\0";
    char *str;
    unsigned char martrixKeyNumber;
    int count   = 5;
    int initNum = 5;
    LCD_Init();
    LCD_ShowString(1, 1, "PassWord:");
    while (1) {
        martrixKeyNumber = martrixKey();
        if (martrixKeyNumber) {
            if (martrixKeyNumber <= 10) {
                if (count >= 0) {
                    strcpy(password, leftMove(password, 7));
                    password[5] = (char)((martrixKeyNumber % 10) + '0'); // 密码向左移动一位，这里余10，是因为S10按键要算作0
                    count--;
                }
                str = password;
                LCD_ShowString(2, 1, password);
            }
            if (martrixKeyNumber == 11) {
                if (strcmp(password, realPassword) == 0) {
                    LCD_ShowString(1, 14, "OK ");
                    count = initNum;
                    strcpy(password, initPassword);
                    LCD_ShowString(2, 1, initPassword);
                } else {
                    LCD_ShowString(1, 14, "ERR");
                    count = initNum;
                    strcpy(password, initPassword);
                    LCD_ShowString(2, 1, initPassword);
                }
            }
            if (martrixKeyNumber == 12) {
                LCD_ShowString(1, 14, "   ");
                count = initNum;
                strcpy(password, initPassword);
                LCD_ShowString(2, 1, initPassword);
            }
        }
    }
}