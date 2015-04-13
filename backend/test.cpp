#include <stdio.h>
#include "value_node.hpp"

void null(int val) {}

int plus7(int val) {
    return val + 7;
}

int update_value(int n)
{
    fprintf(stderr, "root updated! arg = {%d}\n", n);
    return 0;
}

int main()
{
    // Construct node
    //value_node<int, void (&)(int), int (&)(int)> void_root(3, null, update_value);
    //void_root.run();

    value_node<int, int (&)(int), int(&)(int)> int_root(3, plus7, update_value);
    int_root.run();
}
