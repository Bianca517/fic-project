from src import header
from input_data import opcodes 
import re


def get_opcode(operation):
   key_list = list(opcodes.opcodes_list.keys())
   val_list = list(opcodes.opcodes_list.values())
   operation_position = key_list.index(operation)
   opcode = val_list[operation_position]
   return opcode


def is_operation(string):
    key_list = list(opcodes.opcodes_list.keys())
    return (string in key_list)


def get_binary_code_for_immediate(string):
    #get the value without #
    value = (int)(string[1:])
    binary_value = (bin(value))
    #NEGATIVE NUMBERS!!!!
    first_digit = binary_value[0]
    #get rid of the first xb
    binary_value = binary_value[2:]
    binary_value_size = len(binary_value)
    number_of_bits_to_complete = header.IMMEDIATE_VALUE_SIZE - binary_value_size
    nine_bit_immediate_value = ""
    for i in range(0, number_of_bits_to_complete):
        nine_bit_immediate_value += first_digit
    nine_bit_immediate_value += binary_value
    #print(nine_bit_immediate_value)
    return nine_bit_immediate_value 


def get_binary_code_for_register(string):
    one_bit_binary_code = ""
    string = string.upper()
    try:
        register_value = header.REGISTERS[string]
    except:
        register_value = str(0xFFFF)
        return register_value

    one_bit_binary_code = str(register_value)
    #print(one_bit_binary_code)
    return one_bit_binary_code


def get_termen(string):
    #termen might have Rx format or #N; 
    binary_code = 0
    if '#' in string:
        binary_code = get_binary_code_for_immediate(string)
    elif 'R' in string:
        binary_code = get_binary_code_for_register(string)
    return binary_code


def parse_asm_line(line, output_file):
    words_in_line = re.split(" |, ", line)
    print(words_in_line)
    #if there is a label, the opcode is on index 1 in the line
    operation_index = 0 if is_operation(words_in_line[0]) else 1
    operation = words_in_line[operation_index]
    opcode = get_opcode(operation)

    #termen might be immediate value or register
    termen1 = get_termen(words_in_line[operation_index + 1])
    termen2 = get_termen(words_in_line[operation_index + 2])
    print(opcode + " " + termen1 + " " + termen2)
    output_file.write(opcode + termen1 + termen2)


def open_and_parse_file():
    output_file = open(header.PATH_TO_OUTPUT_FILE, "w")
    code_file = open(header.PATH_TO_ASM_FILE, "r")
    line_to_decode = code_file.readline()
    while(line_to_decode):
        parse_asm_line(line_to_decode, output_file)
        line_to_decode = code_file.readline()
        if ("" == line_to_decode):
            break
