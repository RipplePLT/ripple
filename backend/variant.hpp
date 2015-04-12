#ifndef VARIANT_HPP
#define VARIANT_HPP

/**
 * variant.hpp -
 *
 * Author: Alexander Roth
 * Date:   2015-04-09
 */

struct variant {
    enum variant_type {
        t_string,
        t_int,
        t_bool,
        t_byte,
        t_float
    } type;

    union variant_data {
        char* str_val;
        int int_val;
        bool bool_val;
        int byte_val;
        float float_val;
    } data;
};

#endif
