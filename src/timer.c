#include "riscv.h"
#include "clint.c"



void timer_init()
{
    int id = r_mhartid();
    *(uint64*)CLINT_MTIMECMP(id) = *(uint64*)CLINT_MTIME + TIME_INTERVAL;
    w_mtvec(trap_handler);
}
