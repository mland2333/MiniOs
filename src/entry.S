#include "common.h"


.global _entry
.section .text
 _entry:
    
    csrr    a0, mhartid
    mv      tp, a0
    bnez    tp, park        //确保运行在单核心上

    la      sp, stacks
    addi    a0, a0, 1       
    li      a1, STACK_SIZE  //为每个核心分配栈（4096）
    mul     a1, a1, a0
    add     sp, sp, a1
    j       start           //开始运行

park:
    wfi
    j park

    .end
