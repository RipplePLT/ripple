#ifndef __VAR_TREE_HPP__
#define __VAR_TREE_HPP__

#include <string>
#include <string.h>
#include <iostream>
#include "../structures/enum.h"

using namespace std;

class ExpressionNode;
class BinaryExpressionNode;
class UnaryExpressionNode;
class ExpressionNode;
class ValueNode;

union operand {
    BinaryExpressionNode *b_exp;
    UnaryExpressionNode *u_exp;
    ValueNode *v_node;
};

enum link_val_type {
	ltINT,
	ltINT_PTR,
	ltNONE
};

struct link_val {
	enum link_val_type type;
	union {
		int intval;
		void *ptr;
	} value;
};

class LiteralNode {
public:
	struct link_val val;
	LiteralNode (int i);
	struct link_val evaluate();
	// @TODO other literal types
};

class VariableNode {
public:
	struct link_val val;
	int *var;
	VariableNode (int *var);
	// @TODO other var types
	struct link_val evaluate();
};

class ValueNode {
public:
	bool is_literal;
	LiteralNode *lit_node;
	VariableNode *var_node;

	ValueNode (LiteralNode *l);
	ValueNode (VariableNode *v);
	struct link_val evaluate();
};

class UnaryExpressionNode {
public:
    enum e_op op;
    union operand right_operand;

    UnaryExpressionNode(UnaryExpressionNode *u, string _op);
    UnaryExpressionNode(ValueNode *v);
	struct link_val evaluate();
};


class BinaryExpressionNode {
public:
    union operand left_operand;
    union operand right_operand;
    enum e_op op;
    bool left_is_binary;
    bool right_is_binary;

    BinaryExpressionNode(BinaryExpressionNode *bl, string _op,BinaryExpressionNode *br);
    BinaryExpressionNode(BinaryExpressionNode *bl, string _op, UnaryExpressionNode *ur);
    BinaryExpressionNode(UnaryExpressionNode *ul);
	struct link_val evaluate();
};


class ExpressionNode {
public:
    BinaryExpressionNode *bin_exp;
    ValueNode *value;

	ExpressionNode();
	~ExpressionNode();
    ExpressionNode(BinaryExpressionNode *b);
	struct link_val evaluate();
};

#endif
