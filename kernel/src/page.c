#include "page.h"
#include "riscv.h"
#include "type.h"
#include "stdio.h"
#include "memory.h"
extern char _end[];
void* page_start;
void* heap_start;

#define NEXT(x) (*((uint64_t*)x))
void page_init()
{
    int size = 0;
    page_start = 0;
    heap_start = (void*)PGUP((uint64_t)_end);
    for(uint64_t i = (uint64_t)heap_start; i < MAXPA; i+=PAGE_SIZE)
    {
        size++;
        page_free((void*)i);
    }
    printf("head_start = %p, page_num = %d\n", heap_start, size);
}

void page_free(void* pa)
{
    NEXT(pa) = (uint64_t)page_start;
    page_start = pa;
}

void* page_alloc()
{
    void* alloc;
    if(page_start != 0)
    {
        alloc = (void*)page_start;
        page_start =(void*) NEXT(page_start);
    }
    else
    {
        alloc = 0;
    }
    return alloc;
}
