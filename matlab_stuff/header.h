#include <stdio.h>
#include <stdint.h>

typedef enum
{
    FALSE,
    TRUE
} boolean;

void alu_stack_pointer_fcn(uint16_t *stack_pointer, uint8_t spO);
void stack_pointer_fcn(uint16_t *stack_pointer);
void control_unit_fcn(uint8_t a, uint8_t b);