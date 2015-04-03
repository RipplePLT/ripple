#include "ValNode.hpp"

using namespace std;

template<T, V>
ValNode::ValNode(T val, V& func, list<Variant> args) {
    val = val;
    args = args;
}

void ValNode::addLeft(ValNode &node) {
    this->left = node;
}

void ValNode::addRight(ValNode &node) {
    this->right = node;
}

template<T>
T ValNode::getVal() {
    return this->value;
}

ValNode ValNode::getLeft() {
    return this->left;
}

ValNode ValNode::getRight() {
    return this->right;
}

void ValNode::setVal(T val) {
    this->value = val;
}

void ValNode::setLeft(ValNode &left) {
    this->left = left;
}

void ValNode::setRight(ValNode &right) {
    this->right = right;
}

ValNode::~ValNode() {
    this->value = NULL;
    this->function = nullptr;
    this->arguments = NULL;
    this->left = NULL;
    this->right = NULL;
}
