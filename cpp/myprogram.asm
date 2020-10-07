

L1:   	EQU 		1


L2: ;blasjdhljacl ashdcgqyweglcajkb 		ksjdhlfakjs


EQU 0



section    			TEXT

SWAP: MACRO &A, &B, &T
	COPY &A, &T
	COPY &B, &A
	COPY &T, &B
	ENDMACRO

IF L1
	LOAD SPACE ;faz esta opera¸c~ao se L1 for verdadeiro

if l2
	INPUT SPACE ;faz esta opera¸c~ao se L2 for verdadeiro

input n
LOAD N
FAT: SUB ONE
JMPZ FIM
STORE AUX
MULT N
STORE N
LOAD AUX
jmp fat
FIM: OUTPUT N
STOP
SECTION DATA
AUX: SPACE
N: SPACE
ONE: CONST 1