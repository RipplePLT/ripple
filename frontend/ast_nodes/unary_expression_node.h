#ifndef INCLUDED_UNARY_EXPRESSION_NODE
#define INCLUDED_UNARY_EXPRESSION_NODE

#ifndef INCLUDED_AST_NODE
#include "ast_node.h"
#endif

#ifndef INCLDED_VALUE_NODE
#include "value_node.h"
#endif

namespace Ripple {
namespace AST {

// Foreward declaration of class
class UnaryExpressionNode;


enum unary_operator {
	unary_op_none = 0,
	unary_op_minus = 1,
	unary_op_size_of = 2,
	unary_op_not = 3
};

namespace {
	union unary_expression {
		ValueNode *value_node;
		UnaryExpressionNode *unary_expression_node;
	};
}

class UnaryExpressionNode : public ASTNode {
private:
	unary_expression d_expression;
	unary_operator d_operator;
	void type_check();

public:
	UnaryExpressionNode(Ripple::AST::ValueNode *_value_node);
	UnaryExpressionNode(Ripple::AST::unary_operator _operator, Ripple::AST::UnaryExpressionNode *_unary_expression_node);
	
};

}
}

#endif