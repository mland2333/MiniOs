

.macro reg_restore base
    ld ra, 0(\base)
    ld sp, 8(\base)
    ld gp, 16(\base)
    ld tp, 24(\base)
    ld t0, 32(\base)
    ld t1, 40(\base)
    ld t2, 48(\base)
    ld s0, 56(\base)
    ld s1, 64(\base)
    ld a1, 80(\base)
    ld a2, 88(\base)
    ld a3, 96(\base)
    ld a4, 104(\base)
    ld a5, 112(\base)
    ld a6, 120(\base)
    ld a7, 128(\base)
    ld s2, 136(\base)
    ld s3, 144(\base)
    ld s4, 152(\base)
    ld s5, 160(\base)
    ld s6, 168(\base)
    ld s7, 176(\base)
    ld s8, 184(\base)
    ld s9, 192(\base)
    ld s10, 200(\base)
    ld s11, 208(\base)
    ld t3, 216(\base)
    ld t4, 224(\base)
    ld t5, 232(\base)
    ld t6, 240(\base)   
.endm
.global switch_to

switch_to:
    csrw sscratch, a0   //a0 = &proc.context
    ld a1, 248(a0)      //context->pc to mepc
    csrw sepc, a1
    reg_restore a0
    ld a0, 72(a0)

    sret
