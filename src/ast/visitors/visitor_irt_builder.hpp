#pragma once

#include <cassert>
#include <iostream>

#include <../ast/handlers/expressions.hpp>

#include "ivisitor.hpp"

#include "../../symbol_table/symbol_table.hpp"
#include "visitor_symbol_table_builder.hpp"

#include <../irt/handlers/memory.hpp>
#include <../irt/handlers/statements.hpp>
#include <../irt/handlers/expressions.hpp>
#include <../irt/handlers/expression_list.hpp>
#include <../irt/wrappers/wrappers.hpp>

#include "handlers/expressions.hpp"
#include "handlers/statements.hpp"
#include "handlers/types.hpp"
#include "handlers/var_declaration.hpp"
#include "handlers/method_body.hpp"
#include "handlers/method_declaration.hpp"
#include "handlers/main_class.hpp"
#include "handlers/class.hpp"
#include "handlers/goal.hpp"

#include "../../irt/utils.hpp"

namespace ast {

class VisitorIrtBuilder : public IVisitor {
public:
    explicit VisitorIrtBuilder(std::shared_ptr<symtable::TableGlobal> symbolTable) :
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
        return tree_->toStatement();
    }

    const std::unordered_map<std::string, irt::PStatement>& getIrtMethodTrees() const {
        return irt_method_trees_;
    }

private:
    std::shared_ptr<symtable::TableGlobal> symbol_table_;
    std::shared_ptr<irt::ISubtreeWrapper> tree_;

    symtable::PClassInfo current_class_table_;
    symtable::PMethodInfo current_method_table_;

    irt::AddressGenerator addr_gen_;
    std::unordered_map<std::string, irt::PStatement> irt_method_trees_;

    irt::PExpression getVariableScope(std::string var_name);
};

} // namespace ast