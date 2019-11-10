#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "td-cma.h"

typedef char Byte;
#define BUFFER_SIZE     (2930 * 1024)
#define SEGMENT_SIZE    (256  * 1024)

/* memory pool and segment head pointers */
uint8_t *pool;             // memory pool
uint8_t *codeSeg;          // code segment
uint8_t *stackSeg;         // stack segment
uint8_t *dataSeg;          // data segment
uint8_t *extSeg;           // extend segment

/* main registers */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
struct MainRegister {
    union {
        uint16_t X;
        uint8_t L;
        struct {
            uint8_t : 8;
            uint8_t H;
        };
    };
};
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
struct MainRegister {
    union {
        uint16_t X;
        uint8_t H;
        struct {
            uint8_t : 8;
            uint8_t L;
        };
    };
};
#endif
struct MainRegister A, B, C, D;

/* index registers */
uint8_t *SI, *DI;
uint8_t *BP, *SP;

/* program counter */
uint8_t *IP;

/* segment registers */
uint8_t *CS, *DS, *ES, *SS;

/* status register */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
struct PSWFLAGS {
    union {
        uint16_t __flags;
        struct {
            uint8_t CF: 1;
            uint8_t   : 1;
            uint8_t PF: 1;
            uint8_t   : 1;
            uint8_t AF: 1;
            uint8_t   : 1;
            uint8_t ZF: 1;
            uint8_t SF: 1;
            uint8_t TF: 1;
            uint8_t IF: 1;
            uint8_t DF: 1;
            uint8_t OF: 1;
            uint8_t   : 4;
        };
    };
} FLAGS;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
struct PSWFLAGS {
    union {
        uint16_t __flags;
        struct {
            uint8_t   : 4;
            uint8_t OF: 1;
            uint8_t DF: 1;
            uint8_t IF: 1;
            uint8_t TF: 1;
            uint8_t SF: 1;
            uint8_t ZF: 1;
            uint8_t   : 1;
            uint8_t AF: 1;
            uint8_t   : 1;
            uint8_t PF: 1;
            uint8_t   : 1;
            uint8_t CF: 1;
        };
    };
} FLAGS;
#endif

/* Instructions */
enum INSTRUCTION {
    /* Basic instructions (1 ~ 15) */
    ADD = 1, SUB, INC, AND, OR, RR, MOV, IN, OUT, HLT, 
    LDI, LAD, STA, JMP, BZC,

    /* Extended instructions (16 ~ 48) */
    XCHG, CMP, TEST, CLR, SAL, SHL, SAR, SHR, ROL, ROR,
     RCL, RCR, RRD, ADDI, DEC, XOR, NOT, NOR, ORI, XORI,
    ANDI, ADC, SUBC,  JG,  JL,  JE,  JZ, JNZ, PUSH, POP,
    DIVU, MODU, MULU 
};


int main(int argc, char **argv) {
    if(argc < 2)
        Crash(0x1);   // No command line parameter offered. Program crash.

    /* Open source file in binary mode against read-in error */
    FILE* fp = fopen(argv[1], "rb");
    if(!fp) 
        Crash(0x2);   // Open source file failed.

    /* Get length of source file */
    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    rewind(fp);
    if(fileSize >= BUFFER_SIZE)
        Crash(0x3);   // Source file is bigger than buffer designed.

    /* Allocate memory for source code buffer */
    char *buffer = (char *)malloc(sizeof(char) * fileSize);
    if(!buffer)
        Crash(0x4);   // Allocate memory for buffer failed.
    size_t fileReadLength = fread(buffer, sizeof(char), fileSize, fp);
    if(fileReadLength != fileSize)
        Crash(0x5);   // Read-in error
    buffer[fileReadLength] = '\0';
    fclose(fp);

    /* Allocate memory for segments */
    if(!(pool = (uint8_t *)calloc(3 * SEGMENT_SIZE, sizeof(Byte))))
        Crash(0x6);

    /* Initialize segment head pointers and registers */
    codeSeg = dataSeg = stackSeg = (uint8_t *)NULL;
    A.X = B.X = C.X = D.X = 0;
    CS = DS = ES = SS = (uint8_t *)NULL;
    BP = SP = SI = DI = (uint8_t *)NULL;
    IP = CS;
    FLAGS.__flags = 0;  // initialize all flags

    Prework(buffer, fileSize);
    // Executor(buffer, fileSize);

    free(buffer);
    return 0;
}