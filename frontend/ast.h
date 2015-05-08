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

#define LINE_ERR "Error on line number " + to_string(line_no) + ": " <<

#define RPL_STD_OUTPUT_FUNCTION "print"
#define RPL_STD_INPUT_FUNCTION "input"
#define RPL_STD_OPEN_FUNCTION "open"
#define RPL_STD_CLOSE_FUNCTION "close"
#define RPL_STD_READ_FUNCTION "read"

#define INVAL_UNARY_NOT_ERR LINE_ERR "unary not error"
#define INVAL_UNARY_MINUS_ERR LINE_ERR "unary minus error"
#define INVAL_BINARY_PLUS_ERR LINE_ERR "binary plus error"
#define INVAL_BINARY_MINUS_ERR LINE_ERR "binary minus error"
#define INVAL_BINARY_TIMES_ERR LINE_ERR "binary times error"
#define INVAL_BINARY_DIV_ERR LINE_ERR "binary div error"
#define INVAL_BINARY_EXP_ERR LINE_ERR "binary exp error"
#define INVAL_BINARY_FLDIV_ERR LINE_ERR "binary fldiv error"
#define INVAL_BINARY_EQ_ERR LINE_ERR "binary eq error"
#define INVAL_BINARY_NE_ERR LINE_ERR "binary ne error"
#define INVAL_BINARY_GT_ERR LINE_ERR "binary gt error"
#define INVAL_BINARY_LT_ERR LINE_ERR "binary lt error"
#define INVAL_BINARY_GE_ERR LINE_ERR "binary ge error"
#define INVAL_BINARY_LE_ERR LINE_ERR "binary le error"
#define INVAL_BINARY_AND_ERR LINE_ERR "binary and error"
#define INVAL_BINARY_OR_ERR LINE_ERR "binary or error"
#define INVAL_FUNC_CALL_ERR LINE_ERR "function call error"
#define LOOP_CONDITION_ERR LINE_ERR "loop condition error"

#define ARR_ELEMENT_TYPE_ERR LINE_ERR "all elements in an array initialization must have the same type"
#define ARR_UNARY_MINUS_ERR LINE_ERR "cannot perform negation on arrays"
#define ARR_UNARY_NOT_ERR LINE_ERR "cannot perform boolean not on arrays"
#define ARR_BINEXP_ERR LINE_ERR "cannot perform binary operations on arrays"
#define ARR_VAR_ASSIGN_ERR LINE_ERR "cannot assign array to non-array variable"
#define ARR_INT_SIZE_ERR LINE_ERR "array size must be int"
#define ARR_UNKNOWN_SIZE_ERR LINE_ERR "variable size array cannot be initialized"
#define ARR_SMALL_SIZE_ERR LINE_ERR "size of array declared is too small"
#define ARR_ASSIGN_ERR LINE_ERR "can't assign array to non-array variable"

#define ASSIGN_ERR "left operand of assignment expression must be a variable"

#define ERROR "error"
#define COMPILE_ERR "compilation halted because of error in code"

using namespace std;
extern int line_no;

class Node;
class ArrayInitNode;
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

#define INVAL_ASSIGN_ERR(val_type, expression_type) { cout << LINE_ERR \
                        "invalid assignment between operands of type " <<  \
                        val_type << " and " << expression_type << endl; }

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
    ArrayInitNode *a_init;
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
    e_type type = tNOTYPE;
    e_symbol_type sym;
    e_type get_type();
    int array_length;
    bool is_number();
    bool is_bool();
    bool is_string();
    bool is_byte();
};

class ArrayInitNode: public Node{
public:
    std::vector<ExpressionNode*> *args_list;

    ArrayInitNode();
    ArrayInitNode(ExpressionNode *arg);
    void add_arg(ExpressionNode *arg);
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
    ValueNode(ArrayInitNode *a);
    void seppuku();
};


class IDNode: public Node {
public:
    Entry *entry;
    IDNode(Entry *ent);
    string get_name();
    e_type get_type();
    ~IDNode();
    void seppuku();
};


class FunctionCallNode: public Node {
ArgsNode *args_list;
IDNode *func_id;

public:
    FunctionCallNode(IDNode *f, ArgsNode *a);
    FunctionCallNode(IDNode *f);
    void typecheck(list<e_type> *l);
    string generate_std_rpl_function();
    void seppuku();
};


class ArgsNode: public Node {
public:
    std::vector<ExpressionNode*> *args_list;

    ArgsNode();
    ArgsNode(ExpressionNode *arg);
    list<e_type> *to_enum_list();
    void add_arg(ExpressionNode *arg);
    void seppuku();
};


class DeclArgsNode: public Node {
std::vector<IDNode*> decl_args_list;

public:
    DeclArgsNode();
    DeclArgsNode(IDNode* arg);
    void add_arg(IDNode* arg);
    list<e_type> *to_enum_list();
    void seppuku();
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
    void seppuku();
};


class ArrayAccessNode: public Node {
public:
    ValueNode *vn;
    ExpressionNode *en;

    ArrayAccessNode(ValueNode *v, ExpressionNode *e);
    void seppuku();
};


class DatasetAccessNode: public Node {
public:
    ValueNode *vn;
    IDNode *idn;

    DatasetAccessNode(ValueNode *valueNode, IDNode *idNode);
    void seppuku();
};


class UnaryExpressionNode: public Node {
public:
    enum e_op op;
    union operand right_operand;

    UnaryExpressionNode(UnaryExpressionNode *u, string _op);
    UnaryExpressionNode(ValueNode *v);
    void seppuku();

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
    void seppuku();

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
    void seppuku();

private:
    void typecheck(BinaryExpressionNode *expression, ValueNode *value);

};


class DeclarativeStatementNode: public Node {
public:
    e_type type;
    ExpressionNode *en;
    ValueNode *a_size;

    DeclarativeStatementNode(string _type, ValueNode *arr_size, ExpressionNode *expression_node);
    DeclarativeStatementNode(ExpressionNode *expression_node);

    void seppuku();
};


class ConditionalStatementNode: public Node {
public:
    ExpressionNode *condition;
    StatementListNode *consequent;
    StatementListNode *alternative;

    ConditionalStatementNode(ExpressionNode *e, StatementListNode *s, StatementListNode *a);
    void seppuku();
};


class JumpStatementNode: public Node {
public:
    e_jump type;
    ExpressionNode *en;

    JumpStatementNode(string _type, ExpressionNode *expression_node);
    JumpStatementNode(string _type);
    void seppuku();
};


class LoopStatementNode: public Node {
public:
    ExpressionNode *initializer;
    ExpressionNode *condition;
    ExpressionNode *next;
    StatementListNode *statements;

    LoopStatementNode(ExpressionNode *init, ExpressionNode *cond, ExpressionNode *n, StatementListNode *stmts);
    void seppuku();
};


class StatementNode: public Node {
public:
    union statements stmts;

    StatementNode(DeclarativeStatementNode *d);
    StatementNode(ConditionalStatementNode *c);
    StatementNode(JumpStatementNode *j);
    StatementNode(LoopStatementNode *l);
    void seppuku();
};


class StatementListNode: public Node {
public:
    std::vector<StatementNode *> stmt_list;

    void push_statement(StatementNode *s);
    void seppuku();
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

class ProgramNode: public Node {
public:
    FunctionNode *func;
    ProgramNode(FunctionNode *f);
    void seppuku();
};
#endif
