#include "header.h"

static uint16_t stack_pointer_address = DATA_MEMORY_SIZE;

uint16_t ALU_SP_fcn(uint16_t stack_pointer, uint2_t *spO)
{
    // stiva creste invers in memorie
    //  presupun ca daca spO e 0, nu am operatie cu stack
    // presupun ca daca spO e 1, am PUSH
    //  presupun ca daca spO e 2, am POP => return current address
    if (spO->x > 0)
    {
        if (1U == spO->x)
        {
            stack_pointer--;
        }
    }
    return stack_pointer;
}

uint16_t stack_pointer_fcn(uint2_t *spO)
{
    // stackul incepe in memorie de la adresa 399, deci 400-1

    stack_pointer_address = ALU_SP_fcn(stack_pointer_address, spO);

    printf("Stack pointer-ul are adresa: %d\n", stack_pointer_address);
    return stack_pointer_address;
}
