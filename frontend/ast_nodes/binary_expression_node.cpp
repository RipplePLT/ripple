#ifndef INCLUDED_BINARY_EXPRESSION_NODE
#include "binary_expression_node.h"
#endif

#include <iostream>

namespace Ripple {
namespace AST {

BinaryExpressionNode::BinaryExpressionNode(Ripple::AST::UnaryExpressionNode *_unary_expression_node){
	d_left_expression.unary_expression_node = _unary_expression_node;
	d_operator = binary_op_none;

	base_type = _unary_expression_node->base_type;
	derived_type = _unary_expression_node->derived_type;

	code = _unary_expression_node->code;
}

BinaryExpressionNode::BinaryExpressionNode(Ripple::AST::BinaryExpressionNode *_l_binary_expression_node,
										   Ripple::AST::binary_operator _operator,
										   Ripple::AST::BinaryExpressionNode *_r_binary_expression_node){

	d_left_expression.binary_expression_node = _l_binary_expression_node;
	d_operator = _operator;
	d_right_expression.binary_expression_node = _r_binary_expression_node;

	derived_type = t_none;

	type_check();

#ifdef DEBUG
	std::cout << code << std::endl;
#endif
}

void
BinaryExpressionNode::type_check(){
	
	// save pointers for easy access
	BinaryExpressionNode *b_left = d_left_expression.binary_expression_node;
	BinaryExpressionNode *b_right = d_right_expression.binary_expression_node;

	// binary expressions can only be performed between base types
	if(b_left->derived_type != t_none && b_right->derived_type != t_none){
		error = true;
		std::cout << INVAL_BINARY_DERIVED_ERR << std::endl;
		return;
	}

	if(d_operator == binary_op_exponentiation){
		code = "pow(" + b_left->code + "," +  b_right->code + ")";
		base_type = ((b_left->base_type == t_double || b_right->base_type == t_double) 
								? t_double : t_int);
		
		if(b_left->base_type != t_int || 
		   b_left->base_type != t_double || 
		   b_right->base_type != t_int || 
		   b_right->base_type != t_double){

		   	// if both aren't numbers this is an invalid operation
			error = true;
			std::cout << INVAL_BINARY_EXP_ERR << std::endl;
		}
		
		return;
	}

	if(d_operator == binary_op_plus){
		code = "(" + b_left->code + " + " + b_right->code + ")";
		base_type = ((b_left->base_type == t_double || b_right->base_type == t_double) ? t_double : t_int);

		if(b_left->base_type == t_string && b_right->base_type != t_string){
			code = "(" + b_left->code + " + std::to_string(" + b_right->code + "))";
			base_type = t_string;
		}

		if(b_left->base_type != t_string && b_right->base_type == t_string){
			code = "(std::to_string(" + b_left->code + ") + " + b_right->code + ")";
			base_type = t_string;
		}

		if(b_left->base_type == t_bool || b_right->base_type == t_bool){
			error = true;
			std::cout << INVAL_BINARY_PLUS_ERR << std::endl;
		}

		return;
	}

	if(d_operator == binary_op_minus){
		code = "(" + b_left->code + " - " + b_right->code + ")";
		base_type = ((b_left->base_type == t_double || b_right->base_type == t_double) ? t_double : t_int);
		
		if(b_left->base_type != t_int || 
		   b_left->base_type != t_double || 
		   b_right->base_type != t_int || 
		   b_right->base_type != t_double){

		   	// if both aren't numbers this is an invalid operation
			error = true;
			std::cout << INVAL_BINARY_MINUS_ERR << std::endl;
		}

		return;
	}

	if(d_operator == binary_op_times){
		code = "(" + b_left->code + " * " + b_right->code + ")";
		base_type = ((b_left->base_type == t_double || b_right->base_type == t_double) ? t_double : t_int);
		
		if(b_left->base_type != t_int || 
		   b_left->base_type != t_double || 
		   b_right->base_type != t_int || 
		   b_right->base_type != t_double){

		   	// if both aren't numbers this is an invalid operation
			error = true;
			std::cout << INVAL_BINARY_TIMES_ERR << std::endl;
		}

		return;
	}

	if(d_operator == binary_op_divide){
		code = "(" + b_left->code + " / " + b_right->code + ")";
		base_type = ((b_left->base_type == t_double || b_right->base_type == t_double) ? t_double : t_int);
		
		if(b_left->base_type != t_int || 
		   b_left->base_type != t_double || 
		   b_right->base_type != t_int || 
		   b_right->base_type != t_double){

		   	// if both aren't numbers this is an invalid operation
			error = true;
			std::cout << INVAL_BINARY_DIV_ERR << std::endl;
		}

		return;
	}

	if(d_operator == binary_op_fl_divide){
		code = "(" + b_left->code + " / (double)" + b_right->code + ")";
		base_type = t_double;

		if(b_left->base_type != t_int || 
		   b_left->base_type != t_double || 
		   b_right->base_type != t_int || 
		   b_right->base_type != t_double){

		   	// if both aren't numbers this is an invalid operation
			error = true;
			std::cout << INVAL_BINARY_FLDIV_ERR << std::endl;
		}

		return;
	}

	if(d_operator == binary_op_modulus){
		code = "(" + b_left->code + " % " + b_right->code + ")";
		base_type = t_int;

		if(b_left->base_type != t_int || 
		   b_left->base_type != t_double || 
		   b_right->base_type != t_int || 
		   b_right->base_type != t_double){

		   	// if both aren't numbers this is an invalid operation
			error = true;
			std::cout << INVAL_BINARY_MOD_ERR << std::endl;
		}

		return;
	}

	if(d_operator == binary_op_and){
		code = "(" + b_left->code + " && " + b_right->code + ")";
		base_type = t_bool;

		if(!(b_left->base_type == t_bool && b_right->base_type == t_bool)){
			// both operands must be booleans
			error = true;
			std::cout << INVAL_BINARY_AND_ERR << std::endl;
		}

		return;
	}

	if(d_operator == binary_op_or){
		code = "(" + b_left->code + " || " + b_right->code + ")";
		base_type = t_bool;

		if(!(b_left->base_type == t_bool && b_right->base_type == t_bool)){
			// both operands must be booleans
			error = true;
			std::cout << INVAL_BINARY_OR_ERR << std::endl;
		}

		return;
	}

	if(d_operator == binary_op_equals){
		code = "(" + b_left->code + " == " + b_right->code + ")";
		base_type = t_bool;

		if(b_left->base_type != b_right->base_type){
		   	// if both aren't the same type this is an invalid operation
			error = true;
			std::cout << INVAL_BINARY_EQ_ERR << std::endl;
			return;
		}

		if(b_left->base_type == t_string){
			code = "(" + b_left->code + ".compare(" + b_right->code + ") == 0)";
		}

		return;
	}

	if(d_operator == binary_op_not_equals){
		code = "(" + b_left->code + " != " + b_right->code + ")";
		base_type = t_bool;

		if(b_left->base_type != b_right->base_type){
		   	// if both aren't the same type this is an invalid operation
			error = true;
			std::cout << INVAL_BINARY_NE_ERR << std::endl;
		}

		if(b_left->base_type == t_string){
			code = "(" + b_left->code + ".compare(" + b_right->code + ") != 0)";
		}

		return;
	}

	if(d_operator == binary_op_gt){
		code = "(" + b_left->code + " > " + b_right->code + ")";
		base_type = t_bool;

		if(b_left->base_type != t_int || 
		   b_left->base_type != t_double || 
		   b_right->base_type != t_int || 
		   b_right->base_type != t_double){

		   	// if both aren't numbers this is an invalid operation
			error = true;
			std::cout << INVAL_BINARY_GT_ERR << std::endl;
		}

		return;
	}

	if(d_operator == binary_op_lt){
		code = "(" + b_left->code + " < " + b_right->code + ")";
		base_type = t_bool;

		if(b_left->base_type != t_int || 
		   b_left->base_type != t_double || 
		   b_right->base_type != t_int || 
		   b_right->base_type != t_double){

		   	// if both aren't numbers this is an invalid operation
			error = true;
			std::cout << INVAL_BINARY_LT_ERR << std::endl;
		}

		return;
	}

	if(d_operator == binary_op_ge){
		code = "(" + b_left->code + " >= " + b_right->code + ")";
		base_type = t_bool;

		if(b_left->base_type != t_int || 
		   b_left->base_type != t_double || 
		   b_right->base_type != t_int || 
		   b_right->base_type != t_double){

		   	// if both aren't numbers this is an invalid operation
			error = true;
			std::cout << INVAL_BINARY_GE_ERR << std::endl;
		}

		return;
	}

	if(d_operator == binary_op_le){
		code = "(" + b_left->code + " <= " + b_right->code + ")";
		base_type = t_bool;

		if(b_left->base_type != t_int || 
		   b_left->base_type != t_double || 
		   b_right->base_type != t_int || 
		   b_right->base_type != t_double){

		   	// if both aren't numbers this is an invalid operation
			error = true;
			std::cout << INVAL_BINARY_LE_ERR << std::endl;
		}

		return;
	}

}

}
}