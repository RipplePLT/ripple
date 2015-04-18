#ifndef __AST_H__
#define __AST_H__

#include <string>
#include <string.h>
#include <iostream>
#include <vector>
#include "../structures/enum.h"
#include "../structures/union.h"
#include "symbol_table/hashmap.h"

using namespace std;

class Node;
class ValueNode;
class ExpressionNode;
class BinaryExpressionNode;
class UnaryExpressionNode;
class LiteralNode;
class IDNode;
class ArgsNode;
class FunctionCallNode;
class ArrayAccessNode;
class DatasetAccessNode;
class ExpressionNode;
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
        e_type type;
};

class ExpressionNode: public Node {
public:
    BinaryExpressionNode *bin_exp;
    ValueNode *value;

   ExpressionNode(BinaryExpressionNode *b) {
        bin_exp = b;
        value = NULL;
   }

   ExpressionNode(BinaryExpressionNode *b, ValueNode *v) {
        bin_exp = b;
        value = v;
   }

   ~ExpressionNode() {
        delete bin_exp;
   }

   e_type get_type(){
        return type;
   }
};

class IDNode: public Node {
    Entry *entry;
public:
        IDNode(Entry *ent) { entry = ent; }
        ~IDNode() { }

        e_type get_type(){
            return entry->type;
        }
};

class FunctionCallNode: public Node {
    ArgsNode *args_list;
    IDNode *func_name;

public:
    FunctionCallNode(IDNode *func_name, ArgsNode *args_list){ 
        this->func_name = func_name;
        this->args_list = args_list;
        type = func_name->get_type(); 
    }
    FunctionCallNode(IDNode *func_name) {
        this->func_name = func_name;
        type = func_name->get_type(); 
    };

    e_type get_type(){
        return tINT;
    }

};

class LiteralNode: public Node {
    public:
    union literal val;

    // Constructors for different types
    LiteralNode(int i) { val.int_lit = i; type = tINT;  }
    LiteralNode(double d) { val.float_lit = d; type = tFLOAT; cout << "float" << endl; }
    LiteralNode(string s) { val.string_lit = s; type = tSTRING; }
    LiteralNode(bool b) { val.bool_lit = b; type = tBOOL; }
    LiteralNode(char b) { val.byte_lit = b; type = tBYTE; }

    e_type get_type(){
        return type;
    }
};

class ArrayAccessNode: public Node {
public:
    ValueNode *vn;
    ExpressionNode *en;

    ArrayAccessNode(ValueNode *valueNode, ExpressionNode *expressionNode) {
        vn = valueNode;
        en = expressionNode;
    }

    e_type get_type(){
        return tINT;
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

    e_type get_type(){
        return tINT;
    }
};

class ValueNode: public Node {
    public:
    union value val;

    ValueNode(IDNode *i) { val.id_val = i; type = i->get_type(); }
    ValueNode(LiteralNode *l) { val.lit_val = l; type = l->get_type(); }
    ValueNode(FunctionCallNode *f) { val.function_call_val = f; type = f->get_type(); } 
    ValueNode(ArrayAccessNode *a) { val.array_access_val = a; type = a->get_type(); }
    ValueNode(DatasetAccessNode *d) { val.dataset_access_val = d; type = d->get_type(); }
    ValueNode(ExpressionNode *e) { val.expression_val = e; type = e->get_type(); }

    void print_type(){
        switch(type){
            case tINT:
                cout << "int" << endl;
                break;
            case tFLOAT:
                cout << "float" << endl;
                break;
            case tSTRING:
                cout << "string" << endl;
                break;
            case tBOOL:
                cout << "bool" << endl;
                break;
            default:
                cout << "crikey" << endl;
        }
    }


};

class ArgsNode: public Node {
    std::vector<ExpressionNode*> args_list;

    public:
        ArgsNode() {};
	void add_arg(ExpressionNode* arg) { args_list.push_back(arg); }
};

class DeclArgsNode: public Node {
    std::vector<IDNode*> decl_args_list;

    public:
        DeclArgsNode() {};
    void add_arg(IDNode* arg) { decl_args_list.push_back(arg); }
};



class UnaryExpressionNode: public Node {
    
    union operand right_operand;

public:
    enum e_op op;
    
    UnaryExpressionNode(UnaryExpressionNode *u, string _op)
    {
        op = get_op(_op);
        right_operand.u_exp = u;
    }

    UnaryExpressionNode(ValueNode *v)
    {
        op = NONE;
        right_operand.v_node = v;
    }
};

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
        left_is_binary = right_is_binary = true;
    }
    
    BinaryExpressionNode(BinaryExpressionNode *bl, string _op, UnaryExpressionNode *ur) {
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

        delete bl;
    }

    BinaryExpressionNode(UnaryExpressionNode *ul) {
        left_operand.u_exp = ul;
        op = NONE;
    }

};

class DeclarativeStatementNode: public Node {
public:
    e_type type;
    ExpressionNode *en;

    DeclarativeStatementNode(string _type, ExpressionNode *expression_node){
        type = get_type(_type);
        en = expression_node;
    }

    DeclarativeStatementNode(ExpressionNode *expression_node){
        en = expression_node;
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
    }

    StatementNode(ConditionalStatementNode *c) {
        stmts.cond = c;
    }

    StatementNode(JumpStatementNode *j) {
        stmts.jump = j;
    }

    StatementNode(LoopStatementNode *l) {
        stmts.loop = l;
    }
};

class StatementListNode: public Node {
public:
    std::vector<StatementNode *> stmt_list;

    void push_statement(StatementNode *s){
        stmt_list.push_back(s);
    }

};

class FunctionNode: public Node {
public:
    enum e_type type;
    IDNode *id;
    StatementListNode *stmt_list;

    FunctionNode(string _type, IDNode *id_node, StatementListNode *stmt_list_n){
        type = get_type(_type);
        id = id_node;
        stmt_list = stmt_list_n;
    }
};

#endif
