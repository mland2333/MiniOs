#pragma once
#include "type.h"
typedef struct
{
     reg_t ra;
     reg_t sp;
     reg_t s0;
     reg_t s1;
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
}context;

void context_switch(context* new_context, context* old_context);
void porc_init();
void schedule();
