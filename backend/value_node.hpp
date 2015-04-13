#ifndef VALUE_NODE_HPP
#define VALUE_NODE_HPP

#include <list>

/**
 * value_node.hpp - Templated value node to create the dependency tree.
 *
 * Author: Alexander Roth
 **/
using namespace std;

// TODO: Look into using variadic templates for the argument.

template<typename T, typename Val, typename Aux>
class value_node {
    private:
        T value;
        Val& update_func;
        Aux& aux_func;
        list<value_node> children;
    public:
        value_node(T val, Val update, Aux aux);
        ~value_node();
        void add_child(value_node<T, Val, Aux> &node);
        void run();

        T get_value();
        list<value_node> get_children();

        void set_value(T val);
        void set_children(list<value_node> children);
};

template<typename T, typename Val, typename Aux>
value_node<T, Val, Aux>::value_node(T val, Val func, Aux aux) 
    : update_func(func), aux_func(aux) {
        this->value = val;
    }

template<typename T, typename Val, typename Aux>
value_node<T, Val, Aux>::~value_node() {
    this->value = 0;
    this->children.clear();
}

template<typename T, typename Val, typename Aux>
void value_node<T, Val, Aux>::add_child(value_node &node) {
    this->children.push_back(node);
}

template<typename T, typename Val, typename Aux>
void value_node<T, Val, Aux>::run() {
    auto temp = this->value;
    this->value = this->update_func(temp);
    this->aux_func(this->value);
}

template<typename T, typename Val, typename Aux>
T value_node<T, Val, Aux>::get_value() {
    return this->value;
}

template<typename T, typename Val, typename Aux>
list<typename value_node<T,Val, Aux>::value_node> value_node<T, Val, Aux>::get_children() {
    return this->children;
}

template<typename T, typename Val, typename Aux>
void value_node<T, Val, Aux>::set_value(T val) {
    this->value = val;
}

template<typename T, typename Val, typename Aux>
void value_node<T, Val, Aux>::set_children(list<value_node> children) {
    this->children = children;
}

#endif
