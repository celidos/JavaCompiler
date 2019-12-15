#pragma once

#include <../ast/handlers/expressions.hpp>

#include "ivisitor.hpp"

#include "visitor_symbol_table_builder.hpp"

#include <../irt/handlers/statements.hpp>
#include <../irt/handlers/expressions.hpp>

#include "handlers/expressions.hpp"
#include "handlers/statements.hpp"
#include "handlers/types.hpp"
#include "handlers/var_declaration.hpp"
#include "handlers/method_body.hpp"
#include "handlers/method_declaration.hpp"
#include "handlers/main_class.hpp"
#include "handlers/class.hpp"
#include "handlers/goal.hpp"

namespace ast {

class VisitorIrtBuilder : public IVisitor {
public:
    VisitorIrtBuilder(std::shared_ptr<symtable::TableGlobal> symbolTable) :
        symbol_table_(symbolTable)
    {  }

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
    void visit(const TypeBoolean* type);
    void visit(const TypeArray* type);
    void visit(const TypeClass* type);
    void visit(const VarDeclaration* var_declaration);
    void visit(const MethodBody* method_body);
    void visit(const MethodDeclaration* method_declaration);
    void visit(const Class* class_var);
    void visit(const MainClass* main_class);
    void visit(const Goal* goal);
    void visit(const ExpressionNewId* expr);
    void visit(const ExpressionNewIntArray* expr);
    void visit(const ExpressionCallFunction* expr);
    void visit(const StatementArrayAssign* statement);
    void visit(const StatementPrint* statement);
    void visit(const StatementWhile* statement);
    void visit(const StatementIf* statement);
    void visit(const Statements* statement);

    std::shared_ptr<irt::IVisitable> retrieveIrt() {
        return last_result_;
    }

private:
    std::shared_ptr<symtable::TableGlobal> symbol_table_;
    std::shared_ptr<irt::IVisitable> last_result_;
};

} // namespace ast