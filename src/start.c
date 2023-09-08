#include "common.h"
#include "defs.h"
#include "stdio.h"
#include "thread.h"
#include "page.h"
__attribute__ ((aligned (16))) char stacks[4096 * MAX_CPU];

void start()
{
    uart_init();
    /*uart_puts("Hello MiniOs\n");
    char s[] = "He";
    char fmt[] = "%x : %p, %s\n";
    printf(fmt , -1, &s[0], s);
    
    uart_input();*/
    page_init();
    proc_init();
    schedule();
    while(1) {}; 
}
