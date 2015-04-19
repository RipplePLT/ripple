#include <stdio.h>
#include "linkedvar.hpp"
#include "../frontend/ast.h"

int main()
{
    // Build ExpressionNode for (1 + 2)
    LiteralNode l1 (1);
    LiteralNode l2 (2);
    ValueNode v1 (&l1);
    ValueNode v2 (&l2);
    UnaryExpressionNode u1 (&v1);
    UnaryExpressionNode u2 (&v2);
    BinaryExpressionNode b1 (&u1);
    BinaryExpressionNode b2 (&u2);
    BinaryExpressionNode b (&b1, "+", &b2);
    ExpressionNode e (&b);

    // Create Variable
    int x = 5;
    // LinkedVar<int> var_x (&x, e);
    LinkedVar var_x (&x, e);

    return 0;
}
