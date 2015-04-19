#include <stdio.h>
#include "linkedvar.hpp"
#include "../frontend/symbol_table/hashmap.h"
#include "../frontend/ast.h"

int main()
{
	// Build Expression node for x = 5
	LiteralNode l (5);
	ValueNode v (&l);
	UnaryExpressionNode u (&v);
	BinaryExpressionNode b_x (&u);
	ExpressionNode e_x (&b_x);

    // Build ExpressionNode for y = x + 2
	Entry y_entry ("x", tINT, 0);
	IDNode i (&y_entry);
    LiteralNode l2 (2);
    ValueNode v1 (&i);
    ValueNode v2 (&l2);
    UnaryExpressionNode u1 (&v1);
    UnaryExpressionNode u2 (&v2);
    BinaryExpressionNode b1 (&u1);
    BinaryExpressionNode b2 (&u2);
    BinaryExpressionNode b_y (&b1, "+", &b2);
    ExpressionNode e_y (&b_y);

    // Create Variable
    int x, y;
    // LinkedVar<int> var_x (&x, e);
    LinkedVar var_x (&x, e_x);
	LinkedVar var_y (&y, e_y);

	var_x.add_reference(&var_y);

    return 0;
}
