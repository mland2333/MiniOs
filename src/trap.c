#include "stdio.h"
#include "riscv.h"
#include "type.h"
extern void timer_handler();
extern void yield();
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

void trans_to_s()
{
    reg_t m_status = read_csr(mstatus);
    int flag =(((m_status & MSTATUS_MPP_S) == 0)? 0:SSTATUS_SPP);
    reg_t s_status = read_csr(sstatus);
    s_status &= ~SSTATUS_SPP;
    write_csr(sstatus, s_status | flag);
    write_csr(mepc, &yield);
    m_status &= ~MSTATUS_MPP_MASK;
    write_csr(mstatus, m_status|MSTATUS_MPP_S);
}
