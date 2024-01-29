.balign 256, 0
.text 
.global trap_vector_m
trap_vector_m:
    j exception_handler
    j default_handler
    j default_handler
    j software_handler
    j default_handler
    j default_handler
    j default_handler
    j timer_handler
    j default_handler
    j default_handler
    j default_handler
    j external_handler
    j default_handler
    j default_handler
    j default_handler
    j default_handler

.balign 256, 0
.text 
.global trap_vector_s
trap_vector_s:
    j exception_handler
    j default_handler
    j default_handler
    j software_handler
    j default_handler
    j default_handler
    j default_handler
    j default_handler
    j default_handler
    j default_handler
    j default_handler
    j external_handler
    j default_handler
    j default_handler
    j default_handler
    j default_handler


.macro reg_save base
    sd ra, 0(\base)
    sd sp, 8(\base)
    sd gp, 16(\base)
    sd tp, 24(\base)
    sd t0, 32(\base)
    sd t1, 40(\base)
    sd t2, 48(\base)
    sd s0, 56(\base)
    sd s1, 64(\base)
    sd a0, 72(\base)
    sd a1, 80(\base)
    sd a2, 88(\base)
    sd a3, 96(\base)
    sd a4, 104(\base)
    sd a5, 112(\base)
    sd a6, 120(\base)
    sd a7, 128(\base)
    sd s2, 136(\base)
    sd s3, 144(\base)
    sd s4, 152(\base)
    sd s5, 160(\base)
    sd s6, 168(\base)
    sd s7, 176(\base)
    sd s8, 184(\base)
    sd s9, 192(\base)
    sd s10, 200(\base)
    sd s11, 208(\base)
    sd t3, 216(\base)
    sd t4, 224(\base)
    sd t5, 232(\base)
    sd t6, 240(\base)
.endm

.global timer_handler
timer_handler:
    //交换t0和mscratch，其中mscratch中是当前进程上下文地址
    csrrw t0, sscratch, t0  
    //存储当前进程context
    reg_save t0
    mv t1, t0
    csrr t0, sscratch
    sd t0, 32(t1)
    //存储mepc
    csrr t0, mepc
    sd t0, 248(t1)

    call timer_load
    call trans_to_s
    mret
    //不会返回,在switch_to中返回到另一个进程中
    
