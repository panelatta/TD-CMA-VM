DATA SEGMENT
    db 03H, 02H, 10H
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA
START:
    MOV AX, DATA
    MOV DS, AX
    
    ADD AX, 1
    MOV AX, 400CH
    INT 21H
CODE ENDS
    END START