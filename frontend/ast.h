#ifndef __AST_H__
#define __AST_H__

#include <string>
#include <string.h>
#include <iostream>

using namespace std;

class BinaryExpression;
class UnaryExpression;
class LiteralNode;

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
        LiteralNode *v_node;
};

union value {
    int int_val;
    double float_val;
    std::string string_val;
    bool bool_val;
    char byte_val;

    value() { memset(this, 0, sizeof(value)); }
    ~value() {}
};

struct ID {
    char *name;
}

class IDNode {
public:
    struct ID id;

    IDNode(char *idName) { id.name = idName; }
}



class LiteralNode {
    public:
    union value val;
    enum e_type type;

    // Constructors for different types
    LiteralNode(int i) { val.int_val = i; type = tINT;  }
    LiteralNode(double d) { val.float_val = d; type = tFLOAT; }
    LiteralNode(std::string s) { val.string_val = s; type = tSTRING; }
    LiteralNode(bool b) { val.bool_val = b; type = tBOOL; }
    LiteralNode(char b) { val.byte_val = b; type = tBYTE; }
};

class UnaryExpression {
    union operand right_operand;

    public:
    enum e_op op;
    
    UnaryExpression(UnaryExpression *u, std::string _op)
    {
        op = get_op(_op);
        right_operand.u_exp = u;
    }

    UnaryExpression(LiteralNode *v)
    {
        op = NONE;
        right_operand.v_node = v;
    }
};

class BinaryExpression {
    public:
    union operand left_operand;
    union operand right_operand;
    enum e_op op;
    bool left_is_binary;
    bool right_is_binary;

    BinaryExpression(BinaryExpression *bl, std::string _op,BinaryExpression *br) {
        left_operand.b_exp = bl;
        right_operand.b_exp = br;
        op = get_op(_op);
        left_is_binary = right_is_binary = true;
    }
    
    BinaryExpression(BinaryExpression *bl, std::string _op, UnaryExpression *ur) {
        left_operand.b_exp = bl;
        right_operand.u_exp = ur;
        op = get_op(_op);
        left_is_binary = true;
        right_is_binary = false;
    }

    BinaryExpression(BinaryExpression *bl) {
        
        left_operand = bl->left_operand;
        right_operand = bl->right_operand;
        op = bl->op;
        left_is_binary = bl->left_is_binary;
        right_is_binary = bl->right_is_binary;
    }

    BinaryExpression(UnaryExpression *ul) {
        left_operand.u_exp = ul;
        op = NONE;
    }
};
#endif
