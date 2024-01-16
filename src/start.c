#include "common.h"
#include "defs.h"
#include "stdio.h"
#include "process.h"
#include "page.h"
__attribute__ ((aligned (16))) char stacks[4096 * MAX_CPU];     //为每个cpu都分配栈
extern user_init();

void start()
{
    uart_init();
    page_init();        //物理页初始化
    proc_init();        //进程初始化
    printf("here\n");
    user_init();
    printf("here\n");
    schedule();         //第一个进程
    while(1) {}; 
}
