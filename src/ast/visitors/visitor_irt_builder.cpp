#include "visitor_irt_builder.hpp"


namespace ast {

void VisitorIrtBuilder::visit(const ExpressionBinaryOp *expr) {
    expr->getLeft()->accept(this);
    irt::PISubtreeWrapper left = tree_;
    expr->getRight()->accept(this);
    irt::PISubtreeWrapper right = tree_;

    irt::PExpressionBinaryOp res =
        std::make_shared<irt::ExpressionBinaryOp>(expr->getOp(),
                                                  left->toExpression(),
                                                  right->toExpression());
    tree_ = std::make_shared<irt::ExpressionWrapper>(res);
};

void VisitorIrtBuilder::visit(const ExpressionInt *expr) {
    auto res = std::make_shared<irt::ExpressionLoadConst>(expr->getValue());
    tree_ = std::make_shared<irt::ExpressionWrapper>(res);
};

void VisitorIrtBuilder::visit(const ExpressionLogical *expr) {
    auto res = std::make_shared<irt::ExpressionLoadConst>(expr->getValue() == "true" ? 1 : 0);
    tree_ = std::make_shared<irt::ExpressionWrapper>(res);
    std::cerr << "ExpressionLogical";
};

// TODO: fill other classes for irt ---------------------------------------------------------------

void VisitorIrtBuilder::visit(const ExpressionId *expr) {};

void VisitorIrtBuilder::visit(const ExpressionSquareBracket *expr) {};

void VisitorIrtBuilder::visit(const ExpressionLen *expr) {};

void VisitorIrtBuilder::visit(const ExpressionUnaryNegation *expr) {
//  expr XOR true
    std::cerr << "ExpressionUnaryNegation";
    expr->getArg()->accept(this);
    irt::PISubtreeWrapper left = tree_;
    irt::PExpression right = std::make_shared<irt::ExpressionLoadConst>(1);

    irt::PExpressionBinaryOp
        res = std::make_shared<irt::ExpressionBinaryOp>("^", left->toExpression(), right);
    tree_ = std::make_shared<irt::ExpressionWrapper>(res);
};

// TODO: fill other classes for irt ---------------------------------------------------------------

void VisitorIrtBuilder::visit(const ExpressionThis *expr) {};

void VisitorIrtBuilder::visit(const StatementAssign *statement) {};

void VisitorIrtBuilder::visit(const TypeInt *type) {};

void VisitorIrtBuilder::visit(const TypeBoolean *type) {};

void VisitorIrtBuilder::visit(const TypeArray *type) {};

void VisitorIrtBuilder::visit(const TypeClass *type) {};

void VisitorIrtBuilder::visit(const VarDeclaration *var_declaration) {};

void VisitorIrtBuilder::visit(const MethodBody *method_body) {};

void VisitorIrtBuilder::visit(const MethodDeclaration *method_declaration) {};

void VisitorIrtBuilder::visit(const Class *class_var) {};

void VisitorIrtBuilder::visit(const MainClass *main_class) {
    main_class->getStatement()->accept(this);
}; //TODO

void VisitorIrtBuilder::visit(const Goal *goal) {
    goal->getMainClass()->accept(this);

    for (auto &class_ : goal->getClasses()) {
        class_->accept(this);
    }
}; //TODO
void VisitorIrtBuilder::visit(const ExpressionNewId *expr) {};

void VisitorIrtBuilder::visit(const ExpressionNewIntArray *expr) {};

void VisitorIrtBuilder::visit(const ExpressionCallFunction *expr) {};

void VisitorIrtBuilder::visit(const StatementArrayAssign *statement) {};

void VisitorIrtBuilder::visit(const StatementPrint *statement) {
    statement->getExpression()->accept(this);

    auto expression_list = std::make_shared<irt::ExpressionList>(tree_->toExpression());
    auto res = std::make_shared<irt::ExpressionCall>(std::make_shared<irt::ExpressionName>("print"),
                                                expression_list);
    tree_ = std::make_shared<irt::ExpressionWrapper>(res);
}; //TODO
void VisitorIrtBuilder::visit(const StatementWhile *statement) {};

void VisitorIrtBuilder::visit(const StatementIf *statement) {};

void VisitorIrtBuilder::visit(const Statements *statement) {};

} // namespace ast