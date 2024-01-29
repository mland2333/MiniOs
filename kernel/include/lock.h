#include "type.h"
typedef struct  {
   uint32_t locked;
}lock;

void acquire(lock* lk);
void release(lock* lk);
