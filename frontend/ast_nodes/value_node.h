#ifndef INCLUDED_VALUE_NODE
#define INCLUDED_VALUE_NODE

#ifndef INCLUDED_AST_NODE
#include "ast_node.h"
#endif

#ifndef INCLDED_LITERAL_NODE
#include "literal_node.h"
#endif

namespace Ripple {
namespace AST {

namespace {
	union value_type {
		LiteralNode *literal_node;
	};
}

namespace {
	enum selection {
		literal_node = 0
	};
}

class ValueNode : public ASTNode {
private:
	value_type d_value;

public:
	ValueNode(Ripple::AST::LiteralNode *_literal_node);
	
};

}
}

#endif