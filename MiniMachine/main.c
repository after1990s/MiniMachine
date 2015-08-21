#include <stdio.h>
#include "machine.h"
#include <malloc.h>
int main(void)
{
    _pmachine m = (_machine*)malloc(sizeof(_machine));
    machine_initialize(m);
   
    machine_insert_instruction(
        m,
        instruction_new(MOV, &m->_r_eax, NULL, 1)
        );
    _pinstruction p0 = instruction_new(ADD, &m->_r_eax, NULL, 1);
    machine_insert_instruction(
        m,
        p0
       );
    machine_insert_instruction(
        m,
        instruction_new(MOV, &m->_r_ebx, NULL, 1024));
    machine_insert_instruction(
        m,
        instruction_new(CMP, &m->_r_eax, &m->_r_ebx, 0));
    machine_insert_instruction(
        m,
        instruction_new(JL, p0, NULL, 0));
    machine_start(m);
    printf("%d\n", register_get_content(&m->_r_eax));
}

