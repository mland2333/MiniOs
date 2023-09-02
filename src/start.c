//#include "common.h"

//__attribute__ ((aligned (16))) char stacks[4096 * MAX_CPU];
extern void uart_init();
extern void uart_puts(char *s);
extern void uart_input();
void start()
{
    uart_init();
    uart_puts("Hello MiniOs\n");
    uart_input();
    while(1) {}; 
}
