#include "common.h"


.global _entry
.section .text
 _entry:
    
    csrr    a0, mhartid
    mv      tp, a0
    bnez    tp, park

    la      sp, stacks
    addi    a0, a0, 1
    li      a1, STACK_SIZE
    mul     a1, a1, a0
    add     sp, sp, a1
    j       start

park:
    wfi
    j park

    .end
