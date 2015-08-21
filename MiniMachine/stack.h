#pragma once
#include <memory.h>
#include "instruction.h"


typedef struct _stack_
{
    int stk[1024];//只有0-1022可用。
    int top;
}_stack, *_pstack;

void stack_unittest();

void stack_initialize(_pstack stk);

void stack_push(_pstack stk,int pi);

int stack_pop(_pstack stk);