#include "process.h"
#include "stdio.h"
#include "common.h"
#include "type.h"
#include "lock.h"
#include "riscv.h"
void daley(int count){
    count*=50000;
    while(count--);
}
//int i = 0;
//lock printflock;
void task0()
{ 
    printf("task0\n");
    for(int i = 0;i < 10000; i++)
    {
        //acquire(&printflock);
        printf("hart%d, task0:  %d\n", read_gr(tp), i);
        //release(&printflock);
        daley(100);
    }
    //while(1){}
}

void task1()
{
    printf("task1\n");
    for(int i = 0; i < 10000; i++)
    {
        //acquire(&printflock);
        printf("hart%d, task1:  %d\n", read_gr(tp), i);
        //release(&printflock);
        daley(100);
    }
}
void task2()
{  
    printf("task2\n");
    for(int i = 0;i < 10000; i++)
    {
        //acquire(&printflock);
        printf("hart%d, task2:  %d\n", read_gr(tp), i);
        //release(&printflock);
        daley(100);
    }
    //while(1){}
}
void user_init()
{
    make_process(task0);
    make_process(task1);
    make_process(task2);
}
