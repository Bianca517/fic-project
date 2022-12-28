#include "header.h"
#include "opcodes.h"

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

uint16_t register_file_fcn(uint32_t clk, bool reg_select, uint16_t accumulator, uint16_t data_memory, bool LSE, bool LDM, bool LACC, uint16_t ext_immediate)
{
}