L1: EQU 1
L2: 
EQU 0
L3: EQU 10
SECTION TEXT
INPUT N
LOAD L1
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