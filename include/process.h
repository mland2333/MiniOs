#pragma once
#include "type.h"

#define PROC_NUM 16

typedef struct {
	reg_t ra;
	reg_t sp;
	reg_t gp;
	reg_t tp;
	reg_t t0;
	reg_t t1;
	reg_t t2;
	reg_t s0;
	reg_t s1;
	reg_t a0;
	reg_t a1;
	reg_t a2;
	reg_t a3;
	reg_t a4;
	reg_t a5;
	reg_t a6;
	reg_t a7;
	reg_t s2;
	reg_t s3;
	reg_t s4;
	reg_t s5;
	reg_t s6;
	reg_t s7;
	reg_t s8;
	reg_t s9;
	reg_t s10;
	reg_t s11;
	reg_t t3;
	reg_t t4;
	reg_t t5;
	reg_t t6;
	reg_t pc;
} context;

enum { EMPTY, READY, RUNNING};

typedef struct{
    uint64_t root_pagetable;
    context mcontext;
    int state;
    //int id;
}process;

typedef struct{
    process* proc;
}cpu;

void yield();
void switch_to(context *new_context);
void proc_init();
void schedule();
void make_process();
