#include "header.h"

static char *instructions;

void instruction_memory_fcn(uint16_t program_counter, uint6_t *instruction_register, uint10_t *arguments)
{
    // program counterul are adresa instructiunii curente...instructiunea e pe 16 biti
    // deci pozitia din instructions la care se gaseste instr curenta e &instructions + PC * 8biti
    printf("in funct %s\n", instructions);
    char current_instruction[16];
    strncpy(current_instruction, instructions + (program_counter * 8), 16);
    current_instruction[16] = '\0';
    printf("%s\n", current_instruction);

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
    (*arguments).x = current_instruction_u16 & 0x3FF;                   // primii 10 biti LSB
    (*instruction_register).x = (current_instruction_u16 >> 10) & 0x3F; // primii 6 biti MSB
    printf("%x %d %d\n", current_instruction_u16, (*instruction_register).x, (*arguments).x);
}

uint10_t arguments_register_fcn(uint10_t arguments)
{
    uint10_t register_arg;
    register_arg = arguments;
    return register_arg;
}

uint6_t instruction_register_fcn(uint6_t instruction)
{
    uint6_t register_instr;
    register_instr = instruction;
    return register_instr;
}

void read_machine_code()
{
    char path_to_code[] = "../output_byte_code.txt", *read_string = NULL, *aux = NULL, instruction[17];
    FILE *input_file;
    int read_string_size = 0;

    input_file = fopen(path_to_code, "r");

    if (!input_file)
    {
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        fgets(instruction, 17, input_file);
        if (feof(input_file))
        {
            break;
        }
        fgetc(input_file); // take the endl

        aux = (char *)realloc(read_string, sizeof(char) * (read_string_size + strlen(instruction) + 1));

        if (!aux)
        {
            exit(EXIT_FAILURE);
        }
        read_string = aux;

        if (!read_string_size)
        {
            strcpy(read_string, instruction);
        }
        else
        {
            strcat(read_string, instruction);
        }
        read_string_size += 16;
    }

    read_string[strlen(read_string)] = '\0';
    instructions = (char *)malloc(sizeof(read_string));
    strcpy(instructions, read_string);
    printf("%s\n", instructions);

    free(aux);
    free(read_string);
}