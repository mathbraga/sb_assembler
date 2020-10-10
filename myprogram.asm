cond: equ 1

;fatorial

SECTION TEXT
MUL_N: MACRO ;basjdcbajksdjksvdh
MULT N
        STORE N          
ENDMACRO
		INPUT N
LOAD N
FAT: SUB ONE;asdlcjhbalkjxblsjdbhc
JMPZ FIM
STORE AUX
MUL_N 
LOAD AUX
IF cond
JMP         FAT
FIM: OUTPUT        N
STOP
		SECTION DATA
AUX: SPACE
N: SPACE		
ONE: CONST 1