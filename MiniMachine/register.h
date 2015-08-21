#pragma once
typedef struct _register__
{
    int content;
}_register,*_pregister;

int register_get_content(const _register* const reg);
void register_set_content(_register* const  reg, int content);
void register_init(_register *reg);