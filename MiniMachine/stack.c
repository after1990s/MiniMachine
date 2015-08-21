#include "stack.h"
#include "error.h"
#include "assert.h"
#include "machine.h"
#include <malloc.h>
#include <memory.h>
const int stack_max_size = 1024;
void stack_unittest()
{
    _pstack stk = (_pstack)malloc(sizeof(_stack));;
    _instruction ins = {0xcc};
    stack_initialize(stk);
    for (int i = 0; i < 1023; i++)
    {
        stack_push(stk, (int)&ins);
    }
    for (int i = 0; i < 1023; i++)
    {
        stack_pop(stk);
    }
}

void stack_initialize(_pstack stk)
{
    
    memset(stk->stk, 0, sizeof(int)*stack_max_size);
    stk->top = 0;
}

void stack_push(_pstack stk,int pi)
{
    if (stk->top == stack_max_size-1)
    {
        error_crash("stack overflow");
        assert(1);
    }
    stk->top++;
    stk->stk[stk->top] = pi;
}

int stack_pop(_pstack stk)
{
    if (stk->top == 0)
    {
        error_crash("try to pop an empty stack");
        assert(1);
    }
    return stk->stk[stk->top--];
}

