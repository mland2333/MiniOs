
#include "riscv.h"
#include "type.h"
#include "stdio.h"
extern void* trap_vector_m;
extern void* trap_vector_s;
extern void kernel();

void timer_load()
{
    int id = read_csr(mhartid);
    *(uint64_t*)CLINT_MTIMECMP(id) = *(uint64_t*)CLINT_MTIME + TIME_INTERVAL;
}

void timer_init()
{
    timer_load();
    write_csr(mstatus, read_csr(mstatus) | MSTATUS_MIE);
    write_csr(mie, read_csr(mie) | MIE_MTIE);
}

void start()
{
    //设置mstatus与mepc，使：mret返回后的特权位为S,返回地址为main
    reg_t m = read_csr(mstatus);
    m &= ~MSTATUS_MPP_MASK;
    m = m | MSTATUS_MPP_S;
    write_csr(mstatus, m);
    write_csr(mepc, (uint64_t)kernel);

    

    write_csr(mtvec, (reg_t)(&trap_vector_m) | VECTOR_MODE);
    
    write_csr(satp, 0);//禁用分页
    // delegate all interrupts and exceptions to supervisor mode.
    write_csr(medeleg, 0xffff);
    write_csr(mideleg, 0xffff);
    write_csr(sie, read_csr(sie)|SIE_SEIE | SIE_STIE | SIE_SSIE);

    reg_t s = (reg_t)(&trap_vector_s) | VECTOR_MODE;
    write_csr(stvec, s);

    // configure Physical Memory Protection to give supervisor mode
    // access to all of physical memory.
    write_csr(pmpaddr0, 0x3fffffffffffffull);
    write_csr(pmpcfg0, 0xf);

    
    timer_init();

  // keep each CPU's hartid in its tp register, for cpuid().
    int id = read_csr(mhartid);
    write_gr(tp, id);
    write_csr(sscratch, 0);
    // switch to supervisor mode and jump to main().
    asm volatile("mret");
    
}


