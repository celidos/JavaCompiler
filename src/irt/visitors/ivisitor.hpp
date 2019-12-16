#pragma once

namespace irt {

class ExpressionLoadConst;
class ExpressionBinaryOp;
class ExpressionName;
class ExpressionCall;
class ExpressionList;
//class ExpressionArg;

class IVisitor {
public:
    virtual ~IVisitor() {}

    virtual void visit(const ExpressionLoadConst *expr) = 0;
    virtual void visit(const ExpressionBinaryOp *expr) = 0;
    virtual void visit(const ExpressionName* expr) = 0;
//    void visit(const ExpressionTemp* expr);
//    void visit(const ExpressionMem* expr);
    virtual void visit(const ExpressionCall* expr) = 0;
//    void visit(const ExpressionEseq* expr);
//    virtual void visit(const ExpressionArg* expr) = 0;
//    virtual void visit(const ExpressionLocal* expr) = 0;
//    void visit(const StatementMove* statement);
//    void visit(const StatementExp* statement);
//    void visit(const StatementJump* statement);
//    void visit(const StatementCJump* statement);
//    void visit(const StatementSeq* statement);
//    void visit(const StatementLabel* statement);

    virtual void visit(const ExpressionList* expr) = 0;

    // TODO - FILL IN. Note: list of classes differs from the one in ast/visitors/ivisitor
};

} // namespace irt