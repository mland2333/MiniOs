#pragma once

#include "type.h"
#define PAGE_SIZE_BITS 12
#define PAGE_SIZE (1UL << PAGE_SIZE_BITS)
#define SECTION_SIZE_BITS 27
#define SECTION_SIZE = (1UL << SECTION_SIZE_BITS)
/*
typedef struct mem_section{
  uint64_t section_mem_map;
}mem_section;

extern mem_section* mem_sections[]; 

struct page {
  uint64_t flag;
  int count;
  int order;
  uint64_t compound_head;
};*/ 


void page_init();
void *page_alloc();
void page_free();
