#pragma once

#include <iostream>
#include <string>
#include <stack>

#include <src/ast/visitors/ivisitor.hpp>
#include <handlers/expressions.hpp>
#include <handlers/statements.hpp>
#include <handlers/types.hpp>
#include <handlers/var_declaration.hpp>
#include <handlers/method_body.hpp>
#include <handlers/method_declaration.hpp>
#include <handlers/main_class.hpp>
#include <handlers/goal.hpp>
#include <yyltype.hpp>

#include <../symbol_table/symbol_table.hpp>

namespace ast {

class VisitorSymtableBuilder : public IVisitor {
public:
    VisitorSymtableBuilder() = default;
private:
    TableGlobal table_;

    void visit(const ExpressionInt* expr);
    void visit(const ExpressionBinaryOp* expr);
    void visit(const ExpressionLogical* expr);
    void visit(const ExpressionId* expr);
    void visit(const ExpressionSquareBracket* expr);
    void visit(const ExpressionLen* expr);
    void visit(const ExpressionUnaryNegation* expr);
    void visit(const ExpressionThis* expr);
    void visit(const StatementAssign* statement);
    void visit(const TypeInt* type);
    void visit(const VarDeclaration* var_declaration);
    void visit(const MethodBody* method_body);
    void visit(const MethodDeclaration* method_declaration);
    void visit(const MainClass* main_class);
    void visit(const Goal* goal);
    void visit(const ExpressionNewId* expr);
    void visit(const ExpressionNewIntArray* expr);
};

} // namespace ast;