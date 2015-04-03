#include <list>

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
        list<ValNode> children;
    public:
        ValNode(T val, V& func, list<Variant> args);
        void addNode();
        T getVal();
        list<ValNode> getChildren();
        ValNode getChild(T val);
        void setVal(T val);
        void setLeft(ValNode &left);
        void setRight(ValNode &right);
        ~ValNode();
};
