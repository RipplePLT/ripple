#include "variable.hpp"

template<typename T>
Variable<T>::Variable(T *var, ExpressionNode exp) {
}

template<typename T>
T Variable<T>::get_value() {
    return this.value;
}

template<typename T>
T Variable<T>::update_value() {
}
