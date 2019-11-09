#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errlist.h"
#include "td-cma.h"

inline void Crash(int errorNumber) {
    fputs(ERR_MSG[errorNumber], stderr);
    exit(errorNumber);
}