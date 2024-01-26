#include "stdio.h"
extern void timer_handler();

void exception_handler()
{
    printf("exception\n");
    while(1){}
}

void default_handler()
{
    printf("default\n");
}

void software_handler()
{
    printf("software\n");
}

void external_handler()
{
    printf("external\n");
}

void timer_handler_test()
{
    printf("time_handler\n");
    timer_handler();
}
