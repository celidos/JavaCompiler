#include "visitor_symbol_table_builder.hpp"

namespace ast {

void VisitorSymtableBuilder::visit(const ExpressionInt* expr) { }
void VisitorSymtableBuilder::visit(const ExpressionBinaryOp* expr) { }
void VisitorSymtableBuilder::visit(const ExpressionLogical* expr) { }
void VisitorSymtableBuilder::visit(const ExpressionId* expr) { }
void VisitorSymtableBuilder::visit(const ExpressionSquareBracket* expr) { }
void VisitorSymtableBuilder::visit(const ExpressionLen* expr) { }
void VisitorSymtableBuilder::visit(const ExpressionUnaryNegation* expr) { }
void VisitorSymtableBuilder::visit(const ExpressionThis* expr) { }
void VisitorSymtableBuilder::visit(const StatementAssign* statement) { }
void VisitorSymtableBuilder::visit(const TypeInt* type) { }
void VisitorSymtableBuilder::visit(const VarDeclaration* var_declaration) { }
void VisitorSymtableBuilder::visit(const MethodBody* method_body) {}
void VisitorSymtableBuilder::visit(const MethodDeclaration* method_declaration) {
    symtable::PMethodInfo method_info = std::make_shared<symtable::MethodInfo>(method_declaration->getIdentifier(),
                                                                           method_declaration->getPrivacy(),
                                                                           method_declaration->getType()->getType());
    for (const auto& param: method_declaration->getArgs()) {
        method_info->addParam(param.second, param.first->getType());
    }
    for (const auto& var: method_declaration->getMethodBody()->getVarDeclaration()) {
        method_info->addVar(var);
    }
    last_method_ = method_info;
}
void VisitorSymtableBuilder::visit(const MainClass* main_class) { }
void VisitorSymtableBuilder::visit(const Goal* goal) {
    for(const auto& pclass: goal->getClasses()) {
      pclass->accept(this);
    }
    // table_->Print();
}
void VisitorSymtableBuilder::visit(const ExpressionNewId* expr) { }
void VisitorSymtableBuilder::visit(const ExpressionNewIntArray* expr) { }

void VisitorSymtableBuilder::visit(const TypeBoolean* type) { };
void VisitorSymtableBuilder::visit(const TypeArray* type) { };
void VisitorSymtableBuilder::visit(const TypeClass* type) { };
void VisitorSymtableBuilder::visit(const Class* class_var) {
    // class_var->accept(this);
    symtable::PClassInfo current = std::make_shared<symtable::ClassInfo>(class_var->getIdentifier(), class_var->getParent());
    for (const auto& var: class_var->getVarDeclaration()) {
        current->addVar(var);
    }
    for (const auto& method: class_var->getMethodDeclaration()) {
        method->accept(this);
        current->addMethod(last_method_);
    }
    table_->addClass(current);
};

void VisitorSymtableBuilder::visit(const ExpressionCallFunction* expr) { };
void VisitorSymtableBuilder::visit(const StatementArrayAssign* statement) { };
void VisitorSymtableBuilder::visit(const StatementPrint* statement) { };
void VisitorSymtableBuilder::visit(const StatementWhile* statement) { };
void VisitorSymtableBuilder::visit(const StatementIf* statement) { };
void VisitorSymtableBuilder::visit(const Statements* statement) { };

} // namespace ast
