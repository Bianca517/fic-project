from enum import Enum

#### CONSTANTS ####
PATH_TO_ASM_FILE = "assembly_code.txt"

#### VARIABLES ####
class Flags(Enum):
    zeroFlag = 0
    negativeFlag = 1
    carryFlag = 2
    overflowFlag = 3
    
accumulator_s16 = 0
regX_s16 = 0
regY_s16 = 0
regFlag_u8 = 0





