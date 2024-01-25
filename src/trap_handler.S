.global trap_vector
.option norvc
.balign 4
trap_vector:
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

.global timer_handler

timer_handler:
    //交换t0和mscratch，其中mscratch中是当前进程上下文地址
    csrrw t0, mscratch, t0  
    //存储当前进程context
    reg_save t0
    mv t1, t0
    csrr t0, mscratch
    sd t0, 32(t1)
    //存储mepc
    csrr t0, mepc
    sd t0, 248(t1)

    j timer_load
    j schedule
    //不会返回,在switch_to中返回到另一个进程中
    mret

    
