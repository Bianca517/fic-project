#include "header.h"
#include "opcodes.h"

void control_unit_fcn(uint6_t instruction, bool *next, bool *br_oth, uint6_t *aluOp, bool *LSE, bool *LDM, bool *LACC, bool *ABS, uint2_t *spO, bool *LDR_STR)
{
    // SP OP
    spO->x = 0U;
    if (PSH == instruction.x)
    { // PSH
        spO->x = 1U;
    }
    else if (POP == instruction.x)
    { // POP
        spO->x = 2U;
    }

    if (BRZ <= instruction.x && RET >= instruction.x)
    { // BRANCH
        (*br_oth) = true;
        // if BRA, also activate ABS (always branch signal)
        if (BRA == instruction.x)
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

    if (ADD <= instruction.x && DEC >= instruction.x)
    { // ARITM OR LOGIC OP
        (*aluOp).x = instruction.x;

        // if there is an opcode with immediate value => we need to perform an ALU op with the immd value =>
        //=> extend it from 9bit to 16bit
        (*LSE) = true;
    }
    else
    {
        (*LSE) = false;
        (*aluOp).x = 0U;
    }

    if (LDR == instruction.x || STR == instruction.x)
    {
        *LDR_STR = true;
        if (LDR == instruction.x)
        { // LDR
            (*LDM) = true;
        }
        else
        {
            (*LDM) = false;
        }
    }
    else
    {
        *LDR_STR = false;
    }

    printf("Control Signals:\n");
    printf("NEXT BR/!OTH ALU_OP LDR_STR SP_OP LDM LSE LACC ABS: %d %d %d %d %d %d %d %d %d\n",
           *next, *br_oth, aluOp->x, *LDR_STR, spO->x, *LDM, *LSE, *LACC, *ABS);
}