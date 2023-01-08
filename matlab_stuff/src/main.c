#include "header.h"
#include "opcodes.h"

bool ZF, CF, NF, OF;

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

void show_content_of_data_memory(uint16_t *memory)
{
    printf("Data memory: ");
    uint8_t i;
    for (i = 0; i < DATA_MEMORY_SIZE; i++)
    {
        printf("%d ", memory[i]);
    }
    printf("\n");
}

void initialization(bool *BR_OTH_signal, bool *ABS_signal, bool *JMP_signal, bool *NEXT_signal, bool *LSE_signal, bool *LDM_signal, bool *LACC_signal, bool *LDR_STR, uint2_t *SPO_signal, uint6_t *ALU_OP_signal, uint16_t *result_from_data_memory)
{
    *BR_OTH_signal = false;
    *ABS_signal = false;
    *JMP_signal = false;
    *NEXT_signal = false;
    *LSE_signal = false;
    *LDM_signal = false;
    *LACC_signal = false;
    *LDR_STR = false;
    SPO_signal->x = 0u;
    ALU_OP_signal->x = 0u;

    ZF = false;
    CF = false;
    NF = false;
    OF = false;
    *result_from_data_memory = 0U;
    output_file = fopen("output_file.txt", "w");

    if (!output_file)
    {
        printf("Could not open output_file\n");
        exit(EXIT_FAILURE);
    }
}

int main()
{
    uint16_t *memory = NULL;
    uint16_t *program_counter = NULL;

    bool BR_OTH_signal, ABS_signal, JMP_signal, NEXT_signal, LSE_signal, LDM_signal, LACC_signal, LDR_STR;
    uint2_t SPO_signal;
    uint6_t ALU_OP_signal;

    uint10_t arguments, Y0, Y1;
    bool reg_sel;
    uint9_t immediate_u9;
    uint16_t immediate_u16, ALU_result_u16, accumulator_value_u16, result_from_data_memory, current_instruction, current_register, stack_pointer_address;
    uint6_t current_opcode;

    double clk = 1U;

    initialization(&BR_OTH_signal, &ABS_signal, &JMP_signal, &NEXT_signal, &LSE_signal, &LDM_signal, &LACC_signal, &LDR_STR, &SPO_signal, &ALU_OP_signal, &result_from_data_memory);

    // allocate the memory
    memory = (uint16_t *)calloc(DATA_MEMORY_SIZE, sizeof(uint16_t));
    CHECK_ALLOCATION(memory);

    // allocate pointers
    program_counter = (uint16_t *)calloc(1U, sizeof(uint16_t));
    CHECK_ALLOCATION(program_counter);

    read_machine_code();

    // printf("after read function\n");
    current_instruction = instruction_memory_fcn(*program_counter);

    while (0U != current_instruction)
    {
        arguments = arguments_register_fcn(current_instruction);
        current_opcode = instruction_register_fcn(current_instruction);
        bool c1 = current_opcode.x & (1 << 1);
        bool c0 = current_opcode.x & 1;

        control_unit_fcn(current_opcode, &NEXT_signal, &BR_OTH_signal, &ALU_OP_signal, &LSE_signal, &LDM_signal, &LACC_signal, &ABS_signal, &SPO_signal, &LDR_STR);

        Demux(BR_OTH_signal, arguments, &Y0, &Y1);

        if (PSH == current_opcode.x || POP == current_opcode.x)
        {
            // STACK POINTER
            stack_pointer_address = stack_pointer_fcn(&SPO_signal);
            *program_counter = program_counter_fcn(clk, *program_counter, ABS_signal, JMP_signal, sign_extend_10_to_16_fcn(true, arguments)); // bagat clk
        }
        else if (LDR == current_opcode.x || STR == current_opcode.x)
        {
            // DATA MEM
            result_from_data_memory = data_memory_fcn(memory, current_opcode, ALU_result_u16, stack_pointer_address, immediate_u16);
            show_content_of_data_memory(memory);
            *program_counter = program_counter_fcn(clk, *program_counter, ABS_signal, JMP_signal, sign_extend_10_to_16_fcn(true, arguments)); // bagat clk
        }
        if (!BR_OTH_signal) // DATA PATH FOR ALU INSTRUCTIONS
        {
            // ALU
            Demux2(Y1, &reg_sel, &immediate_u9);
            immediate_u16 = sign_extend_9_to_16_fcn(clk, immediate_u9);
            current_register = register_file_fcn(clk, reg_sel, accumulator_value_u16, result_from_data_memory, LSE_signal, LDM_signal, LACC_signal, immediate_u16);

            ALU_result_u16 = main_ALU_fcn(ALU_OP_signal, current_register, immediate_u16);
            accumulator_value_u16 = accumulator_register_fcn(ALU_result_u16);
            flags_register_fcn(&ZF, &NF, &CF, &OF);

            JMP_signal = Mux_flags(ZF, NF, CF, OF, BR_OTH_signal, c1, c0);

            *program_counter = program_counter_fcn(clk, *program_counter, ABS_signal, JMP_signal, sign_extend_10_to_16_fcn(true, arguments)); // bagat clk
        }
        else
        {
            // BRANCHES
            flags_register_fcn(&ZF, &NF, &CF, &OF);

            JMP_signal = Mux_flags(ZF, NF, CF, OF, BR_OTH_signal, c1, c0);
            *program_counter = program_counter_fcn(clk, *program_counter, ABS_signal, JMP_signal, sign_extend_10_to_16_fcn(true, arguments)); // bagat clk
        }

        printf("\n----------------------------------------------------------------------------\n");
        current_instruction = instruction_memory_fcn(*program_counter);
    }

    return 0;
}