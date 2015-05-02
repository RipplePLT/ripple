#ifndef __VAR_TREE_HPP__
#define __VAR_TREE_HPP__

#include <string>
#include <string.h>
#include <iostream>
#include <vector>
#include "../structures/enum.h"
#include "link_val.hpp"

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
class ExpressionNode;
class ValueNode;

union operand {
    BinaryExpressionNode *b_exp;
    UnaryExpressionNode *u_exp;
    ValueNode *v_node;
};

// @TODO Implement non-integer literals
class LiteralNode {
public:
	link_val val;
	vector<void*> *dependencies;

	LiteralNode (int i);
	LiteralNode (double f);
	link_val evaluate();
};

/*
 * Used to represent regular variables (e.g. "int x") in a link
 * expression.
 * Ex: If x is a Ripple integer, then "link (y <- x)" should create a
 * VariableNode for x.
 *
 * @TODO Implement non-integer types
 */
class VariableNode {
public:
	link_val val;
	void *var;
	vector<void*> *dependencies;

	VariableNode (int *var);
	VariableNode (double *var);
	link_val evaluate();
};

/*
 * Contains a LiteralNode or a VariableNode.
 */
class ValueNode {
public:
	bool is_literal;
	LiteralNode *lit_node;
	VariableNode *var_node;
	vector<void*> *dependencies;

	ValueNode (LiteralNode *l);
	ValueNode (VariableNode *v);
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
