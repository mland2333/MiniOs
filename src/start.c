#include "common.h"
#include "defs.h"
#include "stdio.h"
#include "process.h"
#include "page.h"
__attribute__ ((aligned (16))) char stacks[4096 * MAX_CPU];     //为每个cpu都分配栈
extern void user_init();

void start()
{
    //设置mstatus与mepc，使：mret返回后的特权位为S,返回地址为main
    reg_t mstatus = r_mstatus();
    mstatus = mstatus& ~MSTATUS_MPP_MASK;
    w_mstatus(mstatus | MSTATUS_MPP_S);
    w_mepc(main);

    //以下摘自xv6
    // delegate all interrupts and exceptions to supervisor mode.
    w_medeleg(0xffff);
    w_mideleg(0xffff);
    w_sie(r_sie() | SIE_SEIE | SIE_STIE | SIE_SSIE);

    // configure Physical Memory Protection to give supervisor mode
    // access to all of physical memory.
    w_pmpaddr0(0x3fffffffffffffull);
    w_pmpcfg0(0xf);

    timer_init();

  // keep each CPU's hartid in its tp register, for cpuid().
    int id = r_mhartid();
    w_tp(id);

    // switch to supervisor mode and jump to main().
    asm volatile("mret");
    
}
