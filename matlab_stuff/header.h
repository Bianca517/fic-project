#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// uint pe 6 biti...idk daca merge dar am nevoie pt opcode
typedef struct uint6_t
{
    int x : 6;
} uint6_t;
typedef struct uint10_t
{
    int x : 10;
} uint10_t;
typedef struct uint9_t
{
    int x : 9;
} uint9_t;

uint16_t ALU_SP_fcn(uint16_t stack_pointer_from_SP_reg, uint8_t spO);
uint16_t stack_pointer_fcn(uint16_t stack_pointer_value_from_ALU);

void control_unit_fcn(uint8_t instruction, bool *next, bool *br_oth, bool *aluOp, bool *LSE, bool *LDM, bool *LACC, bool *ABS, bool *spO);
void flags_fcn(uint8_t ZF, uint8_t NF, uint8_t CF, uint8_t OF);

void instruction_memory_fcn(uint16_t program_counter, uint6_t *instruction_register, uint10_t *arguments);
uint6_t instruction_register_fcn(uint6_t instruction);
uint10_t arguments_register_fcn(uint10_t arguments);
void read_machine_code();

uint16_t program_counter_fcn(uint32_t clk, uint8_t PC_from_ALU, bool always_branch_signal, bool jmp_signal, uint16_t address);
uint16_t ALU_PC_fcn(uint16_t PC_value, bool next_signal);
void Demux(bool BR_or_OTH, uint10_t arguments, uint10_t *Y0, uint10_t *Y1);
uint16_t sign_extend_10_to_16_fcn(uint32_t clk, uint10_t input);

uint16_t main_ALU_fcn(bool aluOp, uint16_t opA, uint16_t opB, uint8_t signalControl);
uint16_t sgn_extend_fct(int input);
uint16_t sgn_extend1_fct(uint8_t input);
uint16_t accumulator_fcn(uint16_t a, uint16_t b, uint16_t inp, uint8_t signalControl);
uint16_t data_memory_fcn(uint16_t inp1, uint16_t inp2, uint16_t inp3);

uint16_t register_file_fcn(uint8_t inp1, uint16_t inp2, uint16_t inp3, uint16_t inp4);
uint16_t sign_extend_9_to_16_fcn(uint32_t clk, uint9_t input);
void Demux2(uint10_t arguments, bool *reg_sel, uint9_t *immediate);

// FOR DEBUG PURPOSES
void show_bits(uint16_t a);