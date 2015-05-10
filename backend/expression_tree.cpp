#include "expression_tree.h"

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
	dependencies = u->dependencies;
}


UnaryExpressionNode::UnaryExpressionNode(ValueNode *v)
{
    op = NONE;
    right_operand.v_node = v;
	dependencies = v->dependencies;
}


link_val UnaryExpressionNode::evaluate() {
	link_val result = (op == NONE) ? this->right_operand.v_node->evaluate() :
		(op == bNOT) ? !this->right_operand.u_exp->evaluate() :
		(op == MINUS) ? -this->right_operand.u_exp->evaluate() :
		(op == SIZE) ? this->right_operand.u_exp->evaluate().size_node() :
		this->right_operand.u_exp->evaluate();
	return result;
}


/* BinaryExpressionNode */
BinaryExpressionNode::BinaryExpressionNode(BinaryExpressionNode *bl, string _op,BinaryExpressionNode *br) {
    left_operand.b_exp = bl;
    right_operand.b_exp = br;
    op = str_to_op(_op);
    left_is_binary = right_is_binary = true;
	dependencies = ExpressionNode::dep_union(bl->dependencies, br->dependencies);
}


BinaryExpressionNode::BinaryExpressionNode(BinaryExpressionNode *bl, string _op, UnaryExpressionNode *ur) {
    left_operand.b_exp = bl;
    right_operand.u_exp = ur;
    op = str_to_op(_op);
    left_is_binary = true;
    right_is_binary = false;
	if (bl->dependencies == NULL && ur->dependencies == NULL)
		dependencies = NULL;
	else if (bl->dependencies == NULL)
		dependencies = ur->dependencies;
	else if (ur->dependencies == NULL)
		dependencies = bl->dependencies;
	else
		dependencies = ExpressionNode::dep_union(bl->dependencies, ur->dependencies);
}


BinaryExpressionNode::BinaryExpressionNode(UnaryExpressionNode *ul) {
    left_operand.u_exp = ul;
    op = NONE;
	dependencies = ul->dependencies;
}


link_val BinaryExpressionNode::evaluate() {
	link_val result, left_value, right_value;

	if (this->op == NONE)
		return this->left_operand.u_exp->evaluate();

	left_value = left_is_binary ? this->left_operand.b_exp->evaluate() :
		this->left_operand.u_exp->evaluate();
	right_value = right_is_binary ? this->right_operand.b_exp->evaluate() :
		this->right_operand.u_exp->evaluate();

	switch(op) {
	case (PLUS):
		return left_value + right_value;
		break;
	case (TIMES):
		return left_value * right_value;
		break;
	case (MINUS):
		return left_value - right_value;
		break;
	case (DIV):
		return left_value / right_value;
		break;
	case (EXP):
		return left_value ^ right_value;
		break;
	case (GT):
		return left_value > right_value;
		break;
	case (LT):
		return left_value < right_value;
		break;
	case (GE):
		return left_value >= right_value;
		break;
	case (LE):
		return left_value <= right_value;
		break;
	case (EQ):
		return left_value == right_value;
		break;
	case (NE):
		return left_value != right_value;
		break;
	case (bAND):
		return left_value && right_value;
		break;
	case (bOR):
		return left_value || right_value;
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
	dependencies = b->dependencies;
}


link_val ExpressionNode::evaluate() {
	return this->bin_exp->evaluate();
}


vector<void *> *ExpressionNode::dep_union(vector<void *> *r1, vector<void *> *r2) {
	int i;
	if (r1 == NULL && r2 == NULL)
		return NULL;
	else if (r1 == NULL)
		return r2;
	else if (r2 == NULL)
		return r1;

	// Exclude duplicates from union
	int j;
	bool is_duplicate;
	for (i = 0; i < r2->size(); i++) {
		is_duplicate = false;
		for (j = 0; j < r1->size(); j++)
			if ((*r1)[j] == (*r2)[i])
				is_duplicate = true;
		if (!is_duplicate)
			r1->push_back( (*r2)[i] );
	}

	free(r2);
	return r1;
}


/* ValueNode */
ValueNode::ValueNode(LiteralNode *l) {
	this->is_literal = true;
	this->is_expression = false;
	this->is_stream = false;
	this->lit_node = l;
	
	this->dependencies = NULL;
}


ValueNode::ValueNode(VariableNode *v) {
	this->is_literal = false;
	this->is_expression = false;
	this->is_stream = false;
	this->var_node = v;

	this->dependencies = v->dependencies;
}


ValueNode::ValueNode(ExpressionNode *e) {
	this->is_literal = false;
	this->is_expression = true;
	this->is_stream = false;
	this->expr_node = e;

	this->dependencies = e->dependencies;
}


ValueNode::ValueNode(StreamReaderNode *s) {
	this->is_literal = false;
	this->is_expression = false;
	this->is_stream = true;
	this->sr_node = s;

	this->dependencies = s->dependencies;
}


link_val ValueNode::evaluate() {
	return is_literal ? lit_node->evaluate() :
		is_expression? expr_node->evaluate() :
		is_stream ? sr_node->evaluate() :
		var_node->evaluate();
}


/* LiteralNode */
LiteralNode::LiteralNode(int i) {
	this->val.type = ltINT;
	this->val.value.intval = i;
	this->dependencies = NULL;
}


LiteralNode::LiteralNode(double d) {
	this->val.type = ltDOUBLE;
	this->val.value.doubleval = d;
	this->dependencies = NULL;
}


LiteralNode::LiteralNode(bool b) {
	this->val.type = ltBOOL;
	this->val.value.boolval = b;
	this->dependencies = NULL;
}


LiteralNode::LiteralNode(const char *s) {
	this->val.type = ltSTR;
	this->val.value.strval = new string(s);
	this->dependencies = NULL;
}


link_val LiteralNode::evaluate() {
	return this->val;
}

/* VariableNode */
VariableNode::VariableNode(int *var) {
	this->var = var;
	this->val.type = ltINT_PTR;
	this->val.value.ptr = (void *)var;

	this->dependencies = new vector<void *>();
	this->dependencies->push_back(this->val.value.ptr);
}


VariableNode::VariableNode(double *var) {
	this->var = var;
	this->val.type = ltDOUBLE_PTR;
	this->val.value.ptr = (void *)var;

	this->dependencies = new vector<void *>();
	this->dependencies->push_back(this->val.value.ptr);
}


VariableNode::VariableNode(bool *var) {
	this->var = var;
	this->val.type = ltBOOL_PTR;
	this->val.value.ptr = (void *)var;

	this->dependencies = new vector<void *>();
	this->dependencies->push_back(this->val.value.ptr);
}


VariableNode::VariableNode(string **s) {
	this->var = s;
	this->val.type = ltSTR_PTR;
	this->val.value.ptr = (void *)s;

	this->dependencies = new vector<void *>();
	this->dependencies->push_back(this->val.value.ptr);
}


link_val VariableNode::evaluate() {
	return this->val;
}


StreamReaderNode::StreamReaderNode(enum link_val_type t) {
	this->val.type = t;
	this->dependencies = new vector<void *>();
	this->dependencies->push_back(&this->val.value);
}


link_val StreamReaderNode::evaluate () {
	return this->val;
}
