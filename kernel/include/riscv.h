#pragma once
#include "type.h"

#define PAGE_SIZE 4096

extern char _begin[];
#define MAXPA ((uint64_t)_begin + (1 << ((10 + 10 + 8) - 1)))
#define PGUP(x) (((x)+PAGE_SIZE-1) & ~(PAGE_SIZE-1))
#define DIRECT_MODE 0
#define VECTOR_MODE 1

#define MSTATUS_MPP_MASK (3L << 11) // previous mode.
#define MSTATUS_MPP_M (3L << 11)
#define MSTATUS_MPP_S (1L << 11)
#define MSTATUS_MPP_U (0L << 11)
#define MSTATUS_MIE (1L << 3)

#define MIE_MEIE (1L << 11) // external
#define MIE_MTIE (1L << 7)  // timer
#define MIE_MSIE (1L << 3)  // software

#define SIE_SEIE (1L << 9) // external
#define SIE_STIE (1L << 5) // timer
#define SIE_SSIE (1L << 1) // software

#define MSTATUS_MPP_MASK (3L << 11) // previous mode.
#define MSTATUS_MPP_M (3L << 11)
#define MSTATUS_MPP_S (1L << 11)
#define MSTATUS_MPP_U (0L << 11)
#define MSTATUS_MIE (1L << 3)    // machine-mode interrupt enable.

#define SSTATUS_SPP (1L << 8)  // Previous mode, 1=Supervisor, 0=User
#define SSTATUS_SPIE (1L << 5) // Supervisor Previous Interrupt Enable
#define SSTATUS_UPIE (1L << 4) // User Previous Interrupt Enable
#define SSTATUS_SIE (1L << 1)  // Supervisor Interrupt Enable
#define SSTATUS_UIE (1L << 0)  // User Interrupt Enable

#define CLINT 0x2000000L

//寄存器，上电时恢复为0,全局为1,且为64bit
#define CLINT_MTIME (CLINT + 0xbff8)

//定时器比较值，自己设初值,mtime>=mtimecmp时，产生中断
#define CLINT_MTIMECMP(hartid) (CLINT + 0x4000 +(hartid)*8)

#define TIME_INTERVAL 10000000


#define read_csr(reg) ({\
    reg_t x;\
    asm volatile("csrr %0, " #reg : "=r" (x));\
    x;\
})

#define write_csr(reg, value) do{\
    asm volatile("csrw " #reg ", %0" : : "r" (value));\
}while(0)

#define read_gr(reg) ({\
    reg_t x;\
    asm volatile("mv %0," #reg : "=r" (x));\
    x;\
})

#define write_gr(reg, value) do{\
    asm volatile("mv " #reg ", %0" : : "r" (value));\
}while(0)


