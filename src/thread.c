#include "stdio.h"
#include "thread.h"
#include "common.h"
#include "riscv.h"
uint8_t __attribute__((aligned(16))) proc_stack[STACK_SIZE];

context task;

void first_task()
{
    printf("Hello MiniOs\n");
    while(1){}
}

void proc_init()
{
    w_mscratch(0);
    task.ra = (reg_t) first_task;
    task.sp = (reg_t) &proc_stack[STACK_SIZE];
}

void schedule()
{
     context *next = &task;
     context now;
     context_switch(&now, next);
}
