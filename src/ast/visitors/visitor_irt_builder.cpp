#include "visitor_irt_builder.hpp"

namespace ast
{

void VisitorIrtBuilder::visit(const ExpressionBinaryOp* expr) {
    expr->getLeft()->accept(this);
    irt::PExpression left = std::dynamic_pointer_cast<irt::Expression>(tree_);
    expr->getRight()->accept(this);
    irt::PExpression right = std::dynamic_pointer_cast<irt::Expression>(tree_);

    irt::PExpressionBinaryOp res =
        std::make_shared<irt::ExpressionBinaryOp>(expr->getOp(), left, right);
    tree_ = res;
};

void VisitorIrtBuilder::visit(const ExpressionInt* expr) {
    auto res = std::make_shared<irt::ExpressionLoadConst>(expr->getValue());
    tree_ = res;
};

void VisitorIrtBuilder::visit(const ExpressionLogical* expr) {
    auto res = std::make_shared<irt::ExpressionLoadConst>(expr->getValue() == "true" ? 1 : 0);
    tree_ = res;
};

// TODO: fill other classes for irt ---------------------------------------------------------------

void VisitorIrtBuilder::visit(const ExpressionId* expr) { };
void VisitorIrtBuilder::visit(const ExpressionSquareBracket* expr) { };
void VisitorIrtBuilder::visit(const ExpressionLen* expr) { };

void VisitorIrtBuilder::visit(const ExpressionUnaryNegation* expr) {
    // expr XOR true
    expr->getArg()->accept(this);
    irt::PExpression left = std::dynamic_pointer_cast<irt::Expression>(tree_);
    irt::PExpression right = std::make_shared<irt::ExpressionLoadConst>(1);

    irt::PExpressionBinaryOp res = std::make_shared<irt::ExpressionBinaryOp>("^", left, right);
    tree_ = res;
};

void VisitorIrtBuilder::visit(const ExpressionThis* expr) { };

// TODO: fill other classes for irt ---------------------------------------------------------------

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