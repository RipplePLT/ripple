#include <string>
#define INT_NODE 1
#define FLOAT_NODE 2
#define STRING_NODE 3
#define BYTE_NODE 4
#define BOOL_NODE 5

class ASTNode {
    public:
        virtual ~ASTNode();
};

class Expression : ASTNode {
    public:
        int op;
};

class OrExpression : Expression {
};

class AndExpression : OrExpression {
};

class EqExpression : AndExpression {
};

class RelExpression : EqExpression {
};

class AddExpression : RelExpression {
};

class MultExpression : AddExpression {
};

class ExpExpression : MultExpression {
};

class UnaryExpression : ExpExpression {
};

class IntNode {
    public:
        long value;
        IntNode(const long v): value(v) { }
};

class FloatNode {
    public:
        double value;
        FloatNode(const double v): value(v) { }
};

class StringNode {
    public:
        std::string value;
        StringNode(const std::string v): value(v) { } 
};

class BoolNode {
    public:
        bool value;
        BoolNode(const bool v): value(v) { }
};

class ByteNode {
    public:
        char value;
        ByteNode(const char v): value(v) { }
};


class ValueNode {
    union types {
        IntNode *Int;
        FloatNode *Float;
        StringNode *String;
        BoolNode *Bool;
        ByteNode *Byte;
    } child;

    public:
    int type;

    // Constructors for different types
    ValueNode(IntNode *i) { child.Int = i; this->type = INT_NODE; }
    ValueNode(FloatNode *f) { child.Float = f; this->type = FLOAT_NODE; }
    ValueNode(StringNode *s) { child.String = s; this->type = STRING_NODE; }
    ValueNode(BoolNode *b) { child.Bool = b; this->type = BOOL_NODE; }
    ValueNode(ByteNode *b) { child.Byte = b;  this->type = BYTE_NODE; }
};
