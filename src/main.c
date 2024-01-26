#include "common.h"
#include "defs.h"
#include "stdio.h"
#include "process.h"
#include "page.h"
#include "riscv.h"
__attribute__ ((aligned (16))) char stacks[4096 * MAX_CPU];     //为每个cpu都分配栈
extern void user_init();
void kernel()
{
    
    uart_init();
    page_init();        //物理页初始化
    //printf("here\n");
    proc_init();        //进程初始化
    //trap_init();
    //printf("here\n");
    user_init();
    //printf("here\n");
    write_csr(sstatus, read_csr(sstatus) | SSTATUS_SPP | SSTATUS_SIE); 
    schedule();         //第一个进程
    while(1) {};
}
