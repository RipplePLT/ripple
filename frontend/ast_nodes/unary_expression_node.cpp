#ifndef INCLUDED_UNARY_EXPRESSION_NODE
#include "unary_expression_node.h"
#endif

#include <iostream>

namespace Ripple {
namespace AST {

UnaryExpressionNode::UnaryExpressionNode(Ripple::AST::ValueNode *_value_node){
	d_expression.value_node = _value_node;
	d_operator = unary_op_none;

	base_type = _value_node->base_type;
	derived_type = _value_node->derived_type;

	code = _value_node->code;
#ifdef DEBUG
	std::cout << code << std::endl;
#endif
}

UnaryExpressionNode::UnaryExpressionNode(unary_operator _operator, Ripple::AST::UnaryExpressionNode *_unary_expression_node){

	d_expression.unary_expression_node = _unary_expression_node;
	d_operator = _operator;

	base_type = _unary_expression_node->base_type;
	derived_type = _unary_expression_node->derived_type;

	type_check();

	switch(d_operator){
		case unary_op_minus:
			code = "(-" + _unary_expression_node->code + ")";
			base_type = (base_type == t_double ? t_double : t_int);
			derived_type = t_none;
			break;
		case unary_op_size_of:
			code = "(sizeof(" + _unary_expression_node->code + "))";
			base_type = t_int;
			derived_type = t_none;
			break;
		case unary_op_not:
			code = "(!" + _unary_expression_node->code + ")";
			base_type = t_bool;
			derived_type = t_none;
			break;
		default:
			code = _unary_expression_node->code;
			break;
	}

#ifdef DEBUG
	std::cout << code << std::endl;
#endif
}

void
UnaryExpressionNode::type_check(){
	
	// if no operator was applied the type must be valid
	if(d_operator == unary_op_none){
		return;
	}

	// sizeof operator is valid for all base and derived types
	if(d_operator == unary_op_size_of){
		return;
	}

	if(d_operator == unary_op_minus){
		// unary minus is invalid for derived types
		if(derived_type != t_none){
			error = true;
			std::cout << INVAL_UNARY_MINUS_ERR << std::endl;
			return;
		}

		// unary minus is only valid for numbers
		if(!(base_type == t_int || base_type == t_double)){
			error = true;
			std::cout << INVAL_UNARY_MINUS_ERR << std::endl;
			return;
		}
	}

	if(d_operator == unary_op_not){
		// unary not is invalid for derived types
		if(derived_type != t_none){
			error = true;
			std::cout << INVAL_UNARY_NOT_ERR << std::endl;
			return;
		}

		// unary not is only valid for booleans
		if(!(base_type == t_bool)){
			error = true;
			std::cout << INVAL_UNARY_NOT_ERR << std::endl;
			return;
		}
	}
}


}
}