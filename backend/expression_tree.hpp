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
	vector<void*> *refs;

	LiteralNode (int i);
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
	int *var;
	vector<void*> *refs;

	VariableNode (int *var);
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
	vector<void*> *refs;

	ValueNode (LiteralNode *l);
	ValueNode (VariableNode *v);
	link_val evaluate();
};

class UnaryExpressionNode {
public:
    enum e_op op;
    union operand right_operand;
	vector<void*> *refs;

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
	vector<void*> *refs;

    BinaryExpressionNode(BinaryExpressionNode *bl, string _op,BinaryExpressionNode *br);
    BinaryExpressionNode(BinaryExpressionNode *bl, string _op, UnaryExpressionNode *ur);
    BinaryExpressionNode(UnaryExpressionNode *ul);
	link_val evaluate();
	static int get_int_val(link_val l);
	static link_val add(link_val a, link_val b);
	static link_val subtract(link_val a, link_val b);
	static link_val multiply(link_val a,
		link_val b);
	static link_val divide(link_val a,
		link_val b);
	static link_val exp(link_val a, link_val b);
};


class ExpressionNode {
public:
    BinaryExpressionNode *bin_exp;
    ValueNode *value;
	vector<void*> *refs;

	ExpressionNode();
	~ExpressionNode();
    ExpressionNode(BinaryExpressionNode *b);
	link_val evaluate();
	static vector<void*> *ref_union(vector<void*> *r1, vector<void*> *r2);
};

#endif
