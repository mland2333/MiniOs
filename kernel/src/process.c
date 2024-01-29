#include "stdio.h"
#include "process.h"
#include "common.h"
#include "riscv.h"
#include "lock.h"

uint8_t __attribute__((aligned(16))) proc_stack[PROC_NUM][STACK_SIZE];

cpu mcpu[MAX_CPU];

process proc[PROC_NUM];
//lock proclock[PROC_NUM];
int proc_id = 0;
lock proclock;
void proc_init()
{ 
    for(int i = 0; i < PROC_NUM; i++)
    {
        proc[i].state = EMPTY;
        proc[i].root_pagetable = 0;
    }
}

void yield()
{
    mcpu[read_gr(tp)].proc->state = READY;
    //printf("yield\n");
    schedule();
}

extern void switch_to(void*);
void schedule()
{
    acquire(&proclock);
    int i = proc_id;
    while(proc_id < PROC_NUM)
    {   
        if(proc[i].state == READY)
        {
            proc[i].state = RUNNING;
            proc_id = i + 1;
            release(&proclock);
            mcpu[read_gr(tp)].proc = &proc[i];
            switch_to(&proc[i].mcontext);
        }
        i++;
        if(i == PROC_NUM)
            i = 0;
    }
}

void make_process(void (*taskn)(void))
{
    for(int i = 0; i<PROC_NUM; i++)
    {
        if(proc[i].state == EMPTY)
        {
            //proc[i].mcontext.ra = (reg_t)taskn;
            proc[i].mcontext.sp = (reg_t)&proc_stack[i][STACK_SIZE];
            proc[i].mcontext.pc = (reg_t)taskn;
            proc[i].state = READY;
            break;
        }
    }
}
/*
uint8_t __attribute__((aligned(16))) proc_stack[TASK_NUM][STACK_SIZE];

//context task;

context task[2];
int proc_id = 0;
void daley(int count){
    count*=50000;
    while(count--);
}

void hello()
{
    printf("Hello MiniOs\n");
}
void task1(){
    printf("task1\n");
    delay(10);
}
void task2(){
    printf("task2\n");
    delay(10);
}


void proc_init()
{
    w_mscratch(0);
    task[0].ra = (reg_t) task1;
    task[0].sp = (reg_t) &proc_stack[0][STACK_SIZE];
    task[1].ra = (reg_t) task1;
    task[1].sp = (reg_t) &proc_stack[1][STACK_SIZE];
    
}

void schedule()
{
    while(true){
        int proc_id = proc_id % TASK_NUM;
     context_switch(&now, next);
}*/
