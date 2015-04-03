#include <list>

/**
 * ValNode.hpp - Templated value node to create the dependency tree.
 *
 * Author: Alexander Roth
 * Date:   2015-04-02
 **/
using namespace std;

struct Variant {
    enum VariantType {
        t_string,
        t_int,
        t_bool,
        t_byte,
        t_float
    } type;

    union VariantData {
        char* strVal;
        int intVal;
        bool boolVal;
        int byteVal;
        float floatVal;
    };
};

template<typename T, typename V>
class ValNode {
    private:
        T value;
        V& function;
        list<Variant> arguments;
        list<ValNode> children {nullptr};
    public:
        ValNode(T val, V& func, list<Variant> args);
        ~ValNode();
        void addChildNode(ValNode<T, V> &node);

        T getVal();
        list<ValNode> getChildren();
        list<Variant> getArguments();

        void setVal(T val);
        void setChildren(list<ValNode> children);
        void setArguments(list<Variant> arguments);
};

template<typename T, typename V>
ValNode<T, V>::ValNode(T val, V& func, list<Variant> args) {
    this->value = val;
    this->function = func;
    this->arguments = args;
}

template<typename T, typename V>
ValNode<T, V>::~ValNode() {
    this->value = nullptr;
    this->function = nullptr;
    this->arguments = nullptr;
    this->children = nullptr;
}

template<typename T, typename V>
void ValNode<T, V>::addChildNode(ValNode &node) {
    this->children.push_back(node);
}

template<typename T, typename V>
T ValNode<T, V>::getVal() {
    return this->value;
}

template<typename T, typename V>
list<typename ValNode<T,V>::ValNode> ValNode<T, V>::getChildren() {
    return this->children;
}

template<typename T, typename V>
list<Variant> ValNode<T, V>::getArguments() {
    return this->arguments;
}

template<typename T, typename V>
void ValNode<T, V>::setVal(T val) {
    this->value = val;
}

template<typename T, typename V>
void ValNode<T, V>::setChildren(list<ValNode> children) {
    this->children = children;
}

template<typename T, typename V>
void ValNode<T, V>::setArguments(list<Variant> arguments) {
    this->arguments = arguments;
}
