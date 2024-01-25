#include "process.h"
#include "stdio.h"
#include "common.h"
#include "type.h"
void daley(int count){
    count*=500000;
    while(count--);
}


void task0()
{   
    for(int i = 0; i < 10000; i++)
    {
        printf("task0:  %d\n", i);
        daley(100);
    }
    //while(1){}
}

void task1()
{
    for(int i = 0; i < 10000; i++)
    {
        printf("task1:  %d\n", i);
        daley(100);
    }
}

void user_init()
{
    make_process(task0);
    make_process(task1);
}
