#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "td-cma.h"

typedef char Byte;
#define BUFFER_SIZE     (2930 * 1024)
#define SEGMENT_SIZE    (256  * 1024)

/* segment head pointers */
uint16_t *codeSeg;          // code segment
uint16_t *stackSeg;         // stack segment
char     *dataSeg;          // data segment

/* main registers */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
struct MainRegister {
    union {
        uint16_t x;
        uint8_t l;
        struct {
            uint8_t : 8;
            uint8_t h;
        };
    };
};
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
struct MainRegister {
    union {
        uint16_t x;
        uint8_t h;
        struct {
            uint8_t : 8;
            uint8_t l;
        };
    };
};
#endif
struct MainRegister A, B, C, D;

/* index registers */
uint16_t SI, DI;
uint16_t *BP, *SP;

/* program counter */
uint16_t IP;

/* segment registers */
uint16_t *CS, *DS, *ES, *SS;

/* status register */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
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
} FLAGS;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
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
} FLAGS;
#endif

int main(int argc, char **argv) {
    if(argc < 2)
        Crash(1);   // No command line parameter offered. Program crash.

    /* Open source file in binary mode against read-in error */
    FILE* fp = fopen(argv[1], "rb");
    if(!fp) 
        Crash(2);   // Open source file failed.

    /* Get length of source file */
    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    rewind(fp);
    if(fileSize >= BUFFER_SIZE)
        Crash(3);   // Source file is bigger than buffer designed.

    /* Allocate memory for source code buffer */
    char *buffer = (char *)malloc(sizeof(char) * fileSize);
    if(!buffer)
        Crash(4);   // Allocate memory for buffer failed.
    size_t fileReadLength = fread(buffer, sizeof(char), fileSize, fp);
    if(fileReadLength != fileSize)
        Crash(5);   // Read-in error
    buffer[fileReadLength] = '\0';
    fclose(fp);

    /* Allocate memory for segments */
    if(!(codeSeg = (uint16_t *)calloc(SEGMENT_SIZE, sizeof(Byte))))
        Crash(6);   // Allocate memory for code segment failed.
    if(!(dataSeg = (char *)calloc(SEGMENT_SIZE, sizeof(Byte))))
        Crash(7);   // Allocate memory for data segment failed.
    if(!(stackSeg = (uint16_t *)calloc(SEGMENT_SIZE, sizeof(Byte))))
        Crash(8);   // Allocate memory for stack segment failed.

    Prework(buffer, fileSize);
    Executor(buffer, fileSize);

    free(buffer);
    return 0;
}