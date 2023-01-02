#include "header.h"
#include "opcodes.h"

void Demux2(uint10_t arguments, bool *reg_sel, uint9_t *immediate)
{
    *reg_sel = (bool)((arguments.x >> 9) & 0x001); // msb is 1 => true, else false
    printf("Registrul: %s\n", *reg_sel == false ? "Rx" : "Ry");
    immediate->x = arguments.x & 0x01FF;
    printf("Valoarea immediate: %d\n", immediate->x);
}

uint16_t sign_extend_9_to_16_fcn(double clk, uint9_t input)
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

uint16_t register_file_fcn(double clk, bool reg_select, uint16_t accumulator, uint16_t data_memory, bool LSE, bool LDM, bool LACC, uint16_t ext_immediate)
{
}

uint16_t data_memory_fcn(uint16_t register_value, uint16_t stack_pointer_value, uint16_t immediate_sgn_ext)
{
}