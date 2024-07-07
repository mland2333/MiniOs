#pragma once

#include "type.h"

extern char _begin[];
#define MAXPA ((uint64_t)_begin + (1 << ((10 + 10 + 8) - 1)))

#define vaddr_t uint64_t
#define paddr_t uint64_t

#define ptr_t uint64_t

/*
enum{NORMAL, RESERVED};

typedef struct{
  uint64_t start, end;
  int flag;
}mem_block;

void mem_block_init();

uint64_t early_memory_alloc();
void mem_block_used_to_buddy();
void memory_init();*/
