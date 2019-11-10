#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "td-cma.h"

/* memory pool and segment head pointers */
extern uint8_t *pool;             // memory pool
extern uint8_t *codeSeg;          // code segment
extern uint8_t *stackSeg;         // stack segment
extern uint8_t *dataSeg;          // data segment
extern uint8_t *extSeg;           // extend segment

/* main registers */
extern struct MainRegister A, B, C, D;
#define AX (A.X)
#define AH (A.H)
#define AL (A.L)
#define BX (B.X)
#define BH (B.H)
#define BL (B.L)
#define CX (C.X)
#define CH (C.H)
#define CL (C.L)
#define DX (D.X)
#define DH (D.H)
#define DL (D.L)

/* index registers */
extern uint8_t  *SI, *DI;
extern uint8_t  *BP, *SP;

/* program counter */
extern uint8_t  *IP;

/* segment registers */
extern uint8_t  *CS, *DS, *ES, *SS;

/* status register */
extern struct PSWFLAGS FLAGS;
#define CF (FLAGS.CF)
#define PF (FLAGS.PF)
#define AF (FLAGS.AF)
#define ZF (FLAGS.ZF)
#define SF (FLAGS.SF)
#define TF (FLAGS.TF)
#define IF (FLAGS.IF)
#define DF (FLAGS.DF)
#define OF (FLAGS.OF)

/* Instructions */
extern enum INSTRUCTION;


void Executor(int isDataSegUsed, int isStackSegUsed, int isExtSegUsed) {
    /* Check pool and segment head pointers */
    if(!pool)                           Crash(0x7);
    if(!codeSeg)                        Crash(0x8);
    if(isDataSegUsed && (!dataSeg))     Crash(0x9);
    if(isStackSegUsed && (!stackSeg))   Crash(0xA);
    if(isExtSegUsed && (!extSeg))       Crash(0xB);

    /* Check registers */
    if(CS != codeSeg)                   Crash(0xC);
    if(isDataSegUsed
        && (DS != dataSeg))             Crash(0xD);
    if(isExtSegUsed
        && (ES != extSeg))              Crash(0xE);
    if(isStackSegUsed
        && (SS != stackSeg))            Crash(0xF);
    if(isDataSegUsed  && (SI != DS))    Crash(0x10);
    if(isExtSegUsed   && (DI != ES))    Crash(0x11);
    if(isStackSegUsed && (BP != SS))    Crash(0x12);
    if(isStackSegUsed && (SP != SS))    Crash(0x13);
    if(IP != CS)                        Crash(0x14);
    
}