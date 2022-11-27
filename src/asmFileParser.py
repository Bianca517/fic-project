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


def parse_asm_line(line):
    words_in_line = re.split(" |, ", line)
    print(words_in_line)
    operation_index = 0 if is_operation(words_in_line[0]) else 1
    operation = words_in_line[operation_index]
    opcode = get_opcode(operation)
    termen1 = int(words_in_line[operation_index + 1])
    termen2 = int(words_in_line[operation_index + 2])
    print(opcode + bin(termen1) + bin(termen2))


def open_and_parse_file():
    code_file = open(header.PATH_TO_ASM_FILE, "r")
    line_to_decode = code_file.readline()
    while(line_to_decode):
        parse_asm_line(line_to_decode)
        line_to_decode = code_file.readline()
        if ("" == line_to_decode):
            break
