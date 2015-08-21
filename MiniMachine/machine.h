#pragma once


#include "stack.h"
#include "error.h"
#include "register.h"

#define MOV 0x00
#define CMP 0x01
#define JE 0x30//jump equal
#define JG 0x31//jump true.
#define JL 0x32//jump true.
#define JMP 0X04
#define PUSH 0X05
#define POP 0x06
#define CALL 0x07
#define RET 0x08

#define ADD 0x10//ADD reg num or ADD reg reg
#define SUB 0x11

typedef struct _instruction_{
    //int ins;
    int op;
    _pregister preg1;
    _pregister preg2;
    _pregister preg3;
    _pregister preg4;
    unsigned int oui;//用于ADDN和SUBN
    struct _instruction_ *next;//这个用于组成命令链，实际的下一条指令由pc指定。
} _instruction, *_pinstruction;

typedef struct _machine_
{
    _register _r_pc;//program counter;
    _register _r_flag;//cmp == 为0。 >为1，<为-1 ;
    _register _r_eip; // call or pop
    _register _r_eax;
    _register _r_ebx;
    _register _r_ecx;
    _register _r_edx;

    struct _stack_ stack;

    _pinstruction instructions;
    _pinstruction instruction_tail;
}_machine, *_pmachine;

void instruction_execute(_pmachine m, _pinstruction ins);
void instruction_execute_mov(_pmachine m, _pinstruction ins);
void instruction_execute_cmp(_pmachine m, _pinstruction ins);
void instruction_execute_je(_pmachine m, _pinstruction ins);
void instruction_execute_jg(_pmachine m, _pinstruction ins);
void instruction_execute_jl(_pmachine m, _pinstruction ins);
void instruction_execute_jmp(_pmachine m, _pinstruction ins);
void instruction_execute_push(_pmachine m, _pinstruction ins);
void instruction_execute_pop(_pmachine m, _pinstruction ins);
void instruction_execute_call(_pmachine m, _pinstruction ins);
void instruction_execute_ret(_pmachine m, _pinstruction ins);
void instruction_execute_add(_pmachine m, _pinstruction ins);
void instruction_execute_sub(_pmachine m, _pinstruction ins);
_pinstruction instruction_new(int op, _pregister r1, _pregister r2, unsigned int oui);

void machine_initialize(_pmachine m);
void machine_start(_pmachine m);
void machine_insert_instruction(_pmachine m, _pinstruction ins);