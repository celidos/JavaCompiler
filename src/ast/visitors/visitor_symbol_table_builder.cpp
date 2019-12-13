#include <visitor_symbol_table_builder.hpp>

namespace ast{

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
void VisitorSymtableBuilder::visit(const MethodBody* method_body) { }
void VisitorSymtableBuilder::visit(const MethodDeclaration* method_declaration) { }
void VisitorSymtableBuilder::visit(const MainClass* main_class) {
    table[main_class]
}
void VisitorSymtableBuilder::visit(const Goal* goal) {
    goal->getMainClass()->accept(this);
    /// TODO visit_goal must visit all classes!!! not only main
}
void VisitorSymtableBuilder::visit(const ExpressionNewId* expr) { }
void VisitorSymtableBuilder::visit(const ExpressionNewIntArray* expr) { }

} // namespace ast