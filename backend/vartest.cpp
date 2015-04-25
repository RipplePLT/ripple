#include <stdio.h>
#include "linkedvar.hpp"
#include "variable_tree.hpp"

int main()
{
    int x, y;

	// Build RHS ExpressionNode for x = 5
	ValueNode v (5);
	UnaryExpressionNode u (&v);
	BinaryExpressionNode b_x (&u);
	ExpressionNode e_x (&b_x);

    // Build RHS ExpressionNode for y = x + 2
    ValueNode v1 (&x);
    ValueNode v2 (2);
    UnaryExpressionNode u1 (&v1);
    UnaryExpressionNode u2 (&v2);
    BinaryExpressionNode b1 (&u1);
    BinaryExpressionNode b2 (&u2);
    BinaryExpressionNode b_y (&b1, "+", &b2);
    ExpressionNode e_y (&b_y);

    LinkedVar var_x (&x, e_x);
	LinkedVar var_y (&y, e_y);

	var_x.add_reference(&var_y);

	fprintf(stderr, "x = %d\n", var_x.get_value());
	fprintf(stderr, "y = %d\n", var_y.get_value());

    return 0;
}
