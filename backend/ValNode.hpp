
using namespace std;

typdef struct Variant {
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
    } data;
} Variant;

template<T, V>
class ValNode {
    private:
        T value;
        V& function;
        list<Variant> arguments;
        ValNode left {NULL};
        ValNode right {NULL};
    public:
        ValNode(T val, V& func, list<Variant> args);
        void addLeft();
        void addRight();
        T getVal();
        ValNode getLeft();
        ValNode getRight();
        void setVal(T val);
        void setLeft(ValNode &left);
        void setRight(ValNode &right);
        ~ValNode();
}
