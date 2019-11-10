#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errlist.h"
#include "td-cma.h"

inline void Crash(int msgNumber) {
    fputs(Messeges[msgNumber], stderr);
    exit(msgNumber);
}