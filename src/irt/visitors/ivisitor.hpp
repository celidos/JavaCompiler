#pragma once

namespace irt {

class ExpressionLoadConst;
class ExpressionBinaryOp;

class IVisitor {
public:
    virtual ~IVisitor() {}

    virtual void visit(const ExpressionLoadConst *expression) = 0;
    virtual void visit(const ExpressionBinaryOp *expression) = 0;

    // TODO - FILL IN. Note: list of classes differs from the one in ast/visitors/ivisitor
};

} // namespace irt