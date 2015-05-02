#ifndef __AST_H__
#define __AST_H__

#include <string>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "symbol_table/hashmap.h"
#include "../structures/enum.h"
#include "../structures/union.h"

#define RPL_STD_OUTPUT_FUNCTION "print"
#define RPL_STD_INPUT_FUNCTION "input"
#define RPL_STD_OPEN_FUNCTION "open"
#define RPL_STD_CLOSE_FUNCTION "close"
#define RPL_STD_READ_FUNCTION "read"

#define INVAL_UNARY_NOT_ERR "\tunary not error"
#define INVAL_UNARY_MINUS_ERR "\tunary minus error"
#define INVAL_BINARY_PLUS_ERR "\tbinary plus error"
#define INVAL_BINARY_MINUS_ERR "\tbinary minus error"
#define INVAL_BINARY_TIMES_ERR "\tbinary times error"
#define INVAL_BINARY_DIV_ERR "\tbinary div error"
#define INVAL_BINARY_EXP_ERR "\tbinary exp error"
#define INVAL_BINARY_FLDIV_ERR "\tbinary fldiv error"
#define INVAL_BINARY_EQ_ERR "\tbinary eq error"
#define INVAL_BINARY_NE_ERR "\tbinary ne error"
#define INVAL_BINARY_GT_ERR "\tbinary gt error"
#define INVAL_BINARY_LT_ERR "\tbinary lt error"
#define INVAL_BINARY_GE_ERR "\tbinary ge error"
#define INVAL_BINARY_LE_ERR "\tbinary le error"
#define INVAL_BINARY_AND_ERR "\tbinary and error"
#define INVAL_BINARY_OR_ERR "\tbinary or error"
#define LOOP_CONDITION_ERR "\tloop condition error"
#define ERROR "error"
#define COMPILE_ERR "compilation halted because of error in code"

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

enum e_op str_to_op(string op_string);
enum e_type str_to_type(string type);
enum e_jump str_to_jump(string type);
string type_to_str(e_type type);

void write_to_file(string filename, string code);

#define IS_STD_RPL_FUNCTION(f_name) (f_name).compare(RPL_STD_INPUT_FUNCTION) == 0    || \
                                    (f_name).compare(RPL_STD_OUTPUT_FUNCTION) == 0   || \
                                    (f_name).compare(RPL_STD_OPEN_FUNCTION) == 0     || \
                                    (f_name).compare(RPL_STD_READ_FUNCTION) == 0     || \
                                    (f_name).compare(RPL_STD_CLOSE_FUNCTION) == 0

#define INVAL_ASSIGN_ERR(val_type, expression_type, line_no) { cout <<        \
                        "\tInvalid assignment between operands of type: " <<  \
                        val_type << " and " << expression_type << " on line " \
                        << line_no << endl; }

extern int line_no;
extern bool error;
extern string filename_cpp;

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
    e_type type = tNONE;
    e_type get_type();
    bool is_number();
    bool is_bool();
    bool is_string();
    bool is_byte();
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
    string generate_std_rpl_function(string function_name, ArgsNode *args);
};


class ArgsNode: public Node {
public:
    std::vector<ExpressionNode*> args_list;

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
    LiteralNode(string *s);
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
public:
    enum e_op op;
    union operand right_operand;

    UnaryExpressionNode(UnaryExpressionNode *u, string _op);
    UnaryExpressionNode(ValueNode *v);

private:
    void typecheck(e_op op);
};


class BinaryExpressionNode: public Node {
public:
    union operand left_operand;
    union operand right_operand;
    enum e_op op;
    bool left_is_binary;
    bool right_is_binary;

    BinaryExpressionNode(BinaryExpressionNode *bl, string _op,BinaryExpressionNode *br);
    BinaryExpressionNode(BinaryExpressionNode *bl, string _op, UnaryExpressionNode *ur);
    BinaryExpressionNode(UnaryExpressionNode *ul);
private:
    void typecheck(Node *left, Node *right, e_op op);
    string gen_binary_code(string l_code, enum e_op op, string r_code);
};


class ExpressionNode: public Node {
public:
    BinaryExpressionNode *bin_exp;
    ValueNode *value;

    ExpressionNode(BinaryExpressionNode *b);
    ExpressionNode(BinaryExpressionNode *b, ValueNode *v);
    ~ExpressionNode();

private:
    void typecheck(BinaryExpressionNode *expression, ValueNode *value);

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
    void seppuku();
};

#endif
