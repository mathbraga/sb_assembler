

L1:   	EQU 		1


L1: ;blasjdhljacl ashdcgqyweglcajkb 		ksjdhlfakjs


EQU 0


SECTION    			TEXT

SWAP: MACRO &A, &B, &T
	COPY &A, &T
	COPY &B, &A
	COPY &T, &B
	ENDMACRO

IF L1
	LOAD SPACE ;faz esta opera¸c~ao se L1 for verdadeiro

IF L2
	INPUT SPACE ;faz esta opera¸c~ao se L2 for verdadeiro

INPUT N
LOAD N
FAT: SUB ONE
JMPZ FIM
STORE AUX
MULT N
STORE N
LOAD AUX
JMP FAT
FIM: OUTPUT N
STOP
SECTION DATA
AUX: SPACE
N: SPACE
ONE: CONST 1
