#include "header.h"

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