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
class TypeBoolean;
class TypeArray;
class TypeClass;
class VarDeclaration;
class MethodBody;
class MethodDeclaration;
class Class;
class MainClass;
class Goal;
class ExpressionNewId;
class ExpressionNewIntArray;
class ExpressionCallFunction;
class Statements;
class StatementIf;
class StatementWhile;
class StatementPrint;
class StatementArrayAssign;

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
typedef std::shared_ptr<TypeBoolean> PTypeBoolean;
typedef std::shared_ptr<TypeArray> PTypeArray;
typedef std::shared_ptr<TypeClass> PTypeClass;
typedef std::shared_ptr<VarDeclaration> PVarDeclaration;
typedef std::shared_ptr<MethodBody> PMethodBody;
typedef std::shared_ptr<MethodDeclaration> PMethodDeclaration;
typedef std::shared_ptr<Class> PClass;
typedef std::shared_ptr<MainClass> PMainClass;
typedef std::shared_ptr<Goal> PGoal;
typedef std::shared_ptr<ExpressionNewId> PExpressionNewId;
typedef std::shared_ptr<ExpressionNewIntArray> PExpressionNewIntArray;
typedef std::shared_ptr<ExpressionCallFunction> PExpressionCallFunction;
typedef std::shared_ptr<StatementArrayAssign> PStatementArrayAssign;
typedef std::shared_ptr<StatementPrint> PStatementPrint;
typedef std::shared_ptr<StatementWhile> PStatementWhile;
typedef std::shared_ptr<StatementIf> PStatementIf;
typedef std::shared_ptr<Statements> PStatements;

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
    virtual void visit(const TypeInt* type) = 0;
    virtual void visit(const TypeBoolean* type) = 0;
    virtual void visit(const TypeArray* type) = 0;
    virtual void visit(const TypeClass* type) = 0;
    virtual void visit(const VarDeclaration* var_declaration) = 0;
    virtual void visit(const MethodBody* method_body) = 0;
    virtual void visit(const MethodDeclaration* method_declaration) = 0;
    virtual void visit(const MainClass* main_class) = 0;
    virtual void visit(const Class* class_var) = 0;
    virtual void visit(const Goal* goal) = 0;
    virtual void visit(const ExpressionNewId* expr) = 0;
    virtual void visit(const ExpressionNewIntArray* expr) = 0;
    virtual void visit(const ExpressionCallFunction* expr) = 0;
    virtual void visit(const StatementArrayAssign* statement) = 0;
    virtual void visit(const StatementPrint* statement) = 0;
    virtual void visit(const StatementWhile* statement) = 0;
    virtual void visit(const StatementIf* statement) = 0;
    virtual void visit(const Statements* statement) = 0;
};

}

