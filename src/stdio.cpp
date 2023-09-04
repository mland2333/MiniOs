#include "stdio.h"
#include "defs.h"
#include "type.h"
#include "template.h"
int printf(const char* fmt, ...)
{
     va_list ap;
     va_start(ap, fmt);
     char *s;
     uint64_t ptr;
     int num;
     int res = 0;
     MyPrint print;
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
                     s = const_cast<char*>("null");
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
                 res += print(ptr, 16);
                 break;
             case 'd':
                 num = va_arg(ap, int);
                 if(num < 0)
                 {
                     uart_putc('-');
                     num = -num;
                     res++;
                 }
                 res += print(num, 10);
                
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
                 res += print(num, 16);
                 
                 break;

         }
     }
     va_end(ap);
     return res;
}
