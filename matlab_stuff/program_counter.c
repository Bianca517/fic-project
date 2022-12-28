#include "header.h"

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
