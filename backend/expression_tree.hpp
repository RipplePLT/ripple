#ifndef __VAR_TREE_HPP__
#define __VAR_TREE_HPP__

#include <string>
#include <string.h>
#include <iostream>
#include "../structures/enum.h"

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

/*
 * The struct link_val represents a linked variable's value and its
 * type, so that we can deal with dynamic types.
 */
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


// @TODO Implement non-integer literals
class LiteralNode {
public:
	struct link_val val;
	LiteralNode (int i);
	struct link_val evaluate();
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
	struct link_val val;
	int *var;
	VariableNode (int *var);
	struct link_val evaluate();
};

/*
 * Contains a LiteralNode or a VariableNode.
 */
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
	static int get_int_val(struct link_val l);
	static struct link_val add(struct link_val a, struct link_val b);
	static struct link_val multiply(struct link_val a,
		struct link_val b);
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
