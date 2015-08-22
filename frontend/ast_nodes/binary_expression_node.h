#ifndef INCLUDED_BINARY_EXPRESSION_NODE
#define INCLUDED_BINARY_EXPRESSION_NODE

#ifndef INCLUDED_AST_NODE
#include "ast_node.h"
#endif

#ifndef INCLDED_UNARY_EXPRESSION_NODE
#include "unary_expression_node.h"
#endif

namespace Ripple {
namespace AST {

// Foreward declaration of class
class BinaryExpressionNode;


enum binary_operator {
	binary_op_none = 0,
	binary_op_plus = 1,
	binary_op_minus = 2,
	binary_op_times = 3,
	binary_op_divide = 4,
	binary_op_fl_divide = 5,
	binary_op_modulus = 6,
	binary_op_exponentiation = 7,
	binary_op_and = 8,
	binary_op_or = 9,
	binary_op_equals = 10,
	binary_op_not_equals = 11,
	binary_op_gt = 12,
	binary_op_lt = 13,
	binary_op_ge = 14,
	binary_op_le = 15
};

namespace {
	union binary_expression {
		BinaryExpressionNode *binary_expression_node;
		UnaryExpressionNode *unary_expression_node;
	};
}

class BinaryExpressionNode : public ASTNode {
private:
	binary_expression d_left_expression;
	binary_expression d_right_expression;
	binary_operator d_operator;
	void type_check();

public:
	BinaryExpressionNode(Ripple::AST::UnaryExpressionNode *_unary_expression_node);
	BinaryExpressionNode(Ripple::AST::BinaryExpressionNode *_l_binary_expression_node,
						 Ripple::AST::binary_operator _operator,
						 Ripple::AST::BinaryExpressionNode *_r_binary_expression_node);
	
};

}
}

#endif