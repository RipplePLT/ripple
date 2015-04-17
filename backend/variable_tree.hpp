#ifndef __VARIABLE_TREE_HPP__
#define

#include <list>

#include "variable.hpp"

/**
 * variable_tree - A tree data structure that holds a pointer to a variable 
 * object. The tree should call evaluate on a given node, which will go down
 * the tree and evaluate the return expression based  
 **/

class variable_tree {
    private:
        variable& node;
        list<variable&> children;
    public:
        variable_tree();
        ~variable_tree(); 
        void evaluate(variable node, int position);
}

/*
 * Constructuor method
 */
variable_tree::variable_tree() {
}

/* 
 * Destructor method
 */
variable_tree::~variable_tree() {
}

/*
 * Updates a value of a variable node. You are going to have to mess around with
 * this a bit to figure out the best way to implement this. I was considering a 
 * bottom-up tree evaulation method where the first link statement creates the
 * tree, however, that could cause issues, in that each link would need a tree?
 *
 * Think it over
 */
void variable_tree::evaulate(variable node, int position) {

}
#endif
