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

uint16_t cmp(uint16_t opA, uint16_t opB)
{
    if (opA < opB)
    {
        return -1;
    }
    if (opA == opB)
    {
        return 0;
    }
    else
        return 1;
}

uint16_t tst(uint16_t operand, uint16_t mask)
{
    return (operand & mask) != 0;
}

uint16_t main_ALU_fcn(bool aluOp, uint16_t opA, uint16_t opB, uint8_t signalControl)
{
    uint16_t result;
    uint16_t bits = 1;
    uint16_t mask;
    if (aluOp)
    {
        switch (signalControl)
        {
        case 0:
            // perform the addition operation
            result = opA + opB;
            break;
        case 1:
            // perform the subtraction operation
            result = opA - opB;
            break;
        case 2:
            // perform the logical shift right operation
            result = result >> bits;
            break;
        case 3:
            // perfrom the logical shift left operation
            result = result << bits;
            break;
        case 4:
            // perform the RSR operation
            // var pt MSB = (result & 1) << 15;
            // result = result >> 1;
            // result = result | MSB
            break;
        case 5:
            // perform the RSL operation
            result = result << bits;
            break;
        case 6:
            // perform the MOV operation
            break;
        case 7:
            // perform the MUL operation
            result = opA * opB;
            break;
        case 8:
            // perform the DIV operation
            if (opA != 0 && opB == 0)
            {
                result = opB / opA;
            }
            if (opB != 0 && opA == 0)
            {
                result = opA / opB;
            }
            if (opA == 0 && opB == 0)
            {
                // error code to signal the fact that the operation was not possible
                result = -1;
            }
            result = opA / opB;
            break;
        case 9:
            // perform the MOD operation
            result = opA % opB;
            break;
            /*
        case 9:
            // perform the AND operation
            result = opA & opB;
            break;*/
        case 10:
            // perform the OR operation
            result = opA | opB;
            break;
        case 11:
            // perform the XOR operation
            result = opA ^ opB;
            break;
        case 12:
            // perform the NOT operation on the first operand
            result = ~opA;
            break;
        case 13:
            // perform the NOT operation on the second operand
            result = ~opB;
            break;
        case 14:
            // perform the CMP operation
            result = cmp(opA, opB);
            break;
        case 15:
            // perform the TST operation on the first operand
            result = tst(opA, mask);
            break;
        case 16:
            // perform the TST operation on the second operand
            result = tst(opB, mask);
            break;
        case 17:
            // perform the INC operation on the first operand
            result = opA + 1;
            break;
        case 18:
            // perform the INC operation on the second operand
            result = opB + 1;
            break;
        case 19:
            // perform the DEC operation on the first operand
            result = opA - 1;
            break;
        case 20:
            // perform the DEC operation on the second operand
            result = opB - 1;
            break;
        default:
            // if the control signals are not recognised, return 0
            result = 0;
        }
    }
    return result;
}

uint16_t ALU_PC_fcn(uint16_t PC_value, bool next_signal)
{
    // only if next signal is active, increment the program counter
    // else, leave it like this because it means we have branch => take into consideration the given address
    if (true == next_signal)
    {
        PC_value++;
    }

    return PC_value;
}

uint16_t program_counter_fcn(uint32_t clk, uint8_t PC_from_ALU, bool always_branch_signal, bool jmp_signal, uint16_t address)
{
    uint16_t PC_to_return = 0U;

    if (clk)
    {
        if (always_branch_signal || jmp_signal)
        {
            PC_to_return = address;
        }
        else
        {
            PC_to_return = PC_from_ALU;
        }
    }

    return PC_to_return;
}

void Demux(bool BR_or_OTH, uint10_t arguments, uint10_t *Y0, uint10_t *Y1)
{
    // if BR_or_OTH is true => BR => Y0 active
    // if BR_or_OTH is false => OTH => Y1 active
    if (true == BR_or_OTH)
    {
        (*Y0).x = arguments.x; //"arguments" represents a 10 bit address
        // leave Y1 to HI-Z
    }
    else
    {
        (*Y1).x = arguments.x;
        // leave Y0 to Hi-Z
    }
}

void Demux2(uint10_t arguments, bool *reg_sel, uint9_t *immediate)
{
    *reg_sel = (arguments.x >> 9) & 0x001 ? true : false; // msb is 1 => true, else false
    (*immediate).x = arguments.x & 0x1FF;
}

uint16_t sign_extend_10_to_16_fcn(uint32_t clk, uint10_t input)
{
    uint16_t output;
    if (clk)
    {
        output = 0U;
        uint8_t i;
        for (i = 15; i >= 10; i--)
        {
            output |= ((input.x & (1 << 9)) << i);
        }
        output |= input.x;
        // show_bits(output);
    }
    return output; // leave output on Hi-Z if not synced with clk
}

uint16_t sign_extend_9_to_16_fcn(uint32_t clk, uint9_t input)
{
    uint16_t output;
    if (clk)
    {
        output = 0U;
        uint8_t i;
        for (i = 15; i >= 9; i--)
        {
            output |= ((input.x & (1 << 9)) << i);
        }
        output |= input.x;
        // show_bits(output);
    }
    return output; // leave output on Hi-Z if not synced with clk
}
/*
uint16_t accumulator_fcn(uint16_t a, uint16_t b, uint16_t inp, uint8_t signalControl)
{
    inp = alu1_fct(a, b, signalControl);
    return value;
}*/

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

uint16_t data_memory_fcn(uint16_t inp1, uint16_t inp2, uint16_t inp3)
{
}

uint16_t register_file_fcn(uint8_t inp1, uint16_t inp2, uint16_t inp3, uint16_t inp4)
{
}

void control_unit_fcn(uint8_t instruction, bool *next, bool *br_oth, bool *aluOp, bool *LSE, bool *LDM, bool *LACC, bool *ABS, bool *spO)
{
    // SP OP
    if (0b100000 == instruction)
    { // PSH
        (*spO) = false;
    }
    else if (0b100001 == instruction)
    { // POP
        (*spO) = true;
    }

    if (0b100010 <= instruction && 0b101000 >= instruction)
    { // BRANCH
        (*br_oth) = true;
        // if BRA, also activate ABS (always branch signal)
        if (0b100110 == instruction)
        {
            (*ABS) = true;
        }
        else
        {
            (*ABS) = false;
        }
        (*next) = false;
    }
    else
    {
        (*br_oth) = false;
        (*next) = true;
    }

    if (0b000001 <= instruction && 0b011101 >= instruction)
    { // ARITM OR LOGIC OP
        (*aluOp) = instruction;

        // if there is an opcode with immediate value => we need to perform an ALU op with the immd value =>
        //=> extend it from 9bit to 16bit
        if (0b010011 <= instruction && 0b011101 >= instruction)
        {
            (*LSE) = true;
        }
        else
        {
            (*LSE) = false;
        }
    }
    else
    {
        (*aluOp) = false;
    }

    if (0b011111 == instruction)
    { // LDR
        (*LDM) = 1U;
    }
}

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
    /*
    uint6_t IR;
    uint10_t AR;
    instruction_memory_fcn(1, &IR, &AR);
    */

    return 0;
}