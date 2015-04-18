#ifndef __RPL_ENUM__
#define __RPL_ENUM__ 1

enum e_type {
    tINT,
    tBOOL,
    tFLOAT,
    tSTRING,
    tBYTE,
    tVOID
};

enum e_op {
    PLUS,
    MINUS,
    TIMES,
    DIV,
    FLDIV,
    EXP,
    bAND,
    bOR,
    bNOT,
    EQ,
    NE,
    GT,
    LT,
    GE,
    LE,
    SIZE,
    NONE
};

enum e_jump {
    tRETURN,
    tCONTINUE,
    tBREAK
};

#endif