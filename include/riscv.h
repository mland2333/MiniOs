#pragma once
#include "type.h"

#define PAGE_SIZE 4096

extern char _begin[];
#define MAXPA ((uint64_t)_begin + (1 << ((10 + 10 + 8) - 1)))
#define PGUP(x) (((x)+PAGE_SIZE-1) & ~(PAGE_SIZE-1))



static inline void
w_mscratch(reg_t x)
{
    asm volatile("csrw mscratch, %0" : : "r" (x));
}
