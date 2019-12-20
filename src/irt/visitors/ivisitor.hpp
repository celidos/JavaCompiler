#pragma once

namespace irt {

class ExpressionLoadConst;
class ExpressionBinaryOp;
class ExpressionName;
class ExpressionTemp;
class ExpressionMem;
class ExpressionCall;
class ExpressionSeq;
class ExpressionArg;
class ExpressionLocal;
class StatementMove;
class StatementExp;
class StatementJump;
class StatementCJump;
class StatementSeq;
class StatementLabel;
class StatementNan;

class ExpressionList;

class IVisitor {
public:
    virtual ~IVisitor() {}

    virtual void visit(const ExpressionLoadConst *expr) = 0;
    virtual void visit(const ExpressionBinaryOp *expr) = 0;
    virtual void visit(const ExpressionName* expr) = 0;
    virtual void visit(const ExpressionTemp* expr) = 0;
    virtual void visit(const ExpressionMem* expr) = 0;
    virtual void visit(const ExpressionCall* expr) = 0;
    virtual void visit(const ExpressionSeq* expr) = 0;
    virtual void visit(const ExpressionArg* expr) = 0;
    virtual void visit(const ExpressionLocal* expr) = 0;
    virtual void visit(const StatementMove* statement) = 0;
    virtual void visit(const StatementExp* statement) = 0;
    virtual void visit(const StatementJump* statement) = 0;
    virtual void visit(const StatementCJump* statement) = 0;
    virtual void visit(const StatementSeq* statement) = 0;
    virtual void visit(const StatementLabel* statement) = 0;
    virtual void visit(const StatementNan* statement) = 0;

    virtual void visit(const ExpressionList* expr) = 0;
};

} // namespace irt