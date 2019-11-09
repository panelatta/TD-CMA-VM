#ifndef ERR_LIST
#define ERR_LIST

const char *ERR_MSG[] = {
    "SUCCESS #0: td-cma works fine.",

    "ERROR #1: Usage: td-cma <source-file-name> [--Strict/-s]",
    "ERROR #2: File open failed.",
    "ERROR #3: File too large.",
    "ERROR #4: Allocate buffer memory space failed.",
    "ERROR #5: File read in error.",
    "ERROR #6: Allocate code segment memory space failed.",
    "ERROR #7: Allocate data segment memory space failed.",
    "ERROR #8: Allocate stack segment memory space failed."
};

#endif