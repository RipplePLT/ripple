#include <iostream>

#include "../linked_var.h"
#include "../expression_tree.h"
#include "../sync_queue.h"

/*
 * This test is an example of the intermediate code that link
 * statements will compile to.
 */
int main()
{
    /*
     * Everything is allocated on the heap, since all threads need
     * access to this data.
     */

	// === Assignment ===
	//		int root = 5;
    cout << "int root = 5;" << endl;
    int root = 5;
	linked_var::register_cpp_var(&root);

    /* === Link Statement ===
     * 		link (int x <- root);
     */
    cout << "link (int x <- root);" << endl;
	int x;
	linked_var::register_cpp_var(&x);
    VariableNode *l = new VariableNode (&root);
    ValueNode *v = new ValueNode (l);
    UnaryExpressionNode *u = new UnaryExpressionNode (v);
    BinaryExpressionNode *b_x = new BinaryExpressionNode (u);
    ExpressionNode *e_x = new ExpressionNode (b_x);
    linked_var *var_x = new linked_var (&x, e_x);
    /* === End of code for link (x <- root) === */

    /* === Link Statement ===
     * 		link (int y <- x + 2)
     */
    cout << "link (int y <- x + 2);" << endl;
	int y;
	linked_var::register_cpp_var(&y);
    VariableNode *l1 = new VariableNode (&x);
    ValueNode *v1 = new ValueNode (l1);
    LiteralNode *l2 = new LiteralNode (2);
    ValueNode *v2 = new ValueNode (l2);
    UnaryExpressionNode *u1 = new UnaryExpressionNode (v1);
    UnaryExpressionNode *u2 = new UnaryExpressionNode (v2);
    BinaryExpressionNode *b1 = new BinaryExpressionNode (u1);
    BinaryExpressionNode *b2 = new BinaryExpressionNode (u2);
    BinaryExpressionNode *b_y = new BinaryExpressionNode (b1, "+", b2);
    ExpressionNode *e_y = new ExpressionNode (b_y);
    linked_var *var_y = new linked_var (&y, e_y);
    /* === End of code for "link (y <- x + 2)" === */

    cout << "\tx == " << *(int *)var_x->get_value().value.ptr << endl;
    cout << "\ty == " << var_y->get_value().value.intval << endl;

    /*
     * === Assignment ===
     * 		root = 6;
     */
    cout << "root = 6;" << endl;
    root = 6;
	linked_var::update_nonlinked_var(&root);
    /* === End of code for "root = 6" === */

    cout << "\tx == " << *(int *)var_x->get_value().value.ptr << endl;
    cout << "\ty == " << var_y->get_value().value.intval << endl;

    return 0;
}
