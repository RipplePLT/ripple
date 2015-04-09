#ifndef __AST_H__
#define __AST_H__

#include <string>
#include <string.h>
#include <iostream>
#include <vector>

using namespace std;

class BinaryExpressionNode;
class UnaryExpressionNode;
class LiteralNode;
class FunctionCallNode;
class ArgsNode;

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
    BinaryExpressionNode *b_exp;
    UnaryExpressionNode *u_exp;
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
};

class IDNode {
    public:
        struct ID id;

        IDNode(char *idName) { id.name = idName; }
};

class FunctionCallNode{
    ArgsNode *args_list;
    IDNode *func_name;

    public:
        FunctionCallNode(IDNode *func_name, ArgsNode *args_list){ this->func_name = func_name ; this->args_list = args_list; };
        FunctionCallNode(IDNode *func_name) { this->func_name = func_name; };

};

class ArgsNode{
    std::vector<ExpressionNode> args_list;

    public:
        ArgsNode(std::vector<ExpressionNode> args_list) { this->args_list = args_list; };
	void add_arg(ExpressionNode arg) { args_list.push_back(arg); }
};


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

class UnaryExpressionNode {
    union operand right_operand;

    public:
    enum e_op op;

    UnaryExpressionNode(UnaryExpressionNode *u, std::string _op)
    {
        op = get_op(_op);
        right_operand.u_exp = u;
    }

    UnaryExpressionNode(LiteralNode *v)
    {
        op = NONE;
        right_operand.v_node = v;
    }
};

class BinaryExpressionNode {
    public:
        union operand left_operand;
        union operand right_operand;
        enum e_op op;
        bool left_is_binary;
        bool right_is_binary;

        BinaryExpressionNode(BinaryExpressionNode *bl, std::string _op,BinaryExpressionNode *br) {
            left_operand.b_exp = bl;
            right_operand.b_exp = br;
            op = get_op(_op);
            left_is_binary = right_is_binary = true;
        }

        BinaryExpressionNode(BinaryExpressionNode *bl, std::string _op, UnaryExpressionNode *ur) {
            left_operand.b_exp = bl;
            right_operand.u_exp = ur;
            op = get_op(_op);
            left_is_binary = true;
            right_is_binary = false;
        }

        BinaryExpressionNode(BinaryExpressionNode *bl) {

            left_operand = bl->left_operand;
            right_operand = bl->right_operand;
            op = bl->op;
            left_is_binary = bl->left_is_binary;
            right_is_binary = bl->right_is_binary;
        }

        BinaryExpressionNode(UnaryExpressionNode *ul) {
            left_operand.u_exp = ul;
            op = NONE;
        }
};
#endif
