#include <iostream>
#include <cmath>
#include <assert.h>
#include "../expression_tree.hpp"
#include "../link_val.hpp"
#include "../linked_var.hpp"

/* Spaghetti */

class TreeTest {
    public:
        static VariableNode *create_var_node(int *i);
        static VariableNode *create_var_node(double *d);
        static LiteralNode *create_literal_node(int i);
        static LiteralNode *create_literal_node(double d);
        static linked_var *link_int_var(int *i);
        static linked_var *link_double_var(double *d);
        static linked_var *link_bool_lit_op_bool_var
            (void *linked, bool b, bool *d, const char *op);
        static linked_var *link_int_lit_op_double_var
            (void *linked, int i, double *d, const char *op);
        static void run_all_unit_tests();
        static void run_all_integration_tests();
};

VariableNode *TreeTest::create_var_node(int *i) {
    // Code
    VariableNode *v = new VariableNode (i);

    // Test
    assert(v->val.type == ltINT_PTR);
    assert(v->val.value.ptr == (void *)i);
    assert(v->var == i);
    assert(v->dependencies->size() == 1);
    assert((*v->dependencies)[0] == i);

    return v;
}

VariableNode *TreeTest::create_var_node(double *d) {
    // Code
    VariableNode *v = new VariableNode (d);

    // Test
    assert(v->val.type == ltDOUBLE_PTR);
    assert(v->val.value.ptr == (void *)d);
    assert(v->var == d);
    assert(v->dependencies->size() == 1);
    assert((*v->dependencies)[0] == d);

    return v;
}

LiteralNode *TreeTest::create_literal_node(int i) {
    LiteralNode *l = new LiteralNode(i);

    assert(l->val.type == ltINT);
    assert(l->val.value.intval == i);

    return l;
}

LiteralNode *TreeTest::create_literal_node(double d) {
    LiteralNode *l = new LiteralNode(d);

    assert(l->val.type == ltDOUBLE);
    assert(l->val.value.doubleval == d);

    return l;
}

void TreeTest::run_all_unit_tests() {
    int a = 5;
    int b = 0;
    double c = 5.5;
    double d = 5;
    double e = 0;

    /* VariableNode */
    create_var_node(&a);
    create_var_node(&b);
    create_var_node(&c);
    create_var_node(&d);
    create_var_node(&e);

    /* LiteralNode */
    create_literal_node(a);
    create_literal_node(b);
    create_literal_node(c);
    create_literal_node(d);
    create_literal_node(e);
}

/* Link to one integer variable */
linked_var *TreeTest::link_int_var(int *i) {
    // Code
    VariableNode *v = new VariableNode (i);

    // Test
    assert(v->val.type == ltINT_PTR);
    assert(v->val.value.ptr == (void *)i);
    assert(v->var == i);
    assert(v->dependencies->size() == 1);
    assert((*v->dependencies)[0] == i);

    // Code
    linked_var::references[i] = new vector<linked_var*>();
    ValueNode *valNode = new ValueNode (v);

    // Test
    assert(valNode->is_literal == false);
    assert(valNode->var_node == v);
    assert(valNode->dependencies->size() == 1);
    assert((*valNode->dependencies)[0] == i);
    assert(v->evaluate().value.ptr == i);
    assert(v->evaluate().type == ltINT_PTR);

    // Code
    UnaryExpressionNode *u = new UnaryExpressionNode (valNode);

    // Test
    assert(u->op == NONE);
    assert(u->right_operand.v_node == valNode);
    assert(u->dependencies == valNode->dependencies);
    assert(u->evaluate().value.ptr == i);
    assert(u->evaluate().type == ltINT_PTR);

    // Code
    BinaryExpressionNode *b_x = new BinaryExpressionNode (u);
    assert(b_x->left_operand.u_exp == u);
    assert(b_x->op == NONE);
    assert(b_x->dependencies == u->dependencies);
    assert(b_x->evaluate().value.ptr == i);
    assert(b_x->evaluate().type == ltINT_PTR);

    // Code
    ExpressionNode *e_x = new ExpressionNode (b_x);

    // Test
    assert(e_x->bin_exp == b_x);
    assert(e_x->value == NULL);
    assert(e_x->dependencies == b_x->dependencies);
    assert(e_x->evaluate().value.ptr == i);
    assert(e_x->evaluate().type == ltINT_PTR);

    // Code
    linked_var *var_x = new linked_var (i, e_x);
    assert(var_x->get_value().value.ptr == i);
    assert(var_x->get_value().type == ltINT_PTR);

    return var_x;
}

/* Link to one double variable */
linked_var *TreeTest::link_double_var(double *d) {
    // Code
    VariableNode *v = new VariableNode (d);

    // Test
    assert(v->val.type == ltDOUBLE_PTR);
    assert(v->val.value.ptr == (void *)d);
    assert(v->var == d);
    assert(v->dependencies->size() == 1);
    assert((*v->dependencies)[0] == d);

    // Code
    linked_var::references[d] = new vector<linked_var*>();
    ValueNode *valNode = new ValueNode (v);

    // Test
    assert(valNode->is_literal == false);
    assert(valNode->var_node == v);
    assert(valNode->dependencies->size() == 1);
    assert((*valNode->dependencies)[0] == d);
    assert(v->evaluate().value.ptr == d);
    assert(v->evaluate().type == ltDOUBLE_PTR);

    // Code
    UnaryExpressionNode *u = new UnaryExpressionNode (valNode);

    // Test
    assert(u->op == NONE);
    assert(u->right_operand.v_node == valNode);
    assert(u->dependencies == valNode->dependencies);
    assert(u->evaluate().value.ptr == d);
    assert(u->evaluate().type == ltDOUBLE_PTR);

    // Code
    BinaryExpressionNode *b_x = new BinaryExpressionNode (u);
    assert(b_x->left_operand.u_exp == u);
    assert(b_x->op == NONE);
    assert(b_x->dependencies == u->dependencies);
    assert(b_x->evaluate().value.ptr == d);
    assert(b_x->evaluate().type == ltDOUBLE_PTR);

    // Code
    ExpressionNode *e_x = new ExpressionNode (b_x);

    // Test
    assert(e_x->bin_exp == b_x);
    assert(e_x->value == NULL);
    assert(e_x->dependencies == b_x->dependencies);
    assert(e_x->evaluate().value.ptr == d);
    assert(e_x->evaluate().type == ltDOUBLE_PTR);

    // Code
    linked_var *var_x = new linked_var (d, e_x);
    assert(var_x->get_value().value.ptr == d);
    assert(var_x->get_value().type == ltDOUBLE_PTR);

    return var_x;
}

/* @TODO int literal, double literal */
/* @TODO Link to int (op) int */
/* @TODO Link to double (op) double */

/* Link to int literal (op) double var */
linked_var *TreeTest::link_int_lit_op_double_var(void *linked, int i,
        double *d, const char *op) {
    // Determine target value
    double target;
    if (!strcmp(op, "+"))
        target = i + *d;
    else if (!strcmp(op, "-"))
        target = i - *d;
    else if (!strcmp(op, "*"))
        target = i * *d;
    else if (!strcmp(op, "/"))
        target = i / *d;
    else if (!strcmp(op, "^"))
        target = pow(i, *d);
    else
        target = 0;

    // Left operand
    LiteralNode *l1 = new LiteralNode(i);
    ValueNode *v1 = new ValueNode(l1);
    UnaryExpressionNode *u1 = new UnaryExpressionNode(v1);
    BinaryExpressionNode *b1 = new BinaryExpressionNode(u1);
    assert(b1->evaluate().value.intval == i);
    assert(b1->evaluate().type == ltINT);

    // Right operand
    VariableNode *l2 = new VariableNode(d);
    ValueNode *v2 = new ValueNode (l2);
    UnaryExpressionNode *u2 = new UnaryExpressionNode(v2);
    BinaryExpressionNode *b2 = new BinaryExpressionNode(u2);
    assert(b2->evaluate().value.ptr == d);
    assert(b2->evaluate().type == ltDOUBLE_PTR);

    // Operation
    BinaryExpressionNode *bin = new BinaryExpressionNode (b1, op, b2);
    if (link_val::is_bool_op(op)) {
        assert(bin->evaluate().type == ltBOOL);
    } else {
        assert(bin->evaluate().type == ltDOUBLE);
        assert(bin->evaluate().value.doubleval == target);
    }

    ExpressionNode *exp = new ExpressionNode(bin);
    linked_var *var = new linked_var(linked, exp);

    return var;
}

/* Link to bool literal (op) bool var */
linked_var *TreeTest::link_bool_lit_op_bool_var(void *linked, bool i,
        bool *d, const char *op) {
    // Determine target value
    bool target;
    if (!strcmp(op, "and"))
        target = i && *d;
    else if (!strcmp(op, "or"))
        target = i || *d;
    else
        target = false;

    // Left operand
    LiteralNode *l1 = new LiteralNode(i);
    ValueNode *v1 = new ValueNode(l1);
    UnaryExpressionNode *u1 = new UnaryExpressionNode(v1);
    BinaryExpressionNode *b1 = new BinaryExpressionNode(u1);
    assert(b1->evaluate().value.boolval == i);
    assert(b1->evaluate().type == ltBOOL);

    // Right operand
    VariableNode *l2 = new VariableNode(d);
    ValueNode *v2 = new ValueNode (l2);
    UnaryExpressionNode *u2 = new UnaryExpressionNode(v2);
    BinaryExpressionNode *b2 = new BinaryExpressionNode(u2);
    assert(b2->evaluate().value.ptr == d);
    assert(b2->evaluate().type == ltBOOL_PTR);

    // Operation
    BinaryExpressionNode *bin = new BinaryExpressionNode (b1, op, b2);
    assert(bin->evaluate().type == ltBOOL);
    assert(bin->evaluate().value.boolval == target);

    ExpressionNode *exp = new ExpressionNode(bin);
    linked_var *var = new linked_var(linked, exp);

    return var;
}

void TreeTest::run_all_integration_tests() {
    int a = 5;
    link_int_var(&a);

    double b = 2.5;
    link_double_var(&b);

    double z;
    linked_var *z_link;
    z_link = link_int_lit_op_double_var(&z, a, &b, "+");
    assert(z_link->get_value().type == ltDOUBLE);
    assert(z_link->get_value().value.doubleval == 7.5);

    z_link = link_int_lit_op_double_var(&z, a, &b, "-");
    assert(z_link->get_value().value.doubleval == 2.5);

    z_link = link_int_lit_op_double_var(&z, a, &b, "*");
    assert(z_link->get_value().value.doubleval == 12.5);

    z_link = link_int_lit_op_double_var(&z, a, &b, "/");
    assert(z_link->get_value().value.doubleval == 2);

    bool q;
    z_link = link_int_lit_op_double_var(&q, a, &b, ">");
    assert(z_link->get_value().value.boolval == true);
    z_link = link_int_lit_op_double_var(&q, a, &b, ">=");
    assert(z_link->get_value().value.boolval == true);

    z_link = link_int_lit_op_double_var(&q, a, &b, "<");
    assert(z_link->get_value().value.boolval == false);
    z_link = link_int_lit_op_double_var(&q, a, &b, "<=");
    assert(z_link->get_value().value.boolval == false);

    b = 5;
    z_link = link_int_lit_op_double_var(&q, a, &b, ">=");
    assert(z_link->get_value().value.boolval == true);
    z_link = link_int_lit_op_double_var(&q, a, &b, "<=");
    assert(z_link->get_value().value.boolval == true);
    z_link = link_int_lit_op_double_var(&q, a, &b, "==");
    assert(z_link->get_value().value.boolval == true);
    z_link = link_int_lit_op_double_var(&q, a, &b, "!=");
    assert(z_link->get_value().value.boolval == false);

    a = 5, b = 2;
    z_link = link_int_lit_op_double_var(&z, a, &b, "^");
    assert(z_link->get_value().value.doubleval == 25);

    bool r = true;
    linked_var *r_link;
    linked_var::references[&r] = new vector<linked_var*>();
    r_link = link_bool_lit_op_bool_var(&r, (3 > 2), &r, "and");
    assert(r_link->get_value().value.boolval == true);
    r_link = link_bool_lit_op_bool_var(&r, (2 > 2), &r, "and");
    assert(r_link->get_value().value.boolval == false);
    r = false;
    r_link = link_bool_lit_op_bool_var(&r, (3 > 2), &r, "or");
    assert(r_link->get_value().value.boolval == true);
    r_link = link_bool_lit_op_bool_var(&r, (2 > 2), &r, "or");
    assert(r_link->get_value().value.boolval == false);
}

int main() {
    TreeTest::run_all_unit_tests();
    TreeTest::run_all_integration_tests();

    cerr << "All tests passed." << endl;
}
