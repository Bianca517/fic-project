#include "header.h"

void instruction_memory_fcn(uint16_t program_counter, uint6_t *instruction_register, uint10_t *arguments)
{
    // asta e byte code generat de asamblor; TBD: cum il dam ca input fara sa l hardcodam?
    static char instructions[] = "010011000000010001010110000000100000010101110000000001101000100000000";

    // program counterul e numarul instructiunii curente...instructiunea e pe 16 biti
    // deci pozitia din instructions la care se gaseste instr curenta e &instructions + 16 * PC
    char current_instruction[17];
    strncpy(current_instruction, instructions + (program_counter * 16), 16);
    current_instruction[17] = '\0';
    // printf("%s\n", current_instruction);

    uint16_t current_instruction_u16 = 0;
    uint32_t multiplier = 1;
    int i;
    for (i = 0xF; i >= 0; i--)
    {
        current_instruction_u16 += multiplier * (uint16_t)(current_instruction[i] - '0');
        // printf("%c %d %d\n", current_instruction[i], multiplier, current_instruction_u16);
        multiplier *= 2;
    }

    // printf("%d\n", current_instruction_u16);
    (*arguments).x = current_instruction_u16 & 0x3FF;                   // primii 10 biti LSB
    (*instruction_register).x = (current_instruction_u16 >> 10) & 0x3F; // primii 6 biti MSB
    // printf("%x %d %d\n", current_instruction_u16, (*instruction_register).x, (*arguments).x);
}

uint10_t arguments_register_fcn(uint10_t arguments)
{
    uint10_t register_arg;
    register_arg = arguments;
    return register_arg;
}

uint6_t instruction_register_fcn(uint6_t instruction)
{
    uint6_t register_instr;
    register_instr = instruction;
    return register_instr;
}