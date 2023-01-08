#include "header.h"

static char *instructions;
static uint10_t arguments_register;
static uint6_t instruction_register;

uint16_t instruction_memory_fcn(uint16_t program_counter)
{
    // program counterul are adresa instructiunii curente...instructiunea e pe 16 biti
    // deci pozitia din instructions la care se gaseste instr curenta e &instructions + PC * 8biti
    // printf("in funct %s\n", instructions);
    if ((program_counter * 8) >= strlen(instructions))
    {
        return 0;
    }

    char current_instruction[16] = "";
    strncpy(current_instruction, instructions + (program_counter * 8), 16);
    current_instruction[16] = '\0';
    fprintf(output_file, "Current instruction to decode: %s\n", current_instruction);

    // from char to int
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
    return current_instruction_u16;
}

uint10_t arguments_register_fcn(uint16_t instruction)
{
    arguments_register.x = instruction & 0x3FF; // primii 10 biti LSB
    fprintf(output_file, "Arguments register is: 0x%x \n", arguments_register.x);
    return arguments_register;
}

uint6_t instruction_register_fcn(uint16_t instruction)
{
    instruction_register.x = (instruction >> 10) & 0x3F; // primii 6 biti MSB
    fprintf(output_file, "Instruction register is: 0x%x\n", instruction_register.x);
    return instruction_register;
}

void read_machine_code()
{
    uint8_t cInstructionSize = 16U;
    char path_to_code[] = "../output_byte_code.txt", *buffered_read_string = NULL, *aux = NULL, instruction[17];
    FILE *input_file;
    uint8_t read_string_size = 0U;

    input_file = fopen(path_to_code, "r");

    if (!input_file)
    {
        printf("Could not open input file!\n");
        exit(EXIT_FAILURE);
    }

    while (true)
    {
        fgets(instruction, cInstructionSize + 1, input_file);

        if (feof(input_file))
            break;
        fgetc(input_file); // endl

        aux = realloc(buffered_read_string, (read_string_size + cInstructionSize + 1U) * sizeof(char));
        CHECK_ALLOCATION(aux);

        buffered_read_string = aux;

        if (!read_string_size)
        {
            strcpy(buffered_read_string, instruction);
        }
        else
        {
            strcat(buffered_read_string, instruction);
        }
        read_string_size += cInstructionSize;
    }
    instructions = malloc(sizeof(char) * (read_string_size + 1));
    CHECK_ALLOCATION(instructions);
    strcpy(instructions, buffered_read_string);

    instructions[read_string_size] = '\0';
    printf("%s\n", instructions);

    free(buffered_read_string);
    fclose(input_file);
}