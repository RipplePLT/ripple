#include <iostream>
#include <string>
#include <cmath>
#include "expression_tree.hpp"

enum e_op str_to_op(const std::string op_string) {
    if(op_string.compare("+") == 0)
        return PLUS;
    else if (op_string.compare("-") == 0)
        return MINUS;
    else if (op_string.compare("*") == 0)
        return TIMES;
    else if (op_string.compare("/") == 0)
        return DIV;
    else if (op_string.compare("//") == 0)
        return FLDIV;
    else if (op_string.compare("^") == 0)
        return EXP;
    else if (op_string.compare("and") == 0)
        return bAND;
    else if (op_string.compare("or") == 0)
        return bOR;
    else if (op_string.compare("not") == 0)
        return bNOT;
    else if (op_string.compare("==") == 0)
        return EQ;
    else if (op_string.compare("!=") == 0)
        return NE;
    else if (op_string.compare(">") == 0)
        return GT;
    else if (op_string.compare("<") == 0)
        return LT;
    else if (op_string.compare(">=") == 0)
        return GE;
    else if (op_string.compare("<=") == 0)
        return LE;
    else if (op_string.compare("@") == 0)
        return SIZE;
	else
		return NONE;
};

/* UnaryExpressionNode */
UnaryExpressionNode::UnaryExpressionNode(UnaryExpressionNode *u, string _op)
{
    op = str_to_op(_op);
    right_operand.u_exp = u;
}
UnaryExpressionNode::UnaryExpressionNode(ValueNode *v)
{
    op = NONE;
    right_operand.v_node = v;
}
struct link_val UnaryExpressionNode::evaluate() {
	struct link_val result = (op == NONE) ? this->right_operand.v_node->evaluate() :
		this->right_operand.u_exp->evaluate();
	return result;
}

/* BinaryExpressionNode */
BinaryExpressionNode::BinaryExpressionNode(BinaryExpressionNode *bl, string _op,BinaryExpressionNode *br) {
    left_operand.b_exp = bl;
    right_operand.b_exp = br;
    op = str_to_op(_op);
    left_is_binary = right_is_binary = true;
}
BinaryExpressionNode::BinaryExpressionNode(BinaryExpressionNode *bl, string _op, UnaryExpressionNode *ur) {
    left_operand.b_exp = bl;
    right_operand.u_exp = ur;
    op = str_to_op(_op);
    left_is_binary = true;
    right_is_binary = false;
}
BinaryExpressionNode::BinaryExpressionNode(UnaryExpressionNode *ul) {
    left_operand.u_exp = ul;
    op = NONE;
}

int BinaryExpressionNode::get_int_val(struct link_val l) {
	return (l.type == ltINT) ? l.value.intval :
		(l.type == ltINT_PTR) ? *(int *)l.value.ptr :
		-1000000; // should never happen
}

struct link_val BinaryExpressionNode::add(struct link_val a,
		struct link_val b) {
	int a_int, b_int;
	struct link_val result;

	a_int = get_int_val(a);
	b_int = get_int_val(b);

	result.type = ltINT;
	result.value.intval = a_int + b_int;
	return result;
}

struct link_val BinaryExpressionNode::subtract(struct link_val a,
		struct link_val b) {
	int a_int, b_int;
	struct link_val result;

	a_int = get_int_val(a);
	b_int = get_int_val(b);

	result.type = ltINT;
	result.value.intval = a_int - b_int;
	return result;

}

struct link_val BinaryExpressionNode::multiply (struct link_val a,
		struct link_val b) {
	int a_int, b_int;
	struct link_val result;

	a_int = get_int_val(a);
	b_int = get_int_val(b);

	result.type = ltINT;
	result.value.intval = a_int * b_int;
	return result;
}

struct link_val BinaryExpressionNode::divide (struct link_val a,
		struct link_val b) {
	int a_int, b_int;
	struct link_val result;

	a_int = get_int_val(a);
	b_int = get_int_val(b);

	result.type = ltINT;
	result.value.intval = a_int / b_int;
	return result;
}

struct link_val BinaryExpressionNode::exp (struct link_val a,
		struct link_val b) {
	int a_int, b_int;
	struct link_val result;

	a_int = get_int_val(a);
	b_int = get_int_val(b);

	result.type = ltINT;
	result.value.intval = pow(a_int, b_int);
	return result;
}

struct link_val BinaryExpressionNode::evaluate() {
	struct link_val result, left_value, right_value;

	if (this->op == NONE)
		return this->left_operand.u_exp->evaluate();

	left_value = left_is_binary ? this->left_operand.b_exp->evaluate() :
		this->left_operand.u_exp->evaluate();
	right_value = right_is_binary ? this->right_operand.b_exp->evaluate() :
		this->right_operand.u_exp->evaluate();

	switch(op) {
	case (PLUS):
		return add(left_value, right_value);
		break;
	case (TIMES):
		return multiply(left_value, right_value);
		break;
	case (MINUS):
		return subtract(left_value, right_value);
		break;
	case (DIV):
		return divide(left_value, right_value);
		break;
	case (EXP):
		return exp(left_value, right_value);
		break;
	default:
		result.type = ltNONE;
		result.value.ptr = NULL;
	}
	return result;
}

/* ExpressionNode */
ExpressionNode::ExpressionNode() { }
ExpressionNode::~ExpressionNode() { }
ExpressionNode::ExpressionNode(BinaryExpressionNode *b) {
    bin_exp = b;
    value = NULL;
}
struct link_val ExpressionNode::evaluate() {
	return this->bin_exp->evaluate();
}

/* ValueNode */
ValueNode::ValueNode(LiteralNode *l) {
	this->is_literal = true;
	this->lit_node = l;
}
ValueNode::ValueNode(VariableNode *v) {
	this->is_literal = false;
	this->var_node = v;
}
struct link_val ValueNode::evaluate() {
	return is_literal ? lit_node->evaluate() : var_node->evaluate();
}

/* LiteralNode */
LiteralNode::LiteralNode(int i) {
	this->val.type = ltINT;
	this->val.value.intval = i;
}
struct link_val LiteralNode::evaluate() {
	return this->val;
}

/* VariableNode */
VariableNode::VariableNode(int *var) {
	this->var = var;
	this->val.type = ltINT_PTR;
	this->val.value.ptr = (void *)var;
}
struct link_val VariableNode::evaluate() {
	return this->val;
}
