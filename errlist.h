#ifndef ERR_LIST
#define ERR_LIST

const char *ERR_MSG[] = {
    "SUCCESS #0: td-cma works fine.",

    "ERROR #1: Usage: td-cma <source-file-name> [--PreWork]",
    "ERROR #2: File open failed.",
    "ERROR #3: File too large. Max size: 3000000 Bytes.",
    "ERROR #4: Request buffer memory space failed.",
    "ERROR #5: File read in error."
};

#endif