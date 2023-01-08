from src import header
from input_data import opcodes 
import re

LABEL_DICT = {}

def get_opcode(operation, is_operation_with_immediate):
    if is_operation_with_immediate:
        key_list = list(opcodes.opcodes_with_immediate_dict.keys())
        val_list = list(opcodes.opcodes_with_immediate_dict.values())
    else:
        key_list = list(opcodes.opcodes_dict.keys())
        val_list = list(opcodes.opcodes_dict.values())

    operation_position = key_list.index(operation)
    opcode = val_list[operation_position]
    return opcode


def is_operation(string):
    key_list1 = list(opcodes.opcodes_dict.keys())
    key_list2 = list(opcodes.opcodes_with_immediate_dict.keys())
    return ((string in key_list1) or (string in key_list2))


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
    global LABEL_DICT
    #termen might have Rx format or #N; 
    binary_code = 0
    if '#' in string:
        binary_code = get_binary_code_for_immediate(string)
    elif 'R' in string:
        binary_code = get_binary_code_for_register(string)
    elif string in LABEL_DICT.keys():
        #get address
        binary_code = LABEL_DICT[string]
    return binary_code


def write_output(output_file, opcode, termens_arr):
    print(opcode)
    output_file.write(opcode)

    for termen in termens_arr:
        print(termen)
        output_file.write(str(termen))
        
    output_file.write('\n')

def get_instruction_number_formatted(instruction_number):
    return bin(instruction_number)[2:].zfill(10)

def parse_asm_line(line, output_file, instruction_number):
    global LABEL_DICT
    termens_arr = []
    is_operation_with_immediate = ('#' in line)
    words_in_line = re.split(" |, ", line)
    print(words_in_line)
    #if there is a label, the opcode is on index 1 in the line
    operation_index = 0 if is_operation(words_in_line[0]) else 1

    if(operation_index == 1): #we have label => add it to dict
        ten_bit_instruction_number = get_instruction_number_formatted(instruction_number)
        LABEL_DICT.update({words_in_line[0]: ten_bit_instruction_number})

    operation = words_in_line[operation_index]
    opcode = get_opcode(operation, is_operation_with_immediate)

    #index through the rest of termens in the line
    for index in range (operation_index + 1, len(words_in_line)):
        #termen might be immediate value or register or label
        termen = get_termen(words_in_line[index])
        termens_arr.append(termen)

    write_output(output_file, opcode, termens_arr)


def open_and_parse_file():
    output_file = open(header.PATH_TO_OUTPUT_FILE, "w")
    code_file = open(header.PATH_TO_ASM_FILE, "r")

    instruction_number = 0
    line_to_decode = code_file.readline()
    while(line_to_decode):
        #get rid of the last endl
        if line_to_decode[-1] == '\n':
            line_to_decode = line_to_decode[:-1]

        parse_asm_line(line_to_decode, output_file, instruction_number)
        instruction_number = instruction_number + 2 #bcz the program count is din 2 in 2
        #read new line and break if eof
        line_to_decode = code_file.readline()
        if ("" == line_to_decode):
            break
