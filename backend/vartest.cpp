#include <stdio.h>
#include "../frontend/ast.h"

int main()
{
    LiteralNode l1 = new LiteralNode(1);
    LiteralNode l2 = new LiteralNode(2);

    ValueNode v1 = new ValueNode(l1);
    ValueNode v2 = new ValueNode(l2);

    UnaryExpressionNode u1 = new UnaryExpressionNode(v1);
    UnaryExpressionNode u2 = new UnaryExpressionNode(v2);

    BinaryExpressionNode b1 = new BinaryExpressionNode(u1);
    BinaryExpressionNode b2 = new BinaryExpressionNode(u2);

    BinaryExpressionNode b = new BinaryExpressionNode(b1, "+", b2);
    ExpressionNode e = new ExpressionNode(b);

    return 0;
}
