#include "common.h"
#include "defs.h"
#include "memory.h"
#include "page.h"
#include "process.h"
#include "riscv.h"
#include "stdio.h"
__attribute__((aligned(16))) char stacks[4096 * MAX_CPU]; // 为每个cpu都分配栈
extern void user_init();
volatile static int started = 0;

void kernel() {
  if (read_gr(tp) == 0) {
    uart_init();
    memory_init();
    // page_init();        //物理页初始化
    // printf("here\n");
    proc_init(); // 进程初始化
    // trap_init();
    // printf("here\n");
    user_init();
    // printf("here\n");
    __sync_synchronize();
    started = 1;
  } else {
    while (!started)
      ;
    __sync_synchronize();
    printf("hart %d starting\n", read_gr(tp));
  }
  write_csr(sstatus, read_csr(sstatus) | SSTATUS_SPP | SSTATUS_SIE);
  schedule();
}
