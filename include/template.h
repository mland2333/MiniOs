
#include "defs.h"
//extern "C" int uart_putc(char ch);

class MyPrint
{
private :
    static char digits[17];
    static char buf[16];
public:
    template<typename T>
    int operator()(T num, int base);
};
char MyPrint::digits[17] = "0123456789abcdef";
char MyPrint::buf[16] = {};

template <typename T>
int MyPrint::operator()(T num, int base)
{
    int j = 0;
    int count = 0;
    do {
        buf[j++] = digits[num % base];
        num /= base;
        count++;
    } while (num != 0);
    for (; j > 0; j--)
        uart_putc(buf[j - 1]);
    return count;
} 


