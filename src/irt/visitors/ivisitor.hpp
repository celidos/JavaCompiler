#pragma once

namespace irt {

class ExpressionLoadConst;
class ExpressionBinaryOp;

class IVisitor {
public:
    virtual ~IVisitor() {}

    virtual void visit(const ExpressionLoadConst *expression) = 0;
    virtual void visit(const ExpressionBinaryOp *expression) = 0;
};

} // namespace irt