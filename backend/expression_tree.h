#ifndef __VAR_TREE_H__
#define __VAR_TREE_H__

#include <string>
#include <string.h>
#include <iostream>
#include <vector>
#include "../structures/enum.h"
#include "link_val.h"

/*
 * The nodes defined in this file are used at runtime to construct
 * an ExpressionNode, which represents the expression to which a
 * linked variable is linked.
 *
 * All node classes implement the evaluate() method, which returns a
 * link_val struct representing the value of a given node.
 */

using namespace std;

class ExpressionNode;
class BinaryExpressionNode;
class UnaryExpressionNode;
class ValueNode;
class LiteralNode;
class VariableNode;
class StreamReaderNode;

union operand {
    BinaryExpressionNode *b_exp;
    UnaryExpressionNode *u_exp;
    ValueNode *v_node;
};

class StreamReaderNode {
public:
	link_val val;
	vector<void*> *dependencies;

	StreamReaderNode (enum link_val_type t);
	link_val evaluate();
};

class LiteralNode {
public:
	link_val val;
	vector<void*> *dependencies;

	LiteralNode (int i);
	LiteralNode (double f);
	LiteralNode (bool b);
	LiteralNode (const char *s);
	link_val evaluate();
};

/*
 * Used to represent regular variables (e.g. "int x") in a link
 * expression.
 * Ex: If x is a Ripple integer, then "link (y <- x)" should create a
 * VariableNode for x.
 *
 */
class VariableNode {
public:
	link_val val;
	void *var;
	vector<void*> *dependencies;

	VariableNode (int *var);
	VariableNode (double *var);
	VariableNode (bool *var);
	VariableNode (string **var);
	link_val evaluate();
};

/*
 * Represents a call to a function in a link expression.
 */
class FunctionCallNode {
public:
	link_val val;
	void *fn;
	vector<void*> *dependencies;

	FunctionCallNode (void *);
	link_val evaluate ();
};

/*
 * Contains a LiteralNode or a VariableNode.
 */
class ValueNode {
public:
	bool is_literal;
	bool is_expression;
	bool is_stream;
	LiteralNode *lit_node;
	VariableNode *var_node;
	ExpressionNode *expr_node;
	StreamReaderNode *sr_node;
	vector<void*> *dependencies;

	ValueNode (LiteralNode *l);
	ValueNode (VariableNode *v);
	ValueNode (ExpressionNode *e);
	ValueNode (StreamReaderNode *s);
	link_val evaluate();
};

class UnaryExpressionNode {
public:
    enum e_op op;
    union operand right_operand;
	vector<void*> *dependencies;

    UnaryExpressionNode(UnaryExpressionNode *u, string _op);
    UnaryExpressionNode(ValueNode *v);
	link_val evaluate();
};


class BinaryExpressionNode {
public:
    union operand left_operand;
    union operand right_operand;
    enum e_op op;
    bool left_is_binary;
    bool right_is_binary;
	vector<void*> *dependencies;

    BinaryExpressionNode(BinaryExpressionNode *bl, string _op,BinaryExpressionNode *br);
    BinaryExpressionNode(BinaryExpressionNode *bl, string _op, UnaryExpressionNode *ur);
    BinaryExpressionNode(UnaryExpressionNode *ul);
	link_val evaluate();
};


class ExpressionNode {
public:
    BinaryExpressionNode *bin_exp;
    ValueNode *value;
	vector<void*> *dependencies;

	ExpressionNode();
	~ExpressionNode();
    ExpressionNode(BinaryExpressionNode *b);
	link_val evaluate();
	static vector<void*> *dep_union(vector<void*> *r1, vector<void*> *r2);
};

#endif
