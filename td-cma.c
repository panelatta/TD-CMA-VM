#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "td-cma.h"

#define BUFFER_SIZE 3000000

int main(int argc, char **argv) {
    if(argc < 2)
        Crash(1);

    FILE* fp = fopen(argv[1], "rb");
    if(!fp) 
        Crash(2);

    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    rewind(fp);
    if(fileSize >= BUFFER_SIZE)
        Crash(3);

    char *buffer = (char *)malloc(sizeof(char) * fileSize);
    if(!buffer)
        Crash(4);
    size_t fileReadLength = fread(buffer, sizeof(char), fileSize, fp);
    if(fileReadLength != fileSize)
        Crash(5);
    buffer[fileReadLength] = '\0';
    
    fclose(fp);

    Prework(buffer, fileSize);

    free(buffer);

    return 0;
}