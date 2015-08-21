#include "machine.h"

void instruction_execute(_pmachine m, _pinstruction ins)
{
    //设置默认的指令
    register_set_content(&m->_r_pc, (int)ins->next);
    switch (ins->op)
    {
    case MOV:
        instruction_execute_mov(m, ins);
        break;
    case CMP:
        instruction_execute_cmp(m, ins);
        break;
    case JE:
        instruction_execute_je(m, ins);
        break;
    case JG:
        instruction_execute_jg(m, ins);
        break;
    case JL:
        instruction_execute_jl(m, ins);
        break;
    case JMP:
        instruction_execute_jmp(m, ins);
        break;
    case PUSH:
        instruction_execute_push(m, ins);
        break;
    case POP:
        instruction_execute_pop(m, ins);
        break;
    case CALL:
        instruction_execute_call(m, ins);
        break;
    case RET:
        instruction_execute_ret(m, ins);
        break;
    case ADD:
        instruction_execute_add(m, ins);
        break;
    case SUB:
        instruction_execute_sub(m, ins);
        break;
    default:
        error_crash("unknown operation");
    }
}

void instruction_execute_mov(_pmachine m, _pinstruction ins)//assign eax ebx.
{
    if (ins->preg2 != NULL)
    {
        register_set_content(ins->preg1, register_get_content(ins->preg2));
    }
    else
    {
        register_set_content(ins->preg1, ins->oui);
    }
}
void instruction_execute_cmp(_pmachine m, _pinstruction ins)
{
    int a1 = register_get_content(ins->preg1);
    int a2 = register_get_content(ins->preg2);
    if (a1 == a2)
    {
        register_set_content(&m->_r_flag, 0);
        return;
    }
    if (a1 > a2)
    {
        register_set_content(&m->_r_flag, 1);
        return;
    }
    if (a1 < a2)
    {
        register_set_content(&m->_r_flag, -1);
        return;
    }
}
void instruction_execute_je(_pmachine m, _pinstruction ins)
{//je [dst]
    if (register_get_content(&m->_r_flag) == 0)
    {
        register_set_content(
            &m->_r_pc,
            register_get_content(&ins->preg1)
            );
    }
}
void instruction_execute_jg(_pmachine m, _pinstruction ins)
{
    if (register_get_content(&m->_r_flag) > 0)
    {
        register_set_content(
            &m->_r_pc,
            register_get_content(&ins->preg1)
            );
    }
}
void instruction_execute_jl(_pmachine m, _pinstruction ins)
{
    if (register_get_content(&m->_r_flag) < 0)
    {
        register_set_content(
            &m->_r_pc,
            register_get_content(&ins->preg1)
            );
    }
}
void instruction_execute_jmp(_pmachine m, _pinstruction ins)
{
    register_set_content(
        &m->_r_pc,
        register_get_content(ins->preg1)
        );
}
void instruction_execute_push(_pmachine m, _pinstruction ins)
{
    stack_push(&m->stack, (int)ins);
}
void instruction_execute_pop(_pmachine m, _pinstruction ins)
{
    register_set_content(ins->preg1, stack_pop(&m->stack));
}
void instruction_execute_call(_pmachine m, _pinstruction ins)
{
    stack_push(
        &m->stack,
        register_get_content(&m->_r_pc));
    register_set_content(&m->_r_pc, register_get_content(ins->preg1));
}
void instruction_execute_ret(_pmachine m, _pinstruction ins)
{
    register_set_content(
        &m->_r_pc,
        stack_pop(&m->stack));
}

void instruction_execute_add(_pmachine m, _pinstruction ins)
{
    if (ins->preg2 != NULL)
    {
        register_set_content(
            ins->preg1,
            register_get_content(ins->preg1) + register_get_content(ins->preg2));
    }
    else
    {
        register_set_content(
            ins->preg1,
            register_get_content(ins->preg1) + ins->oui);
    }
}
void instruction_execute_sub(_pmachine m, _pinstruction ins)
{
    if (ins->preg2 != NULL)
    {
        register_set_content(
            ins->preg1,
            register_get_content(ins->preg1) - register_get_content(ins->preg2));
    }
    else
    {
        register_set_content(
            ins->preg1,
            register_get_content(ins->preg1) - ins->oui);
    }
}
_pinstruction instruction_new(int op, _pregister r1, _pregister r2, unsigned int oui)
{
    _pinstruction ins = (_pinstruction)malloc(sizeof(_instruction));
    ins->op = op;
    ins->preg1 = r1;
    ins->preg2 = r2;
    ins->preg3 = NULL;
    ins->preg4 = NULL;
    ins->oui = oui;
    ins->next = NULL;
}
void machine_initialize(_pmachine m)
{
    register_init(&m->_r_eax);
    register_init(&m->_r_ebx);
    register_init(&m->_r_ecx);
    register_init(&m->_r_edx);
    register_init(&m->_r_pc);
    register_init(&m->_r_flag);
    register_init(&m->_r_eip);

    
    stack_initialize(&m->stack);
    m->instructions = NULL;
    m->instruction_tail = NULL;
}
void machine_start(_pmachine m)
{
    const int true = 1;
    register_set_content(
        &m->_r_pc, 
        (int)m->instructions
    );
    do
    {
        _pinstruction next_ins = register_get_content(&m->_r_pc);
        if (next_ins==NULL)
            break;
        instruction_execute(m, next_ins);
    } while (true);
    error_report("instruction finished");
    return;
}
void machine_insert_instruction(_pmachine m, _pinstruction ins)
{
    if (m->instructions == NULL)
    {
        m->instructions = ins;
        m->instruction_tail = m->instructions;
    }
    else
    {
        m->instruction_tail->next = ins;
        m->instruction_tail = m->instruction_tail->next;
    }
}