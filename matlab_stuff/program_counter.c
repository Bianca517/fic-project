#include "header.h"

static uint16_t program_counter = 0U;

uint16_t ALU_PC_fcn(uint16_t PC_value, bool next_signal)
{
    // only if next signal is active, increment the program counter
    // else, leave it like this because it means we have branch => take into consideration the given address
    if (true == next_signal)
    {
        PC_value += 2; // instructiunile sunt pe 2 bytes
    }

    return PC_value;
}

uint16_t program_counter_fcn(double clk, bool always_branch_signal, bool jmp_signal, uint16_t address)
{
    if (clk)
    {
        if (always_branch_signal || jmp_signal)
        {
            program_counter = address;
        }
        else
        {
            // program_counter = PC_from_ALU;
            program_counter = ALU_PC_fcn(program_counter, true);
        }
    }

    printf("Program counter-ul curent este: %d", program_counter);
    return program_counter;
}

uint16_t sign_extend_10_to_16_fcn(double clk, uint10_t input)
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

    printf("Iesirile Y0 si Y1 din Demux sunt %d si %d\n", (*Y0).x, (*Y1).x);
}