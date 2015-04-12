#ifndef VALUE_NODE_HPP
#define VALUE_NODE_HPP

#include <list>

#include "variant.hpp"

/**
 * value_node.hpp - Templated value node to create the dependency tree.
 *
 * Author: Alexander Roth
 * Date:   2015-04-02
 **/
using namespace std;

template<typename T, typename V>
class value_node {
    private:
        T value;
        V& function;
        list<variant> arguments {nullptr};
        list<value_node> children {nullptr};
    public:
        value_node(T val, V& func, list<variant> args);
        ~value_node();
        void add_child(value_node<T, V> &node);

        T get_value();
        list<value_node> get_children();
        list<variant> get_arguments();

        void set_value(T val);
        void set_children(list<value_node> children);
        void set_arguments(list<variant> arguments);
};

template<typename T, typename V>
value_node<T, V>::value_node(T val, V& func, list<variant> args) {
    this->value = val;
    this->function = func;
    this->arguments = args;
}

template<typename T, typename V>
value_node<T, V>::~value_node() {
    this->value = nullptr;
    this->function = nullptr;
    this->arguments = nullptr;
    this->children = nullptr;
}

template<typename T, typename V>
void value_node<T, V>::add_child(value_node &node) {
    this->children.push_back(node);
}

template<typename T, typename V>
T value_node<T, V>::get_value() {
    return this->value;
}

template<typename T, typename V>
list<typename value_node<T,V>::value_node> value_node<T, V>::get_children() {
    return this->children;
}

template<typename T, typename V>
list<variant> value_node<T, V>::get_arguments() {
    return this->arguments;
}

template<typename T, typename V>
void value_node<T, V>::set_value(T val) {
    this->value = val;
}

template<typename T, typename V>
void value_node<T, V>::set_children(list<value_node> children) {
    this->children = children;
}

template<typename T, typename V>
void value_node<T, V>::set_arguments(list<variant> arguments) {
    this->arguments = arguments;
}

#endif
