#ifndef __RPL_ENUM__
#define __RPL_ENUM__

enum e_type {
    tNOTYPE,
    tINT,
    tBOOL,
    tFLOAT,
    tSTRING,
    tBYTE,
    tVOID,
    tDERIV,
};

enum e_symbol_type {
    tNOSTYPE,
    tVAR,
    tFUNC,
    tDSET,
    tARR,
    tRES
};

enum e_value_type {
    LIT,
    FUNC_CALL,
    ARR_ACC,
    DS_ACC,
    IDENT,
    EXPR
};

enum e_op {
    PLUS,
    MINUS,
    TIMES,
    DIV,
    FLDIV,
    MOD,
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
