#ifndef __AST_H__
#define __AST_H__

#include <string>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "symbol_table/hashmap.h"
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

        ValueNode(IDNode *i);
        ValueNode(LiteralNode *l);
        ValueNode(FunctionCallNode *f);
        ValueNode(ArrayAccessNode *a);
        ValueNode(DatasetAccessNode *d);
        ValueNode(ExpressionNode *e);
};

class IDNode: public Node {
    Entry *entry;
    public:
        IDNode(Entry *ent);
        ~IDNode();
};

class FunctionCallNode: public Node {
    ArgsNode *args_list;
    IDNode *func_name;

    public:
        FunctionCallNode(IDNode *f, ArgsNode *a);
        FunctionCallNode(IDNode *f);
};

class ArgsNode: public Node {
    std::vector<ExpressionNode*> args_list;

    public:
        ArgsNode();
        ArgsNode(ExpressionNode *arg);
        void add_arg(ExpressionNode *arg);
};

class DeclArgsNode: public Node {
    std::vector<IDNode*> decl_args_list;

    public:
        DeclArgsNode();
        DeclArgsNode(IDNode* arg);
        void add_arg(IDNode* arg);
};

class LiteralNode: public Node {
    public:
        union literal val;
        enum e_type type;

        // Constructors for different types
        LiteralNode(int i);
        LiteralNode(double d);
        LiteralNode(string s);
        LiteralNode(bool b);
        LiteralNode(char b);
};

class ArrayAccessNode: public Node {
    public:
        ValueNode *vn;
        ExpressionNode *en;

        ArrayAccessNode(ValueNode *v, ExpressionNode *e);
};

class DatasetAccessNode: public Node {
    public:
        ValueNode *vn;
        IDNode *idn;

        DatasetAccessNode(ValueNode *valueNode, IDNode *idNode);
};

class UnaryExpressionNode: public Node {
    union operand right_operand;

    public:
        enum e_op op;

        UnaryExpressionNode(UnaryExpressionNode *u, string _op);
        UnaryExpressionNode(ValueNode *v);
};

string gen_binary_code(string l_code, enum e_op op, string r_code);

class BinaryExpressionNode: public Node {
    public:
        union operand left_operand;
        union operand right_operand;
        enum e_op op;
        bool left_is_binary;
        bool right_is_binary;

        BinaryExpressionNode(BinaryExpressionNode *bl, string _op,BinaryExpressionNode *br);
        BinaryExpressionNode(BinaryExpressionNode *bl, string _op, UnaryExpressionNode *ur);
        BinaryExpressionNode(BinaryExpressionNode *bl);
        BinaryExpressionNode(UnaryExpressionNode *ul);
};

class ExpressionNode: public Node {
    public:
        BinaryExpressionNode *bin_exp;
        ValueNode *value;

        ExpressionNode(BinaryExpressionNode *b);
        ExpressionNode(BinaryExpressionNode *b, ValueNode *v);
        ~ExpressionNode();
};

class DeclarativeStatementNode: public Node {
    public:
        e_type type;
        ExpressionNode *en;

        DeclarativeStatementNode(string _type, ExpressionNode *expression_node);
        DeclarativeStatementNode(ExpressionNode *expression_node);
};

class ConditionalStatementNode: public Node {
    public:
        ExpressionNode *condition;
        StatementListNode *consequent;
        StatementListNode *alternative;

        ConditionalStatementNode(ExpressionNode *e, StatementListNode *s, StatementListNode *a);
};

class JumpStatementNode: public Node {
    public:
        e_jump type;
        ExpressionNode *en;

        JumpStatementNode(string _type, ExpressionNode *expression_node);
        JumpStatementNode(string _type);
};

class LoopStatementNode: public Node {
    public:
        ExpressionNode *initializer;
        ExpressionNode *condition;
        ExpressionNode *next;
        StatementListNode *statements;

        LoopStatementNode(ExpressionNode *init, ExpressionNode *cond, ExpressionNode *n, StatementListNode *stmts);
};

class StatementNode: public Node {
    public:
        union statements stmts;

        StatementNode(DeclarativeStatementNode *d);
        StatementNode(ConditionalStatementNode *c);
        StatementNode(JumpStatementNode *j);
        StatementNode(LoopStatementNode *l);
};

class StatementListNode: public Node {
    public:
        std::vector<StatementNode *> stmt_list;

        void push_statement(StatementNode *s);
};

class FunctionNode: public Node {
    public:
        enum e_type type;
        IDNode *id;
        DeclArgsNode *decl_args;
        StatementListNode *stmt_list;

        FunctionNode(string _type, IDNode *id_node, DeclArgsNode *decl_args_list, StatementListNode *stmt_list_n);
};

#endif
