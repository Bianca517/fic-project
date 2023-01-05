#include "header.h"
#include "opcodes.h"

bool *br_oth;
bool *ABS_signal;
bool *JMP_signal;
bool *NEXT_signal;
bool *LSE_signal;
bool *LDM_signal;
bool *LACC_signal;
uint2_t *SPO_signal;
uint6_t *ALU_OP_signal;

bool ZF, CF, NF, OF;

uint10_t arguments;
bool *reg_sel;
uint9_t *immediate_u9;
uint16_t immediate_u16, ALU_result_u16, accumulator_value_u16;

int sgn_extend_8_to_9(uint8_t input)
{
    if (input & (1 << 7))
    {
        input |= 1 << 8;
    }
    return input;
}

uint16_t sgn_extend_fct(int input)
{
    input = sgn_extend_8_to_9(input);
    // if the 9th bit (the most significant bit) is 1, then the number is negative
    if (input & (1 << 8))
    {
        input |= 0b111111111 << 9;
    }
    return input;
}

uint16_t sgn_extend_8_to_10(uint8_t input)
{
    if (input >> 7)
    {
        /* sign bit is set, so fill in the upper bits with 1s */
        return input | 0xFC00;
    }
    else
    {
        return input;
    }
}

uint16_t sgn_extend1_fct(uint8_t input)
{
    if (input >> 9)
    {
        /* sign bit is set, so fill in the upper bits with 1s */
        return input | 0xFC00;
    }
    else
    {
        return input;
    }
}

void show_bits(uint16_t a)
{
    int8_t i;
    for (i = 15; i >= 0; i--)
    {
        printf("%d", (a >> i) & 1);
    }
}

int main()
{
    double clk;
    uint16_t current_instruction, current_register;
    uint6_t current_opcode;
    read_machine_code();
    // while
    current_instruction = instruction_memory_fcn(0);
    arguments = arguments_register_fcn(current_instruction);
    current_opcode = instruction_register_fcn(current_instruction);

    // control unit
    uint10_t *Y0, *Y1;
    Y0 = malloc(sizeof(uint10_t));
    Y1 = malloc(sizeof(uint10_t));
    Demux(false, arguments, Y0, Y1); // baga br_othr

    if (!br_oth)
    {
        // STACK POINTER
        SPO_signal = malloc(sizeof(uint2_t));
        SPO_signal->x = 1u;

        stack_pointer_fcn(SPO_signal); // baga spo signal

        // ALU
        reg_sel = malloc(sizeof(bool));
        immediate_u9 = malloc(sizeof(uint9_t));
        Demux2(*Y1, reg_sel, immediate_u9);
        immediate_u16 = sign_extend_9_to_16_fcn(true, *immediate_u9);
        current_register = register_file_fcn(1U, reg_sel, 5U, 6U, true, false, false, 7U);
        ALU_OP_signal = malloc(sizeof(uint6_t));
        ALU_OP_signal->x = 19U;
        ALU_result_u16 = main_ALU_fcn(*ALU_OP_signal, current_register, immediate_u16);
        accumulator_value_u16 = accumulator_register_fcn(ALU_result_u16);
        flags_register_fcn(&ZF, &NF, &CF, &OF);
        bool c1 = current_opcode.x & (1 << 1);
        bool c0 = current_opcode.x & 1;
        Mux_flags(ZF, NF, CF, OF, br_oth, c1, c0);
    }

    // la final
    program_counter_fcn(true, false, false, sign_extend_10_to_16_fcn(true, arguments)); // bagat clk

    return 0;
}