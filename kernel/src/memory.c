#include "memory.h"
#include "type.h"

mem_block mem_block_free;
mem_block mem_block_used;
extern char _end[];

void mem_block_init(){
  mem_block_free.start = (uint64_t)_end;
  mem_block_free.end = MAXPA;
  mem_block_free.flag = NORMAL;

  mem_block_free.start = (uint64_t)_end;
  mem_block_used.end = (uint64_t)_end;
  mem_block_used.flag = NORMAL;
}

uint64_t early_memory_alloc(int size, int align){
  align = (1 << align) - 1;
  uint64_t start = (mem_block_free.start + 2 * align + 1) & (~align);
  uint64_t end = (mem_block_free.end + align) & (~align);
  if(unlikely(end - start < size)) return 0;
  mem_block_free.start = start + size;
  mem_block_used.end = start + size;
  return start;
}
void memory_init(){
  mem_block_init();
}
void mem_block_used_to_buddy();
