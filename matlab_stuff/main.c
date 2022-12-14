#include "header.h"

void alu_stack_pointer_fcn(uint16_t *stack_pointer, uint8_t spO)
{
    // presupun ca daca spO e 0, incr SP
    // presupun ca daca spO e 1, decr SP
    if (0U == spO)
    {
        (*stack_pointer)++;
    }
    if (1U == spO)
    {
        (*stack_pointer)--;
    }
}

uint16_t stack_pointer_fcn(uint16_t stack_pointer_value_from_ALU) 
{
    uint16_t stack_pointer_register = 0U;

    stack_pointer_register = stack_pointer_value_from_ALU;

    return stack_pointer_register;
}

int main()
{
    return 0;
}