#ifndef TD_CMA
#define TD_CMA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Crash(int msgNumber);
void Note(int msgNumber);

int Prework(char *buffer, size_t fileSize);
void Executor(int isDataSegUsed, int isStackSegUsed, int isExtSegUsed);

#endif