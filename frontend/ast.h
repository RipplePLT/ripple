#ifndef __AST_H__
#define __AST_H__

#include <string>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

#ifndef INCLUDED_PARSE_ERRORS
#include "parse_errors.h"
#endif

#ifndef INCLUDED_AST_NODE
#include "ast_nodes/ast_node.h"
#endif

#ifndef INCLUDED_LITERAL_NODE
#include "ast_nodes/literal_node.h"
#endif

#ifndef INCLUDED_VALUE_NODE
#include "ast_nodes/value_node.h"
#endif

#include "symbol_table/hashmap.h"
#include "symbol_table/symbol_table.h"
#include "../structures/enum.h"
#include "../structures/union.h"
#include "../misc/debug_tools.h"

#define RPL_STD_OUTPUT_FUNCTION "print"
#define RPL_STD_INPUT_FUNCTION "input"
#define RPL_STD_OPEN_FUNCTION "open"
#define RPL_STD_CLOSE_FUNCTION "close"
#define RPL_STD_READ_FUNCTION "read"

#define RPL_STD_INPUT_FUNCTION_ERR LINE_ERR "input() takes a single string input"

#define VARIABE_NODE_NAME "VARIABLE_NODE_NAME"
#define VALUE_NODE_NAME "VALUE_NODE_NAME"
#define UNARY_EXPRESSION_NODE_NAME "UNARY_EXPRESSION_NAME"
#define BINARY_EXPRESSION_NODE_NAME "BINARY_EXPRESSION_NAME"
#define EXPRESSION_NODE_NAME "EXPRESSION_NODE_NAME"

inline string VARIABLE_NODE(string arg){ return "new VariableNode( &" + arg + " )"; }
inline string LITERAL_NODE(string arg){ return "new LiteralNode( " + arg + " )"; }
inline string VALUE_NODE(string arg){ return  "new ValueNode( " + arg + " )"; }
inline string UNARY_EXPRESSION(string arg){ return  "new UnaryExpressionNode( " + arg + " )"; }
inline string UNARY_EXPRESSION(string arg, string op)
            { return  "new UnaryExpressionNode( " + arg + ", \"" + op + "\" )"; }
inline string BINARY_EXPRESSION(string arg1){ return  "new BinaryExpressionNode( " + arg1 + " )"; }
inline string BINARY_EXPRESSION(string arg1, string op, string arg2)
            { return  "new BinaryExpressionNode( " + arg1 + ", \"" + op + "\", " + arg2 + " )"; }
inline string EXPRESSION_NODE(string arg){ return  "new ExpressionNode( " + arg + " )"; }

using namespace std;

/* Abstract Syntax Tree node classes */
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
class StreamReaderNode;
class ConditionalStatementNode;
class DeclarativeStatementNode;
class JumpStatementNode;
class LoopStatementNode;
class LinkStatementNode;
class StatementListNode;
class DatasetNode;
class FunctionNode;

/* Helper functions that translate between enums and strings */
enum e_op str_to_op(string op_string);
enum e_type str_to_type(string type);
enum e_jump str_to_jump(string type);
string type_to_str(e_type type);

void write_to_file(string filename, string code);

extern SymbolTable sym_table;
extern e_type func_type;

#define IS_STD_RPL_FUNCTION(f_name) (f_name).compare(RPL_STD_INPUT_FUNCTION) == 0   || \
                                    (f_name).compare(RPL_STD_OUTPUT_FUNCTION) == 0  || \
                                    (f_name).compare(RPL_STD_OPEN_FUNCTION) == 0    || \
                                    (f_name).compare(RPL_STD_READ_FUNCTION) == 0    || \
                                    (f_name).compare(RPL_STD_CLOSE_FUNCTION) == 0   || \
                                    (f_name).compare("contains_word") == 0          || \
                                    (f_name).compare("length") == 0                 || \
                                    (f_name).compare("print_line") == 0             || \
                                    (f_name).compare("locate_word") == 0            || \
                                    (f_name).compare("contains_tag") == 0           || \
                                    (f_name).compare("contains_word") == 0          || \
                                    (f_name).compare("get_num_tags") == 0           || \
                                    (f_name).compare("size") == 0                   || \
                                    (f_name).compare("get_body") == 0               || \
                                    (f_name).compare("get_head") == 0               || \
                                    (f_name).compare("get_tag") == 0                || \
                                    (f_name).compare("get_num_nodes") == 0          || \
                                    (f_name).compare("get_node") == 0               || \
                                    (f_name).compare("get_node_text") == 0

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
    DeclarativeStatementNode *decl;
};


/* This is the generic Node class.
 * All other Nodes inherit from it, so it contains
 * members that will be used by multiple classes. */
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
        bool returns_value = false;
};

/* The names of Node classes are better understood
 * when compared to the grammar */
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
};


class IDNode: public Node {
    public:
        Entry *entry;
        IDNode(Entry *ent);
        string get_name();
        e_type get_type();
};


class FunctionCallNode: public Node {
    ArgsNode *args_list;
    string func_id;

    public:
    FunctionCallNode(string f, ArgsNode *a);
    FunctionCallNode(string f);
    void typecheck();
    string generate_std_rpl_function();
};


class ArrayInitNode: public Node{
    public:
        int array_length;
        std::vector<ExpressionNode *> *args_list;
        bool has_elements;
        ArrayInitNode();
        ArrayInitNode(ExpressionNode *arg);
        void add_arg(ExpressionNode *arg);
};


class ArgsNode: public Node {
    public:
        std::vector<ExpressionNode *> *args_list;

        ArgsNode();
        ArgsNode(ExpressionNode *arg);
        list<e_type> *to_enum_list();
        void add_arg(ExpressionNode *arg);
};


class TypeNode: public Node {
    public:
        ValueNode *value;
        TypeNode(e_type t, string name);
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
};


class ArrayAccessNode: public Node {
    public:
        ValueNode *value_node;
        ExpressionNode *en;

        ArrayAccessNode(ValueNode *v, ExpressionNode *e);
};


class DatasetAccessNode: public Node {
    public:
        ValueNode *value_node;
        string id;

        DatasetAccessNode(string c, string i);
};


class UnaryExpressionNode: public Node {
    public:
        enum e_op op;
        union operand right_operand;

        UnaryExpressionNode(UnaryExpressionNode *u, string _op);
        UnaryExpressionNode(UnaryExpressionNode *u, TypeNode *t);
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

        ValueNode *get_value_node();

        BinaryExpressionNode(BinaryExpressionNode *bl, string _op,BinaryExpressionNode *br);
        BinaryExpressionNode(BinaryExpressionNode *bl, string _op, UnaryExpressionNode *ur);
        BinaryExpressionNode(UnaryExpressionNode *ul);

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

class StreamReaderNode: public Node {
public:
    string name;
    ArgsNode *arg_list;

    StreamReaderNode(string n, ArgsNode *args_list);
    string generate_code(e_type type);
};


class LinkStatementNode: public Node {
    public:
        IDNode *id_node, *filter;
        ExpressionNode *expression_node;
        StreamReaderNode *stream_reader_node;
        string auxiliary = "";

        LinkStatementNode(IDNode *idn, ExpressionNode *expn);
        LinkStatementNode(IDNode *idn, ExpressionNode *expn, string func);
        LinkStatementNode(IDNode *idn, StreamReaderNode *srn);
        LinkStatementNode(IDNode *idn, StreamReaderNode *srn, string func);
        LinkStatementNode(IDNode *idn, IDNode *filt, StreamReaderNode *srn);
        LinkStatementNode(IDNode *idn, IDNode *filt, StreamReaderNode *srn, string func);

};


class StatementNode: public Node {
    public:
        union statements stmts;

        StatementNode(DeclarativeStatementNode *d);
        StatementNode(ConditionalStatementNode *c);
        StatementNode(JumpStatementNode *j);
        StatementNode(LoopStatementNode *l);
        StatementNode(LinkStatementNode *l);
};


class StatementListNode: public Node {
    public:
        vector<StatementNode *> *stmt_list;
        SymbolTableNode *st_node;

        StatementListNode();
        StatementListNode(SymbolTableNode *s);
        void push_statement(StatementNode *s);
};


class DatasetNode: public Node {
    public:
        string name;
        DeclArgsNode *decl_args;

        DatasetNode(string s, DeclArgsNode *d);
};


class FunctionNode: public Node {
    public:
        enum e_type type;
        string id;
        DeclArgsNode *decl_args;
        StatementListNode *stmt_list;

        FunctionNode(TypeNode *_type, string id_node, DeclArgsNode *decl_args_list, StatementListNode *stmt_list_n);
};


class ProgramSectionNode: public Node {
    union program_section contents;

    public:
    ProgramSectionNode(FunctionNode *f);
    ProgramSectionNode(DatasetNode *d);
    ProgramSectionNode(DeclarativeStatementNode *dsn);
};


class ProgramNode: public Node {
    public:
        ProgramNode();
        void add_section(ProgramSectionNode *);
        FunctionNode *func;
        ProgramNode(FunctionNode *f);
};
#endif
