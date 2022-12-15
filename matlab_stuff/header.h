#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
typedef enum
{
    FALSE = 0U,
    TRUE = 1U
} boolean;

// uint pe 6 biti...idk daca merge dar am nevoie pt opcode
typedef struct uint6_t
{
    int x : 6;
} uint6_t;
typedef struct uint10_t
{
    int x : 10;
} uint10_t;

uint16_t ALU_SP_fcn(uint16_t stack_pointer_from_SP_reg, uint8_t spO);
uint16_t stack_pointer_fcn(uint16_t stack_pointer_value_from_ALU);
void control_unit_fcn(uint8_t instruction, boolean *next, boolean *br_oth, boolean *aluOp, boolean *LSE, boolean *LDM, boolean *LACC, boolean *ABS, boolean *spO);
void flags_fcn(uint8_t ZF, uint8_t NF, uint8_t CF, uint8_t OF);

void instruction_memory_fcn(uint16_t program_counter, uint6_t *instruction_register, uint10_t *arguments);
void iregister_fcn(uint6_t *IR);
void aregister_fcn(uint10_t *AR);

uint16_t pc_fcn(uint8_t *PC, uint8_t signalControl);
uint16_t main_ALU_fcn(boolean aluOp, uint16_t opA, uint16_t opB, uint8_t signalControl);
uint16_t ALU_PC_fcn(uint8_t *PC, uint8_t signalControl);
uint16_t sgn_extend_fct(int input);
uint16_t sgn_extend1_fct(uint8_t input);
uint16_t accumulator_fcn(uint16_t a, uint16_t b, uint16_t inp, uint8_t signalControl);
uint16_t data_memory_fcn(uint16_t inp1, uint16_t inp2, uint16_t inp3);
uint16_t register_file_fcn(uint8_t inp1, uint16_t inp2, uint16_t inp3, uint16_t inp4);
