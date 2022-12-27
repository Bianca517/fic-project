#include "header.h"

uint16_t ALU_SP_fcn(uint16_t stack_pointer_from_SP_reg, uint8_t spO)
{
    // stiva creste invers in memorie
    //  presupun ca daca spO e 0, am PUSH
    //  presupun ca daca spO e 1, am POP
    if (false == spO)
    {
        stack_pointer_from_SP_reg--;
    }
    if (1U == spO)
    {
        stack_pointer_from_SP_reg++;
    }
    return stack_pointer_from_SP_reg;
}

uint16_t stack_pointer_fcn(uint16_t stack_pointer_value_from_ALU)
{
    // stackul incepe in memorie de la adresa 400, deci primul push va fi pus la 399
    static uint16_t stack_pointer_address = 0x400;

    stack_pointer_address = stack_pointer_value_from_ALU;

    return stack_pointer_address;
}
