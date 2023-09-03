//#include "common.h"
#include "defs.h"
#include "stdio.h"
//__attribute__ ((aligned (16))) char stacks[4096 * MAX_CPU];
//extern void uart_init();
//extern void uart_puts(char *s);
//extern void uart_input();
void start()
{
    uart_init();
    uart_puts("Hello MiniOs\n");
    char s[] = "He";
    char fmt[] = "%x : %p, %s\n";
    int res = printf(fmt , -1, &s[0], s);
    //printf("res = %d\n", res);
    
    uart_input();
    while(1) {}; 
}
