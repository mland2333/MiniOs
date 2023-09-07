

static inline void
w_mscratch(reg_t x)
{
    asm volatile("csrw mscratch, %0" : : "r" (x));
}
