#ifndef __AST_H__
#define __AST_H__

#include <string>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "symbol_table/hashmap.h"
#include "symbol_table/symbol_table.h"
#include "../structures/enum.h"
#include "../structures/union.h"

#define LINE_ERR "Error on line number " + to_string(line_no) + ": " <<

#define RPL_STD_OUTPUT_FUNCTION "print"
#define RPL_STD_INPUT_FUNCTION "input"
#define RPL_STD_OPEN_FUNCTION "open"
#define RPL_STD_CLOSE_FUNCTION "close"
#define RPL_STD_READ_FUNCTION "read"

#define VARIABE_NODE_NAME "VARIABLE_NODE_NAME"
#define VALUE_NODE_NAME "VALUE_NODE_NAME"
#define UNARY_EXPRESSION_NODE_NAME "UNARY_EXPRESSION_NAME"
#define BINARY_EXPRESSION_NODE_NAME "BINARY_EXPRESSION_NAME"
#define EXPRESSION_NODE_NAME "EXPRESSION_NODE_NAME"

#define INVAL_UNARY_NOT_ERR LINE_ERR "unary not error"
#define INVAL_UNARY_MINUS_ERR LINE_ERR "unary minus error"
#define INVAL_BINARY_PLUS_ERR LINE_ERR "binary plus error"
#define INVAL_BINARY_MINUS_ERR LINE_ERR "binary minus error"
#define INVAL_BINARY_TIMES_ERR LINE_ERR "binary times error"
#define INVAL_BINARY_DIV_ERR LINE_ERR "binary div error"
#define INVAL_BINARY_EXP_ERR LINE_ERR "binary exp error"
#define INVAL_BINARY_FLDIV_ERR LINE_ERR "binary fldiv error"
#define INVAL_BINARY_MOD_ERR LINE_ERR "binary mod error"
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
#define UNKNOWN_TYPE_ERR LINE_ERR "unknown type error"
#define FUNCTION_BASIC_TYPE_ERR LINE_ERR "functions can only return primitive types"

#define INVALID_DECL_ERR LINE_ERR "invalid declaration"
#define VARIABLE_REDECL_ERR LINE_ERR "variable redeclaration"
#define UNDECLARED_ERROR LINE_ERR "undeclared identifier"

#define ARR_ELEMENT_TYPE_ERR LINE_ERR "all elements in an array initialization must have the same type"
#define ARR_UNARY_MINUS_ERR LINE_ERR "cannot perform negation on arrays"
#define ARR_UNARY_NOT_ERR LINE_ERR "cannot perform boolean not on arrays"
#define ARR_BINEXP_ERR LINE_ERR "cannot perform binary operations on arrays"
#define ARR_VAR_ASSIGN_ERR LINE_ERR "cannot assign array to non-array variable"
#define ARR_INT_SIZE_ERR LINE_ERR "array size must be int"
#define ARR_UNKNOWN_SIZE_ERR LINE_ERR "variable size array cannot be initialized"
#define ARR_UNKNOWN_INIT_ERR LINE_ERR "cannot create an array of unknown size without initialization"
#define ARR_SMALL_SIZE_ERR LINE_ERR "size of array declared is too small"
#define ARR_ASSIGN_ERR LINE_ERR "can't assign array to non-array variable"

#define UNLINKABLE_NO_VAR_ERR LINE_ERR "linked expression must have variables"
#define UNLINKABLE_EXPRESSION_ERR LINE_ERR "expression provided cannot be linked"
#define NOT_A_FUNC_ERR LINE_ERR "attempt to call a non function identifier"
#define COND_STMT_ERR LINE_ERR "expression in if statement must be boolean"
#define LOOP_CONDITION_ERR LINE_ERR "condition expression in loop must be of type boolean"

#define ASSIGN_ERR "left operand of assignment expression must be a variable"
#define ASSIGN_ERR LINE_ERR "left operand of assignment expression must be a variable"

#define ERROR "error"
#define COMPILE_ERR "Unable to complete compilation due to errors in code. Get good"

inline string VARIABLE_NODE(string arg){ return "new VariableNode( &" + arg + " )"; }
inline string LITERAL_NODE(string arg){ return "new LiteralNode( " + arg + " )"; }
inline string VALUE_NODE(string arg){ return  "new ValueNode( " + arg + " )"; }
inline string UNARY_EXPRESSION(string arg){ return  "new UnaryExpressionNode( " + arg + " )"; }
inline string UNARY_EXPRESSION(string arg, string op){ return  "new UnaryExpressionNode( " + arg + ", \"" + op + "\" )"; }
inline string BINARY_EXPRESSION(string arg1){ return  "new BinaryExpressionNode( " + arg1 + " )"; }
inline string BINARY_EXPRESSION(string arg1, string op, string arg2){ return  "new BinaryExpressionNode( " + arg1 + ", \"" + op + "\", " + arg2 + " )"; }
inline string EXPRESSION_NODE(string arg){ return  "new ExpressionNode( " + arg + " )"; }

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
class LinkStatementNode;
class StatementListNode;
class DatasetNode;
class FunctionNode;

enum e_op str_to_op(string op_string);
enum e_type str_to_type(string type);
enum e_jump str_to_jump(string type);
string type_to_str(e_type type);

void write_to_file(string filename, string code);

extern SymbolTable sym_table;

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
    LinkStatementNode *link;
};

union program_section {
    FunctionNode *function;
    DatasetNode *dataset;
};

class Node {
    public:
        string code;
        string ds_name = ""; 
        int array_length;
        string link_code;
        std::vector<string *> linked_vars;
        bool is_linkable = false;
        e_type type = tNOTYPE;
        e_type get_type();
        e_symbol_type sym = tNOSTYPE;
        bool is_number();
        bool is_bool();
        bool is_string();
        bool is_byte();
};


class ValueNode: public Node {
    public:
        union value val;
        enum e_value_type val_type;

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
        void seppuku();
};


class FunctionCallNode: public Node {
    ArgsNode *args_list;
    string func_id;

    public:
    FunctionCallNode(string f, ArgsNode *a);
    FunctionCallNode(string f);
    void typecheck();
    string generate_std_rpl_function();
    void seppuku();
};

class ArrayInitNode: public Node{
    public:
        int array_length;
        std::vector<ExpressionNode *> *args_list;
        bool has_elements;
        ArrayInitNode();
        ArrayInitNode(ExpressionNode *arg);
        void add_arg(ExpressionNode *arg);
        void seppuku();
};

class ArgsNode: public Node {
    public:
        std::vector<ExpressionNode *> *args_list;

        ArgsNode();
        ArgsNode(ExpressionNode *arg);
        list<e_type> *to_enum_list();
        void add_arg(ExpressionNode *arg);
        void seppuku();
};

class TypeNode: public Node {
    public:
        ValueNode *value;
        TypeNode(e_type t);
        TypeNode(e_type t, ValueNode *val);
};

class DeclArgsNode: public Node {
    std::vector<IDNode *> decl_args_list;

    public:
    DeclArgsNode();
    DeclArgsNode(TypeNode *type, IDNode* arg);
    void add_arg(TypeNode *type,IDNode* arg);
    list<e_type> *to_enum_list();
    vector<IDNode*>::iterator begin();
    vector<IDNode*>::iterator end();
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
        ValueNode *value_node;
        ExpressionNode *en;

        ArrayAccessNode(ValueNode *v, ExpressionNode *e);
        void seppuku();
};


class DatasetAccessNode: public Node {
    public:
        ValueNode *value_node;
        string id;

        DatasetAccessNode(string c, string i);
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

        ValueNode *get_value_node();

        BinaryExpressionNode(BinaryExpressionNode *bl, string _op,BinaryExpressionNode *br);
        BinaryExpressionNode(BinaryExpressionNode *bl, string _op, UnaryExpressionNode *ur);
        BinaryExpressionNode(UnaryExpressionNode *ul);
        void seppuku();

    private:
        void typecheck(Node *left, Node *right, e_op op);
        string gen_binary_code(string l_code, enum e_op op, string r_code, e_type l_type, e_type r_type);
};


class ExpressionNode: public Node {
    public:
        BinaryExpressionNode *bin_exp;
        ValueNode *value;
        std::vector<string *> linked_vars;

        ExpressionNode();
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

        DeclarativeStatementNode(TypeNode *t, ExpressionNode *expression_node);
        DeclarativeStatementNode(ExpressionNode *expression_node);
        void typecheck();
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

class LinkStatementNode: public Node {
    public:
        IDNode *id_node;
        ExpressionNode *expression_node;

        LinkStatementNode(IDNode *idn, ExpressionNode *expn);
        void sepukku();
};

class StatementNode: public Node {
    public:
        union statements stmts;

        StatementNode(DeclarativeStatementNode *d);
        StatementNode(ConditionalStatementNode *c);
        StatementNode(JumpStatementNode *j);
        StatementNode(LoopStatementNode *l);
        StatementNode(LinkStatementNode *l);
        void seppuku();
};


class StatementListNode: public Node {
    public:
        vector<StatementNode *> *stmt_list;
        SymbolTableNode *st_node;

        StatementListNode();
        StatementListNode(SymbolTableNode *s);
        void push_statement(StatementNode *s);
        void seppuku();
};

class DatasetNode: public Node {
    public:
        string name;
        DeclArgsNode *decl_args;

        DatasetNode(string s, DeclArgsNode *d);
        void seppuku();
};

class FunctionNode: public Node {
    public:
        enum e_type type;
        string id;
        DeclArgsNode *decl_args;
        StatementListNode *stmt_list;

        FunctionNode(TypeNode *_type, string id_node, DeclArgsNode *decl_args_list, StatementListNode *stmt_list_n);
        void seppuku();
};

class ProgramSectionNode: public Node {
    union program_section contents;

    public:
    ProgramSectionNode(FunctionNode *f);
    ProgramSectionNode(DatasetNode *d);
    void seppuku();
};

class ProgramNode: public Node {
    public:
        ProgramNode();
        void add_section(ProgramSectionNode *);
        FunctionNode *func;
        ProgramNode(FunctionNode *f);
        void seppuku();
};
#endif
