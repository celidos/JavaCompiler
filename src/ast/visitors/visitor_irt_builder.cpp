#include "visitor_irt_builder.hpp"


int MemoryAddress::counter_ = 0;

int Register::counter_ = 0;

namespace ast {

void VisitorIrtBuilder::visit(const ExpressionBinaryOp *expr) {
    std::cerr << "Begin ExpressionBinaryOp\n";
    expr->getLeft()->accept(this);
    irt::PISubtreeWrapper left = tree_;
    expr->getRight()->accept(this);
    irt::PISubtreeWrapper right = tree_;

    irt::PExpressionBinaryOp res =
        std::make_shared<irt::ExpressionBinaryOp>(expr->getOp(),
                                                  left->toExpression(),
                                                  right->toExpression());
    tree_ = std::make_shared<irt::ExpressionWrapper>(res);
    std::cerr << "End ExpressionBinaryOp\n";
};

void VisitorIrtBuilder::visit(const ExpressionInt *expr) {
    std::cerr << "Begin ExpressionInt\n";
    std::cerr << expr->getValue() << "\n";
    auto res = std::make_shared<irt::ExpressionLoadConst>(expr->getValue());
    tree_ = std::make_shared<irt::ExpressionWrapper>(res);
    std::cerr << "End ExpressionInt\n";
};

void VisitorIrtBuilder::visit(const ExpressionLogical *expr) {
    std::cerr << "Begin ExpressionLogical\n";
    auto res = std::make_shared<irt::ExpressionLoadConst>(expr->getValue() == "true" ? 1 : 0);
    tree_ = std::make_shared<irt::ExpressionWrapper>(res);
    std::cerr << "End ExpressionLogical\n";
};

// TODO: fill other classes for irt ---------------------------------------------------------------

void VisitorIrtBuilder::visit(const ExpressionId *expr) {};

void VisitorIrtBuilder::visit(const ExpressionSquareBracket *expr) {};

void VisitorIrtBuilder::visit(const ExpressionLen *expr) {};

void VisitorIrtBuilder::visit(const ExpressionUnaryNegation *expr) {
    std::cerr << "Begin ExpressionUnaryNegation\n";
//  expr XOR true
    expr->getArg()->accept(this);
    irt::PISubtreeWrapper left = tree_;
    irt::PExpression right = std::make_shared<irt::ExpressionLoadConst>(1);

    irt::PExpressionBinaryOp
        res = std::make_shared<irt::ExpressionBinaryOp>("^", left->toExpression(), right);
    tree_ = std::make_shared<irt::ExpressionWrapper>(res);
    std::cerr << "End ExpressionUnaryNegation\n";
};

// TODO: fill other classes for irt ---------------------------------------------------------------

void VisitorIrtBuilder::visit(const ExpressionThis *expr) {};

void VisitorIrtBuilder::visit(const StatementAssign *statement) {};

void VisitorIrtBuilder::visit(const TypeInt *type) {};

void VisitorIrtBuilder::visit(const TypeBoolean *type) {};

void VisitorIrtBuilder::visit(const TypeArray *type) {};

void VisitorIrtBuilder::visit(const TypeClass *type) {};

void VisitorIrtBuilder::visit(const VarDeclaration *var_declaration) {};

void VisitorIrtBuilder::visit(const MethodBody *method_body) {

    std::cerr << "Begin MethodBody\n";

    auto statement_array = method_body->getStatement();

    if (!statement_array.empty()) {
        statement_array[0]->accept(this);
        auto statement1 = tree_;
        if (statement_array.size() > 1) {

            statement_array[1]->accept(this);
            auto statement2 = tree_;

            auto seq = std::make_shared<irt::StatementSeq>(statement1->toStatement(),
                                                           statement2->toStatement());

            for (int i = 2; i < static_cast<int>(statement_array.size()) ; i++) {
                statement_array[i]->accept(this);
                auto statement = tree_;
                seq = std::make_shared<irt::StatementSeq>(seq, statement->toStatement());
            }
            tree_ = std::make_shared<irt::StatementWrapper>(seq);
        }
    } else {
        tree_ =  std::make_shared<irt::StatementWrapper>(std::make_shared<irt::StatementNan>());
    }

    auto body = tree_;

    method_body->getExpression()->accept(this);
    Register memory_;

    auto result =
        std::make_shared<irt::StatementMove>(std::make_shared<irt::ExpressionTemp>(memory_),
                                             tree_->toExpression());

    auto res = std::make_shared<irt::StatementSeq>(body->toStatement(), result);
    tree_ = std::make_shared<irt::StatementWrapper>(res);

    std::cerr << "End MethodBody\n";
};

void VisitorIrtBuilder::visit(const MethodDeclaration *method_declaration) {
    std::cerr << "Begin MethodDeclaration\n";
    current_method_table_ = current_class_table_->getMethod(method_declaration->getIdentifier());
    method_declaration->getMethodBody()->accept(this);
    std::cerr << "End MethodDeclaration\n";
};

void VisitorIrtBuilder::visit(const Class *class_var) {
    std::cerr << "Begin Class\n";
    current_class_table_ = symbol_table_->getClass(class_var->getIdentifier());

    for (auto &method: class_var->getMethodDeclaration()) {
        method->accept(this);
    }
    std::cerr << "End Class\n";
};

void VisitorIrtBuilder::visit(const MainClass *main_class) {
    std::cerr << "Begin MainClass\n";
    current_class_table_ = symbol_table_->getClass(main_class->getIdentifier());

    main_class->getStatement()->accept(this);
    std::cerr << "End MainClass\n";
};

void VisitorIrtBuilder::visit(const Goal *goal) {
    std::cerr << "Begin Goal\n";
    goal->getMainClass()->accept(this);

    auto goal_seq_ = tree_->toStatement();

    for (auto &class_ : goal->getClasses()) {
        std::cerr << "classes\n";
        class_->accept(this);
        goal_seq_ = std::make_shared<irt::StatementSeq>(goal_seq_, tree_->toStatement());
    }
    tree_ = std::make_shared<irt::StatementWrapper>(goal_seq_);
    std::cerr << "End Goal\n";
};

void VisitorIrtBuilder::visit(const ExpressionNewId *expr) {
    std::cerr << "Begin ExpressionNewId\n";
    current_class_table_ = symbol_table_->getClass(expr->getId());

    int size = current_class_table_->getAllVars().size();
    irt::ExpressionList arguments(std::make_shared<irt::ExpressionLoadConst>(size));

    auto malloc = std::make_shared<irt::ExpressionName>("new " + current_class_table_->getName());
    auto call_malloc = std::make_shared<irt::ExpressionCall>(malloc,
                                                             std::make_shared<irt::ExpressionList>(
                                                                 arguments));

    tree_ = std::make_shared<irt::ExpressionWrapper>(call_malloc);
    std::cerr << "End ExpressionNewId\n";
};

// TODO: fill other classes for irt ---------------------------------------------------------------

void VisitorIrtBuilder::visit(const ExpressionNewIntArray *expr) {};

void VisitorIrtBuilder::visit(const ExpressionCallFunction *expr) {
    std::cerr << "Begin ExpressionCallFunction\n";
    expr->getExpr()->accept(this);  // return

    // this будем хранить первым аргументом
    irt::ExpressionList parsed_arguments(tree_->toExpression());

    auto arguments = expr->getArgs();
    for (auto &argument: arguments) {
        argument->accept(this);
        parsed_arguments.addExpression(tree_->toExpression());
    }
    auto function_call =
        std::make_shared<irt::ExpressionCall>(std::make_shared<irt::ExpressionName>(expr->getFuncName()),
                                              std::make_shared<irt::ExpressionList>(parsed_arguments));

    tree_ = std::make_shared<irt::ExpressionWrapper>(function_call);
    std::cerr << "End ExpressionCallFunction\n";
};

// TODO: fill other classes for irt ---------------------------------------------------------------

void VisitorIrtBuilder::visit(const StatementArrayAssign *statement) {};

void VisitorIrtBuilder::visit(const StatementPrint *statement) {
    std::cerr << "Begin StatementPrint\n";
    statement->getExpression()->accept(this);

    auto expression_list = std::make_shared<irt::ExpressionList>(tree_->toExpression());
    auto res = std::make_shared<irt::ExpressionCall>(std::make_shared<irt::ExpressionName>("print"),
                                                     expression_list);
    tree_ = std::make_shared<irt::ExpressionWrapper>(res);
    std::cerr << "End StatementPrint\n";
};

// TODO: fill other classes for irt ---------------------------------------------------------------

void VisitorIrtBuilder::visit(const StatementWhile *statement) {};

void VisitorIrtBuilder::visit(const StatementIf *statement) {
    statement->getCond()->accept(this);

    irt::PISubtreeWrapper cond = root_;
    auto expr = std::dynamic_pointer_cast<irt::PExpression>(cond->toExpression());

    auto label_final = std::make_shared<irt::StatementLabel>(this->addr_gen_.genAddress());
    auto label_if_body = std::make_shared<irt::StatementLabel>(this->addr_gen_.genAddress());
    auto label_else_body = std::make_shared<irt::StatementLabel>(this->addr_gen_.genAddress());

    irt::PISubtreeWrapper
    statement->getIfBody()->accept(this);
    statement->getElseBody()->accept(this);

    auto seq1 = std::make_shared<irt::StatementSeq>(label_if_body,
        std::dynamic_pointer_cast<Statement>(root_));
    seq1 = std::make_shared<irt::StatementSeq>(ifStatement,
        std::make_shared<irt::StatementJump>(label_final));

    auto seq2 = std::make_shared<irt::StatementSeq>(label_else_body,
        std::dynamic_pointer_cast<irt::Statement>(root_));
    seq2 = std::make_shared<irt::StatementSeq>(seq2,
        std::make_shared<irt::StatementJump>(label_final));

    auto cjmp = std::make_shared<irt::StatementCJump>("&&", expr,
        std::make_shared<irt::ExpressionLoadConst>(1), label_if_body, label_else_body);

    auto seq3 = std::make_shared<irt::StatementSeq>(cjmp, seq2);
    auto seq4 = std::make_shared<irt::StatementSeq>(seq3, seq1);
    auto seq4 = std::make_shared<irt::StatementSeq>(seq3, seq1);

    auto root_ = std::make_shared<irt::StatementSeq>(seq4, label_final);
};

void VisitorIrtBuilder::visit(const Statements *statement) {};

} // namespace ast