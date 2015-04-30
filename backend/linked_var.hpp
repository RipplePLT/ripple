#ifndef __LINKED_VAR_HPP__
#define __LINKED_VAR_HPP__

#include <vector>
#include <unordered_map>
#include "expression_tree.hpp"

/*
 * The linked_var class represents a single linked variable.
 */
class linked_var {
    private:
        struct link_val value; // Current value
        void *address; // Address of corresponding C++ variable
        ExpressionNode expression; // Linked expression
    public:
		// Hash map from a memory address to a list of linked_vars
		//   which depend on that memory address.
        static unordered_map<void *, vector<linked_var *>> references;

        linked_var(int *var, ExpressionNode *exp); // Ctor
        struct link_val get_value();
        void update(struct link_val new_value); // Assignment
        void update(); // For testing only
};

#endif
