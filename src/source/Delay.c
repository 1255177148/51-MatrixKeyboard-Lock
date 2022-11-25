#include <INTRINS.H>

/**
 * 延迟指定毫秒数
 * @param ms 指定的毫秒数
 */
void Delayms(unsigned int ms) //@11.0592MHz
{
    unsigned char i, j;
    while (ms--) {
        _nop_();
        i = 2;
        j = 199;
        do {
            while (--j)
                ;
        } while (--i);
    }
}