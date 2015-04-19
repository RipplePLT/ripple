#ifndef __LINKEDVAR_HPP__
#define __LINKEDVAR_HPP__

#include "../frontend/ast.h"

//template<typename T>
class LinkedVar {
    private:
        int value;
        ExpressionNode expression; // Linked expression
        //list<LinkedVar&> references; // LinkedVars to update
    public:
        LinkedVar(int *var, ExpressionNode exp);
        ~LinkedVar();
        //T get_value();
		int get_value();
        //T update_value();
        int update_value();
};

#endif
