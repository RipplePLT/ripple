class ASTNode {
    public:
        virtual ~ASTNode();
};

class ExpressionNode : ASTNode {
};

class IntNode : ExpressionNode {
    public:
        long value;
        IntNode(const long v): value(v) { }
};

class FloatNode : ExpressionNode {
    public:
        double value;
        FloatNode(const double v): value(v) { }
};

class StringNode : ExpressionNode {
    public:
        std::string value;
        StringNode(const std::string v): value(v) { } 
};
