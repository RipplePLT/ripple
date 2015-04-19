#ifndef __LINKEDVAR_HPP__
#define __LINKEDVAR_HPP__

#include "../frontend/ast.h"

/*
 * The LinkedVar class represents a single linked variable.
 * For now it supports only integer values.
 * But it will be templatized in due time.
 */

//template<typename T>
class LinkedVar {
    private:
        int value;
        ExpressionNode expression; // Linked expression
        list<LinkedVar*> references; // LinkedVars to update
    public:
        LinkedVar(int *var, ExpressionNode exp);
        //T get_value();
		int get_value();
        //T update_value();
        int update_value();
		void add_reference(LinkedVar *var);
};

#endif
