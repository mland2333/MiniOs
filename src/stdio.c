#include "stdio.h"
#include "defs.h"
#include "type.h"
int printf(const char* fmt, ...)
{
     va_list ap;
     va_start(ap, fmt);
     char *s;
     uint64_t ptr;
     int num;
     char digits[] = "0123456789abcdef";
     char buf[33];
     int res = 0;
     int j = 0;
     for(int i = 0; fmt[i]!='\0'; i++)
     {
         if(fmt[i] != '%')
         { 
             uart_putc(fmt[i]);
             res++;
             continue;
         }
         i++;
         if(fmt[i] == 0) break;
         switch(fmt[i])
         {
             case 's':
                 if((s=va_arg(ap, char*)) == 0)
                     s = "null";
                 for(;*s!=0;s++) 
                 {
                     uart_putc(*s);
                     res++;
                 }
                 break;
             case 'p':
                 ptr = va_arg(ap, uint64_t);
                 uart_putc('0');
                 uart_putc('x');
                 res+=2;
                 for(j = 0; j < sizeof(uint64_t)*2; j++)
                 {
                     buf[15-j] = digits[(ptr >> (j*4)) & 0xf];
                     res++;
                 }
                 buf[16] = 0;
                 uart_puts(buf);
                 break;
             case 'd':
                 num = va_arg(ap, int);
                 if(num < 0)
                 {
                     uart_putc('-');
                     num = -num;
                     res++;
                 }
                 j = 0;
                 do
                 {
                     buf[j++] = digits[num%10];
                     num /= 10;
                     res++;
                 }while(num != 0);
                 for(;j>0; j--)
                     uart_putc(buf[j-1]);
                 break;
             case 'x':
                 num = va_arg(ap, int);
                 if(num < 0)
                 {
                     uart_putc('-');
                     num = -num;
                     res++;
                 }
                 uart_putc('0');
                 uart_putc('x');
                 res+=2;
                 j = 0;
                 do
                 {
                     buf[j++] = digits[num%16];
                     num >>= 4;
                     res++;
                 }while(num != 0);
                 for(;j>0; j--)
                     uart_putc(buf[j-1]);
                 break;

         }
     }
     return res;
}
