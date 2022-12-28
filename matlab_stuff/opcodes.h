#define HLT 0b000000

#define ADD 0b000001
#define SUB 0b000010
#define LSR 0b000011
#define LSL 0b000100
#define RSR 0b000101
#define RSL 0b000110
#define MOV 0b000111
#define MUL 0b001000
#define DIV 0b001001
#define MOD 0b001010
#define AND 0b001011
#define OR 0b001100
#define XOR 0b001101
#define NOT 0b001110
#define CMP 0b001111
#define TST 0b010000
#define INC 0b010001
#define DEC 0b010010

#define STR 0b011110
#define LDR 0b011111

#define PSH 0b100000
#define POP 0b100001

#define BRZ 0b100010
#define BRN 0b100011
#define BRC 0b100100
#define BRO 0b100101
#define BRA 0b100110
#define JMP 0b100111
#define RET 0b101000

//with immediate 
#define ADDI 0b010011
#define SUBI 0b010100
#define MOVI 0b010101
#define MULI 0b010110
#define DIVI 0b010111
#define MODI 0b011000
#define ANDI 0b011001
#define ORI 0b011010
#define XORI 0b011011
#define CMPI 0b011100
#define TSTI 0b011101
