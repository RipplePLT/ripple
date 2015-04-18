#ifndef __VARIABLE_HPP__
#define __VARIABLE_HPP__

#include "../frontend/ast.h"
// @TODO write test var & exp node

template<typename T>
class Variable {
    private:
        T value;
        ExpressionNode expression; // Linked expression
        list<Variable&> references; // Variables to update
    public:
        Variable(T *var, ExpressionNode exp);
        ~Variable();
        T get_value();
        T update_value();
};

#endif
