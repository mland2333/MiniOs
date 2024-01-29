#include "lock.h"
void acquire(lock* lk)
{
    while(__sync_lock_test_and_set(&lk->locked, 1) != 0){}
    __sync_synchronize();
}

void release(lock* lk)
{
    __sync_synchronize();
    __sync_lock_release(&lk->locked);
}
