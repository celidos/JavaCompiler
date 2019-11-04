#pragma once

#include <iostream>
#include <string>
#include <memory>

namespace ast {

class ExpressionInt;
class ExpressionBinaryOp;
class ExpressionLogical;
class ExpressionId;
class ExpressionSquareBracket;
class ExpressionLen;
class ExpressionUnaryNegation;
class ExpressionThis;
class StatementAssign;
typedef std::shared_ptr<ExpressionInt> PExpressionInt;
typedef std::shared_ptr<ExpressionBinaryOp> PExpressionBinaryOp;
typedef std::shared_ptr<ExpressionLogical> PExpressionLogical;
typedef std::shared_ptr<ExpressionId> PExpressionId;
typedef std::shared_ptr<ExpressionSquareBracket> PExpressionSquareBracket;
typedef std::shared_ptr<ExpressionLen> PExpressionLen;
typedef std::shared_ptr<ExpressionUnaryNegation> PExpressionUnaryNegation;
typedef std::shared_ptr<ExpressionThis> PExpressionThis;
typedef std::shared_ptr<StatementAssign> PStatementAssign;

class IVisitor {
public:
    virtual ~IVisitor() = default;

    virtual void visit(const ExpressionInt* expr) = 0;
    virtual void visit(const ExpressionBinaryOp* expr) = 0;
    virtual void visit(const ExpressionLogical* expr) = 0;
    virtual void visit(const ExpressionId* expr) = 0;
    virtual void visit(const ExpressionSquareBracket* expr) = 0;
    virtual void visit(const ExpressionLen* expr) = 0;
    virtual void visit(const ExpressionUnaryNegation* expr) = 0;
    virtual void visit(const ExpressionThis* expr) = 0;
    virtual void visit(const StatementAssign* statement) = 0;
};

}

