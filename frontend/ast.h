#ifndef __AST_H__
#define __AST_H__

#include <string>
#include <string.h>

class Expression;
class BinaryExpression;
class UnaryExpression;
class ValueNode;

enum e_type {
    tINT,
    tBOOL,
    tFLOAT,
    tSTRING,
    tBYTE,
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

enum e_op get_op(std::string op_string);

union operand {
        BinaryExpression *b_exp;
        UnaryExpression *u_exp;
        ValueNode *v_node;
};

union value {
    int int_val;
    double float_val;
    std::string string_val;
    bool bool_val;
    char byte_val;

    value() {memset(this, 0, sizeof(value));}
    ~value() {}
};

class ASTNode {
    public:
        virtual ~ASTNode();
};

class Expression : ASTNode {
    public:
        int op;
};

class ValueNode {
    union value val;

    public:
    enum e_type type;

    // Constructors for different types
    ValueNode(int i) { val.int_val = i; type = tINT; }
    ValueNode(double d) { val.float_val = d; type = tFLOAT; }
    ValueNode(std::string s) { val.string_val = s; type = tSTRING; }
    ValueNode(bool b) { val.bool_val = b; type = tBOOL; }
    ValueNode(char b) { val.byte_val = b; type = tBYTE; }
};

class UnaryExpression : ValueNode {
    union operand left_operand;
    bool repeats;

    public:
    enum e_op op;
    
    UnaryExpression(UnaryExpression *u, std::string _op):
    ValueNode(10)
    {
        
        op = get_op(_op);
        left_operand.u_exp = u;
        repeats = true;
    }

    UnaryExpression(ValueNode *v):
    ValueNode(10)
    {
        op = NONE;
        left_operand.v_node = v;
        repeats = false;
    }
};
#endif
