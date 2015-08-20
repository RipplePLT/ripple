#ifndef INCLUDED_VALUE_NODE
#include "value_node.h"
#endif

namespace Ripple {
namespace AST {

ValueNode::ValueNode(Ripple::AST::LiteralNode *_literal_node){
	d_value.literal_node = _literal_node;

	base_type = _literal_node->base_type;
	derived_type = t_none;

	code = _literal_node->code;
#ifdef DEBUG
	std::cout << base_type << " " << code << std::endl;
#endif
}

}
}