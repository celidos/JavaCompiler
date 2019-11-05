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
class TypeInt;
class VarDeclaration;
class MethodBody;
class MethodDeclaration;
class MainClass;
class Goal;
typedef std::shared_ptr<ExpressionInt> PExpressionInt;
typedef std::shared_ptr<ExpressionBinaryOp> PExpressionBinaryOp;
typedef std::shared_ptr<ExpressionLogical> PExpressionLogical;
typedef std::shared_ptr<ExpressionId> PExpressionId;
typedef std::shared_ptr<ExpressionSquareBracket> PExpressionSquareBracket;
typedef std::shared_ptr<ExpressionLen> PExpressionLen;
typedef std::shared_ptr<ExpressionUnaryNegation> PExpressionUnaryNegation;
typedef std::shared_ptr<ExpressionThis> PExpressionThis;
typedef std::shared_ptr<StatementAssign> PStatementAssign;
typedef std::shared_ptr<TypeInt> PTypeInt;
typedef std::shared_ptr<VarDeclaration> PVarDeclaration;
typedef std::shared_ptr<MethodBody> PMethodBody;
typedef std::shared_ptr<MethodDeclaration> PMethodDeclaration;
typedef std::shared_ptr<MainClass> PMainClass;
typedef std::shared_ptr<Goal> PGoal;
class IVisitor {
public:
    virtual ~IVisitor() = default;

    virtual void visit(const ExpressionInt* expr, bool need_new_line = true) = 0;
    virtual void visit(const ExpressionBinaryOp* expr, bool need_new_line = true) = 0;
    virtual void visit(const ExpressionLogical* expr, bool need_new_line = true) = 0;
    virtual void visit(const ExpressionId* expr, bool need_new_line = true) = 0;
    virtual void visit(const ExpressionSquareBracket* expr, bool need_new_line = true) = 0;
    virtual void visit(const ExpressionLen* expr, bool need_new_line = true) = 0;
    virtual void visit(const ExpressionUnaryNegation* expr, bool need_new_line = true) = 0;
    virtual void visit(const ExpressionThis* expr, bool need_new_line = true) = 0;
    virtual void visit(const StatementAssign* statement, bool need_new_line = true) = 0;
    virtual void visit(const TypeInt* type, bool need_new_line = true) = 0;
    virtual void visit(const VarDeclaration* var_declaration, bool need_new_line = true) = 0;
    virtual void visit(const MethodBody* method_body, bool need_new_line = true) = 0;
    virtual void visit(const MethodDeclaration* method_declaration, bool need_new_line = true) = 0;
    virtual void visit(const MainClass* main_class, bool need_new_line = true) = 0;
    virtual void visit(const Goal* goal, bool need_new_line = true) = 0;
};

}

