#ifndef __AST_H__
#define __AST_H__

#include <string>
#include <string.h>
#include <iostream>
#include <vector>
#include "../structures/enum.h"
#include "../structures/union.h"

using namespace std;

class Node;
class ValueNode;
class ExpressionNode;
class BinaryExpressionNode;
class UnaryExpressionNode;
class LiteralNode;
class IDNode;
class FunctionCallNode;
class ArrayAccessNode;
class DatasetAccessNode;
class ExpressionNode;
class ValueNode;
class ArgsNode;
class DeclArgsNode;
class ConditionalStatementNode;
class DeclarativeStatementNode;
class JumpStatementNode;
class LoopStatementNode;
class StatementListNode;
class FunctionNode;

enum e_op get_op(string op_string);
enum e_type get_type(string type);
enum e_jump get_jump(string type);

union operand {
    BinaryExpressionNode *b_exp;
    UnaryExpressionNode *u_exp;
    ValueNode *v_node;
};

union value {
    IDNode *id_val;
    LiteralNode *lit_val;
    FunctionCallNode *function_call_val;
    ArrayAccessNode *array_access_val;
    DatasetAccessNode *dataset_access_val;
    ExpressionNode *expression_val;
};

union statements {
    DeclarativeStatementNode *decl;
    ConditionalStatementNode *cond;
    JumpStatementNode *jump;
    LoopStatementNode *loop;
};

class Node {
    public:
        string code;
};

class ValueNode: public Node {
    public:
        union value val;

        ValueNode(IDNode *i) { val.id_val = i; }
        ValueNode(LiteralNode *l) { val.lit_val = l; code = l->code;}
        ValueNode(FunctionCallNode *f) { val.function_call_val = f; } 
        ValueNode(ArrayAccessNode *a) { val.array_access_val = a; }
        ValueNode(DatasetAccessNode *d) { val.dataset_access_val = d; }
        ValueNode(ExpressionNode *e) { val.expression_val = e; code = "(" + e->code ")";}
};

class IDNode: public Node {
    string name;
    public:
    IDNode(string idName) { name = idName; }
    ~IDNode() { }
};

class FunctionCallNode: public Node {
    ArgsNode *args_list;
    IDNode *func_name;

    public:
    FunctionCallNode(IDNode *f, ArgsNode *a){ 
        func_name = f;
        args_list = a;
        code = f->code + "(" + a->code + ")";
    };
    FunctionCallNode(IDNode *f) { func_name = f; code = f->code + "()"; };

};

class ArgsNode: public Node {
    std::vector<ExpressionNode*> args_list;

    public:
    ArgsNode() { code = ""; };
    ArgsNode(ExpressionNode *arg) {args_list.push_back(arg); code = arg->code; };
    void add_arg(ExpressionNode *arg) { args_list.push_back(arg); code += ", " + arg->code; }
};

class DeclArgsNode: public Node {
    std::vector<IDNode*> decl_args_list;

    public:
    DeclArgsNode() { code = ""; };
    DeclArgsNode(IDNode* arg) { decl_args_list.push_back(arg); code = arg->code; };
    void add_arg(IDNode* arg) { decl_args_list.push_back(arg); code += arg->code; };
};

class LiteralNode: public Node {
    public:
        union literal val;
        enum e_type type;

        // Constructors for different types
        LiteralNode(int i) { val.int_lit = i; type = tINT;  }
        LiteralNode(double d) { val.float_lit = d; type = tFLOAT; }
        LiteralNode(string s) { val.string_lit = s; type = tSTRING; }
        LiteralNode(bool b) { val.bool_lit = b; type = tBOOL; }
        LiteralNode(char b) { val.byte_lit = b; type = tBYTE; }
};

class ArrayAccessNode: public Node {
    public:
        ValueNode *vn;
        ExpressionNode *en;

        ArrayAccessNode(ValueNode *valueNode, ExpressionNode *expressionNode) {
            vn = valueNode;
            en = expressionNode;
        }
};

class DatasetAccessNode: public Node {
    public:
        ValueNode *vn;
        IDNode *idn;

        DatasetAccessNode(ValueNode *valueNode, IDNode *idNode) {
            vn = valueNode;
            idn = idNode;
        }
};

class UnaryExpressionNode: public Node {

    union operand right_operand;

    public:
    enum e_op op;

    UnaryExpressionNode(UnaryExpressionNode *u, string _op)
    {
        op = get_op(_op);
        switch(op) {
            case MINUS:
                code = "-" + u->code;
                break;
            case SIZE:
                code = "sizeof(" + u->code + ")";
                break;
            case bNOT:
                code = "!" + u->code;
                break;
            default:
                break;
        }
        right_operand.u_exp = u;
    }

    UnaryExpressionNode(ValueNode *v)
    {
        op = NONE;
        right_operand.v_node = v;
        code = v->code;
    }
};

string gen_binary_code(string l_code, enum e_op op, string r_code);

class BinaryExpressionNode: public Node {
    public:
        union operand left_operand;
        union operand right_operand;
        enum e_op op;
        bool left_is_binary;
        bool right_is_binary;

        BinaryExpressionNode(BinaryExpressionNode *bl, string _op,BinaryExpressionNode *br) {
            left_operand.b_exp = bl;
            right_operand.b_exp = br;
            op = get_op(_op);
            code = gen_binary_code(bl->code, op, br->code); 
            left_is_binary = right_is_binary = true;
        }

        BinaryExpressionNode(BinaryExpressionNode *bl, string _op, UnaryExpressionNode *ur) {
            left_operand.b_exp = bl;
            right_operand.u_exp = ur;
            op = get_op(_op);
            code = gen_binary_code(bl->code, op, ur->code); 
            left_is_binary = true;
            right_is_binary = false;
        }

        BinaryExpressionNode(BinaryExpressionNode *bl) {

            left_operand = bl->left_operand;
            right_operand = bl->right_operand;
            op = bl->op;
            code = bl->code; 
            left_is_binary = bl->left_is_binary;
            right_is_binary = bl->right_is_binary;

            delete bl;
        }

        BinaryExpressionNode(UnaryExpressionNode *ul) {
            left_operand.u_exp = ul;
            code = ul->code;
            op = NONE;
        }
};

class ExpressionNode: public Node {
    public:
        BinaryExpressionNode *bin_exp;
        ValueNode *value;

        ExpressionNode(BinaryExpressionNode *b) {
            bin_exp = b;
            code = b->code;
            value = NULL;
        }

        ExpressionNode(BinaryExpressionNode *b, ValueNode *v) {
            bin_exp = b;
            code = v->code + "=" + b->code;
            value = v;
        }

        ~ExpressionNode() {
            delete bin_exp;
        }
};

class DeclarativeStatementNode: public Node {
    public:
        e_type type;
        ExpressionNode *en;

        DeclarativeStatementNode(string _type, ExpressionNode *expression_node){
            type = get_type(_type);
            en = expression_node;

            //TODO TYPE CONVERSIONS
            code = _type + " " + expression_node->code + ";"; 
        }

        DeclarativeStatementNode(ExpressionNode *expression_node){
            en = expression_node;
            code = expression_node->code + ";";
        }

};

class ConditionalStatementNode: public Node {
    public:
        ExpressionNode *condition;
        StatementListNode *consequent;
        StatementListNode *alternative;

        ConditionalStatementNode(ExpressionNode *e, StatementListNode *s, StatementListNode *a) {
            condition = e;
            consequent = s;
            alternative = a;
        }
};

class JumpStatementNode: public Node {
    public:
        e_jump type;
        ExpressionNode *en;

        JumpStatementNode(string _type, ExpressionNode *expression_node){
            type = get_jump(_type);
            en = expression_node;
        }

        JumpStatementNode(string _type){
            type = get_jump(_type);
        }
};

class LoopStatementNode: public Node {
    public:
        ExpressionNode *initializer;
        ExpressionNode *condition;
        ExpressionNode *next;
        StatementListNode *statements;

        LoopStatementNode(ExpressionNode *init, ExpressionNode *cond, ExpressionNode *n, StatementListNode *stmts){
            initializer = init;
            condition = cond;
            next = n;
            statements = stmts;
        }

};

class StatementNode: public Node {
    public:
        union statements stmts;

        StatementNode(DeclarativeStatementNode *d){
            stmts.decl = d;
            code = d->code;
        }

        StatementNode(ConditionalStatementNode *c) {
            stmts.cond = c;
            code = c->code;
        }

        StatementNode(JumpStatementNode *j) {
            stmts.jump = j;
            code = j->code;
        }

        StatementNode(LoopStatementNode *l) {
            stmts.loop = l;
            code = l->code;
        }
};

class StatementListNode: public Node {
    public:
        std::vector<StatementNode *> stmt_list;

        void push_statement(StatementNode *s){
            stmt_list.push_back(s);
            code = code + s->code;
        }

};

class FunctionNode: public Node {
    public:
        enum e_type type;
        IDNode *id;
        DeclArgsNode *decl_args;
        StatementListNode *stmt_list;

        FunctionNode(string _type, IDNode *id_node, DeclArgsNode *decl_args_list, StatementListNode *stmt_list_n){
            type = get_type(_type);
            id = id_node;
            decl_args = decl_args_list;
            stmt_list = stmt_list_n;
            //TODO typing and symbol_table interactions
            
            code = _type + " " + id_node->code + "(" + decl_args_list->code + ")" + stmt_list_n->code; 
        }
};

#endif
