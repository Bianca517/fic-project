#include "header.h"

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