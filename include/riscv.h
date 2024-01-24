#pragma once
#include "type.h"

#define PAGE_SIZE 4096

extern char _begin[];
#define MAXPA ((uint64_t)_begin + (1 << ((10 + 10 + 8) - 1)))
#define PGUP(x) (((x)+PAGE_SIZE-1) & ~(PAGE_SIZE-1))
#define MTVEC_MODE 1

#define MSTATUS_MPP_MASK (3L << 11) // previous mode.
#define MSTATUS_MPP_M (3L << 11)
#define MSTATUS_MPP_S (1L << 11)
#define MSTATUS_MPP_U (0L << 11)
#define MSTATUS_MIE (1L << 3)

static inline 
void w_mscratch(reg_t x)
{
    asm volatile("csrw mscratch, %0" : : "r" (x));
}

static inline 
reg_t r_mtvec()
{
    reg_t x;
    asm volatile("csrr %0, mtvec" : "r" (x));
    return x;
}
static inline 
void w_mtvec(reg_t x)
{
    asm volatile("csrw mtvec, %0" : : "r" (x));
}

static inline 
reg_t r_mstatus()
{
    reg_t x;
	asm volatile("csrr %0, mstatus" : "=r" (x) );
    return x;
}

static inline 
void w_mstatus(reg_t x)
{
	asm volatile("csrw mstatus, %0" : : "r" (x));
}

static inline 
reg_t r_mepc()
{
    reg_t x;
	asm volatile("csrr %0, mepc" : "=r" (x) );
    return x;
}

static inline 
void w_mepc(reg_t x)
{
	asm volatile("csrw mepc, %0" : : "r" (x));
}
static inline 
reg_t r_mhartid()
{
    reg_t x;
	asm volatile("csrr %0, mhartid" : "=r" (x) );
    return x;
}
