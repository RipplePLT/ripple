#include "variable_tree.hpp"
#include <string>

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
	return this->right_operand.v_node->evaluate();
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
struct link_val BinaryExpressionNode::evaluate() {
	struct link_val result;
	switch(op) {
	case (PLUS):
		// add
		break;
	case (TIMES):
		// multiply
		break;
	case (NONE):
		return this->left_operand.u_exp->evaluate();
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
ValueNode::ValueNode(int *i) {
	this->val = { ltINT_PTR, (void *)i };
}
ValueNode::ValueNode(int i) {
	this->val = { ltINT, i };
}
struct link_val ValueNode::evaluate() {
	return {tINT, 5};
}
