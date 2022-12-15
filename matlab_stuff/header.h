#include <stdio.h>
#include <stdint.h>

typedef enum
{
    FALSE,
    TRUE
} boolean;

void alu_stack_pointer_fcn(uint16_t *stack_pointer, uint8_t spO);
void stack_pointer_fcn(uint16_t *stack_pointer);
void control_unit_fcn(uint8_t control_unit);
void flags_fcn(uint8_t ZF, uint8_t NF, uint8_t CF, uint8_t OF);
void instruction_memory_fcn(uint8_t a, uint8_t b);
uint16_t pc_fcn(uint8_t *PC,uint8_t signalControl);
uint16_t alu1_fcn(uint16_t opA, uint16_t opB, uint8_t signalControl, uint8_t *zFlag);
uint16_t alu_fcn(uint8_t *PC, uint8_t signalControl);
uint16_t sgn_extend_fct(uint8_t input);
uint16_t sgn_extend1_fct(uint8_t input);
uint16_t accumulator_fcn(uint16_t a, uint16_t b, uint16_t inp,uint8_t signalControl);
uint16_t data_memory_fcn(uint16_t inp1, uint16_t inp2, uint16_t inp3);
uint16_t register_file_fcn(uint8_t inp1, uint16_t inp2, uint16_t inp3, uint16_t inp4);
void iregister_fcn(uint8_t a, uint8_t b);
void aregister_fcn(uint8_t a, uint8_t b);