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
    printf("task0\n");
    daley(100);
    yield();
    //while(1){}
}

void task1()
{
    printf("task1\n");
    daley(100);
    yield();
}

void user_init()
{
    make_process(task0);
    make_process(task1);
}
