#include "register.h"
int register_get_content(const _register* const reg)
{
    return reg->content;
}
void register_set_content(_register* const reg, int content)
{
    reg->content = content;
    
}
void register_init(_register *reg)
{
    reg->content = 0;
}