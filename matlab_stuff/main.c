#include "header.h"

uint16_t alu_stack_pointer_fcn(uint16_t stack_pointer_from_SP_reg, uint8_t spO)
{
    // stiva creste invers in memorie
    //  presupun ca daca spO e 0, am PUSH
    //  presupun ca daca spO e 1, am POP
    if (0U == spO)
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

uint16_t alu1_fcn(uint16_t opA, uint16_t opB, uint8_t signalControl)
{
    uint16_t result;
    uint16_t bits = 1;
    uint16_t mask;
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
    return result;
}

uint16_t alu_fcn(uint8_t *PC, uint8_t signalControl)
{
    if (signalControl == 0)
    {
        (*PC)--;
    }
    if (signalControl == 1)
    {
        (*PC)++;
    }
    return *PC;
}

uint16_t pc_fcn(uint8_t *PC, uint8_t signalControl)
{
    uint16_t counter = alu_fcn(PC, signalControl);
    return counter;
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

int main()
{
    return 0;
}