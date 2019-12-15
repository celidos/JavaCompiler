#include "visitor_irt_builder.hpp"

namespace ast
{
void VisitorIrtBuilder::visit(const ExpressionBinaryOp* expr) { };
void VisitorIrtBuilder::visit(const ExpressionInt* expr) { };
void VisitorIrtBuilder::visit(const ExpressionLogical* expr) { };
void VisitorIrtBuilder::visit(const ExpressionId* expr) { };
void VisitorIrtBuilder::visit(const ExpressionSquareBracket* expr) { };
void VisitorIrtBuilder::visit(const ExpressionLen* expr) { };
void VisitorIrtBuilder::visit(const ExpressionUnaryNegation* expr) { };
void VisitorIrtBuilder::visit(const ExpressionThis* expr) { };
void VisitorIrtBuilder::visit(const StatementAssign* statement) { };
void VisitorIrtBuilder::visit(const TypeInt* type) { };
void VisitorIrtBuilder::visit(const TypeBoolean* type) { };
void VisitorIrtBuilder::visit(const TypeArray* type) { };
void VisitorIrtBuilder::visit(const TypeClass* type) { };
void VisitorIrtBuilder::visit(const VarDeclaration* var_declaration) { };
void VisitorIrtBuilder::visit(const MethodBody* method_body) { };
void VisitorIrtBuilder::visit(const MethodDeclaration* method_declaration) { };
void VisitorIrtBuilder::visit(const Class* class_var) { };
void VisitorIrtBuilder::visit(const MainClass* main_class) { };
void VisitorIrtBuilder::visit(const Goal* goal) { };
void VisitorIrtBuilder::visit(const ExpressionNewId* expr) { };
void VisitorIrtBuilder::visit(const ExpressionNewIntArray* expr) { };
void VisitorIrtBuilder::visit(const ExpressionCallFunction* expr) { };
void VisitorIrtBuilder::visit(const StatementArrayAssign* statement) { };
void VisitorIrtBuilder::visit(const StatementPrint* statement) { };
void VisitorIrtBuilder::visit(const StatementWhile* statement) { };
void VisitorIrtBuilder::visit(const StatementIf* statement) { };
void VisitorIrtBuilder::visit(const Statements* statement) { };

} // namespace ast