#include <cstring>
using namespace std;

union literal {
    int int_lit;
    double float_lit;
    string string_lit;
    bool bool_lit;
    char byte_lit;

    literal() { memset(this, 0, sizeof(literal)); }
    ~literal() {}
};
