#ifndef ERR_LIST
#define ERR_LIST

const char *Messeges[] = {
    "SUCCESS #0x0: td-cma works fine.",

    "ERROR #0x1: Usage: td-cma <source-file-name> [--Strict/-s]",
    "ERROR #0x2: File open failed.",
    "ERROR #0x3: File too large.",
    "ERROR #0x4: Allocate buffer memory space failed.",
    "ERROR #0x5: File read in error.",
    "ERROR #0x6: Allocate VM memory space failed.",

    "ERROR #0x7: Pool pointer not initialized.",
    "ERROR #0x8: Code segment head pointer not initialized.",
    "ERROR #0x9: Data segment head pointer not initialized.",
    "ERROR #0xA: Stack segment head pointer not initialized.",
    "ERROR #0xB: Extend segment head pointer not initialized.",

    "ERROR #0xC: Register CS not initialized correctly.",
    "ERROR #0xD: Register DS not initialized correctly.",
    "ERROR #0xE: Register ES not initialized correctly.",
    "ERROR #0xF: Register SS not initialized correctly.",
    "ERROR #0x10: Register SI not initialized correctly.",
    "ERROR #0x11: Register DI not initialized correctly.",
    "ERROR #0x12: Register BP not initialized correctly.",
    "ERROR #0x13: Register SP not initialized correctly.",
    "ERROR #0x14: Program Counter not initialized correctly."
};

#endif