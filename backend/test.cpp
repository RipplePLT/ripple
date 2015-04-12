#include <stdio.h>
#include "value_node.hpp"

int update_root(int n)
{
    fprintf(stderr, "root updated! arg = {%d}\n", n);
    return 0;
}

int main()
{
    // Create argument
    variant arg;
    arg.type = variant::t_int;
    arg.data.int_val = 7;

    // Add argument to list
    list<variant> args;
    args.push_back(arg);

    // Construct node
    //value_node<int, int (&)(int)> root (3, update_root, args);
}
