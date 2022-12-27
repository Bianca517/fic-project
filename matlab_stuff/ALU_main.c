#include "header.h"

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