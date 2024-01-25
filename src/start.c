
#include "riscv.h"
#include "type.h"

extern void* trap_vector;
extern void kernel();
void start()
{
    //设置mstatus与mepc，使：mret返回后的特权位为S,返回地址为main
    reg_t m = read_csr("mstatus");
    m = m& ~MSTATUS_MPP_MASK;
    write_csr(mstatus, m | MSTATUS_MPP_S);
    write_csr(mepc, kernel);
    write_csr(mtvec, (reg_t)trap_vector | VECTOR_MODE);

    // delegate all interrupts and exceptions to supervisor mode.
    write_csr(medeleg, 0xffff);
    write_csr(mideleg, 0xffff);
    write_csr(sie, read_csr(sie)|SIE_SEIE | SIE_STIE | SIE_SSIE);

    // configure Physical Memory Protection to give supervisor mode
    // access to all of physical memory.
    write_csr(pmpaddr0, 0x3fffffffffffffull);
    write_csr(pmpcfg0, 0xf);

    
    timer_init();

  // keep each CPU's hartid in its tp register, for cpuid().
    int id = read_csr(mhartid);
    write_gr(tp, id);

    // switch to supervisor mode and jump to main().
    asm volatile("mret");
    
}

void timer_init()
{
    timer_load();
    write_csr(mie, read_csr(mie) | MIE_MTIE);
}
void timer_load()
{
    int id = read_csr(mhartid);
    *(uint64_t*)CLINT_MTIMECMP(id) = *(uint64_t*)CLINT_MTIME + TIME_INTERVAL;
}
