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

    if(!std::dynamic_pointer_cast<irt::ExpressionLoadConst>(left->toExpression())){
        left = std::make_shared<irt::ExpressionWrapper>(std::make_shared<irt::ExpressionMem>(left->toExpression()));
    }

    if(!std::dynamic_pointer_cast<irt::ExpressionLoadConst>(right->toExpression())){
        right = std::make_shared<irt::ExpressionWrapper>(std::make_shared<irt::ExpressionMem>(right->toExpression()));
    }

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

irt::PExpression VisitorIrtBuilder::getVariableScope(std::string var_name){
    auto var_address = current_method_table_->getAddress(var_name);

    if (current_method_table_->hasVar(var_name)) {
        return std::make_shared<irt::ExpressionLocal>(var_address);
    } else {
        return std::make_shared<irt::ExpressionArg>(var_address);
    }
}

void VisitorIrtBuilder::visit(const ExpressionId *expr) {
    auto var_name = expr->getId();
    tree_ = std::make_shared<irt::ExpressionWrapper>(getVariableScope(var_name));

};


void VisitorIrtBuilder::visit(const ExpressionSquareBracket *expr) {
    std::cerr << "Begin ExpressionSquareBracket\n";

    expr->getEntity()->accept(this);
    irt::PISubtreeWrapper entity = tree_;
    expr->getIndex()->accept(this);
    irt::PISubtreeWrapper index = tree_;

    if(!std::dynamic_pointer_cast<irt::ExpressionLoadConst>(index->toExpression())){
        index = std::make_shared<irt::ExpressionWrapper>(std::make_shared<irt::ExpressionMem>(index->toExpression()));
    }

    irt::PExpressionBinaryOp res =
        std::make_shared<irt::ExpressionBinaryOp>("+",
                                                  entity->toExpression(),
                                                  index->toExpression());
    tree_ = std::make_shared<irt::ExpressionWrapper>(std::make_shared<irt::ExpressionMem>(res));
    std::cerr << "End ExpressionSquareBracket\n";
};


// TODO: fill other classes for irt ---------------------------------------------------------------

void VisitorIrtBuilder::visit(const ExpressionLen *expr) {

    expr->getArg()->accept(this);
    irt::ExpressionList arguments(tree_->toExpression());

    auto length = std::make_shared<irt::ExpressionName>("length");
    auto call_length = std::make_shared<irt::ExpressionCall>(length,
                                                             std::make_shared<irt::ExpressionList>(
                                                                 arguments));

    tree_ = std::make_shared<irt::ExpressionWrapper>(call_length);
};

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

void VisitorIrtBuilder::visit(const ExpressionThis *expr) {
    std::cerr << "Begin ExpressionThis\n";
    // this - нулевой аргумент
    auto expression_this = std::make_shared<irt::ExpressionArg>("argument_this");
    tree_ =  std::make_shared<irt::ExpressionWrapper>(expression_this);
    std::cerr << "End ExpressionThis\n";
};

void VisitorIrtBuilder::visit(const StatementAssign *statement) {
    std::cerr << "Begin StatementAssign\n";
    statement->getExpression()->accept(this);

    auto memory_node = tree_->toExpression();

    // если константа, то мы не должны выделять память
    if (!std::dynamic_pointer_cast<irt::ExpressionLocal>(tree_->toExpression()) &&
        !std::dynamic_pointer_cast<irt::ExpressionLoadConst>(tree_->toExpression()) &&
        !std::dynamic_pointer_cast<irt::ExpressionBinaryOp>(tree_->toExpression()) &&
        !std::dynamic_pointer_cast<irt::ExpressionMem>(tree_->toExpression())) {
        memory_node = std::make_shared<irt::ExpressionMem>(memory_node);
    }

    auto var_name = statement->getIdentifier();

    std::cerr << "Begin getVariableScope\n";
    auto var_address_node = getVariableScope(var_name);
    std::cerr << "End getVariableScope\n";
    auto move_node = std::make_shared<irt::StatementMove>(var_address_node, memory_node);
    tree_ = std::make_shared<irt::StatementWrapper>(move_node);

    std::cerr << "End StatementAssign\n";
};

void VisitorIrtBuilder::visit(const TypeInt *type) {
    // не должно быть в irt tree
    assert(false);
};

void VisitorIrtBuilder::visit(const TypeBoolean *type) {
    // не должно быть в irt tree
    assert(false);
};

void VisitorIrtBuilder::visit(const TypeArray *type) {
    // не должно быть в irt tree
    assert(false);
};

void VisitorIrtBuilder::visit(const TypeClass *type) {
    // не должно быть в irt tree
    assert(false);
};

void VisitorIrtBuilder::visit(const VarDeclaration *var_declaration) {
    // не должно быть в irt tree
    assert(false);
};

void VisitorIrtBuilder::visit(const MethodBody *method_body) {

    std::cerr << "Begin MethodBody\n";

    auto statement_array = method_body->getStatement();

    for (int i = 0; i < static_cast<int>(statement_array.size()); ++i) {
        std::cerr << "\n\n--------------------------\n";
        statement_array[i]->accept(this);
        std::cerr << "--------------------------\n";
    }

    /*
     *    REVERSED ORDER OF STATEMENTS. ATTENTION
     */

    int nnn = static_cast<int>(statement_array.size());

    if (!statement_array.empty()) {
        statement_array[nnn - 1]->accept(this);    // TODO

        auto statement = tree_;
        auto seq = std::make_shared<irt::StatementSeq>(std::make_shared<irt::StatementNan>(),
                                                       statement->toStatement());
            for (int i = nnn - 2; i >= 0; --i) {
                statement_array[i]->accept(this);
                auto statement = tree_;
                seq = std::make_shared<irt::StatementSeq>(seq, statement->toStatement());
            }
            tree_ = std::make_shared<irt::StatementWrapper>(seq);

    } else {
        tree_ = std::make_shared<irt::StatementWrapper>(std::make_shared<irt::StatementNan>());
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
        std::string method_name = class_var->getIdentifier() + '_' + method->getIdentifier();
        irt_method_trees_[method_name] = tree_->toStatement();
    }
    std::cerr << "End Class\n";
};

void VisitorIrtBuilder::visit(const MainClass *main_class) {
    std::cerr << "Begin MainClass\n";
    current_class_table_ = symbol_table_->getClass(main_class->getIdentifier());

    main_class->getStatement()->accept(this);
    irt_method_trees_["main"] = tree_->toStatement();
    std::cerr << "End MainClass\n";
};

void VisitorIrtBuilder::visit(const Goal *goal) {
    std::cerr << "Begin Goal\n";
    goal->getMainClass()->accept(this);
    for (auto &class_ : goal->getClasses()) {
        std::cerr << "classes\n";
        class_->accept(this);
    }
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

void VisitorIrtBuilder::visit(const ExpressionNewIntArray *expr) {
    std::cerr << "Begin ExpressionNewIntArray\n";
    expr->getCounter()->accept(this);

    irt::ExpressionList arguments(tree_->toExpression());

    auto malloc = std::make_shared<irt::ExpressionName>("new int[]");
    auto call_malloc = std::make_shared<irt::ExpressionCall>(malloc,
                                                             std::make_shared<irt::ExpressionList>(
                                                                 arguments));

    tree_ = std::make_shared<irt::ExpressionWrapper>(call_malloc);

    Register memory_;

    auto move_statement =
        std::make_shared<irt::StatementMove>(std::make_shared<irt::ExpressionTemp>(memory_),
                                             call_malloc);

    auto return_register = std::make_shared<irt::ExpressionTemp>(memory_);

    auto res = std::make_shared<irt::ExpressionSeq>(move_statement, return_register);
    tree_ = std::make_shared<irt::ExpressionWrapper>(res);

    std::cerr << "End ExpressionNewIntArray\n";
};

void VisitorIrtBuilder::visit(const ExpressionCallFunction *expr) {
    std::cerr << "Begin ExpressionCallFunction\n";
    expr->getExpr()->accept(this);  // this

    // this будем хранить первым аргументом
    irt::ExpressionList parsed_arguments(tree_->toExpression());

    auto arguments = expr->getArgs();
    for (auto &argument: arguments) {
        std::cerr << "!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
        argument->accept(this);
        parsed_arguments.addExpression(tree_->toExpression());
        std::cerr << "!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
    }
    auto function_call =
        std::make_shared<irt::ExpressionCall>(std::make_shared<irt::ExpressionName>(expr->getFuncName()),
                                              std::make_shared<irt::ExpressionList>(parsed_arguments));

    tree_ = std::make_shared<irt::ExpressionWrapper>(function_call);
    std::cerr << "End ExpressionCallFunction\n";
};

// TODO: fill other classes for irt ---------------------------------------------------------------

void VisitorIrtBuilder::visit(const StatementArrayAssign *statement) {
    std::cerr << "Begin StatementArrayAssign\n";
    statement->getIndex()->accept(this);
    auto index = tree_;
    statement->getExpression()->accept(this);
    auto expression = tree_;

    auto array_node = getVariableScope(statement->getIdentifier());


    auto array_with_id_node =
        std::make_shared<irt::ExpressionBinaryOp>("+",
                                                  array_node,
                                                  index->toExpression());

    auto move_node = std::make_shared<irt::StatementMove>(array_with_id_node, expression->toExpression());
    tree_ = std::make_shared<irt::StatementWrapper>(move_node);

    std::cerr << "End StatementArrayAssign\n";
};

void VisitorIrtBuilder::visit(const StatementPrint *statement) {
    std::cerr << "Begin StatementPrint\n";
    statement->getExpression()->accept(this);

    irt::ExpressionList expression_list(tree_->toExpression());
    auto res = std::make_shared<irt::ExpressionCall>(std::make_shared<irt::ExpressionName>("print"),
                                                     std::make_shared<irt::ExpressionList>(expression_list));
    tree_ = std::make_shared<irt::ExpressionWrapper>(res);
    std::cerr << "End StatementPrint\n";
};

// TODO: fill other classes for irt ---------------------------------------------------------------

void VisitorIrtBuilder::visit(const StatementWhile *statement) {
    /*
                                                  seq2
                                                /      \
                                              /      LABEL_FINAL
                                          seq
                                       /      \
                                   seq _       jump LABEL_COND
                      ___________/      \_
                    /                      seq
                seq                      /     \
              /     \             LABEL_BODY   cycle
     LABEL_COND      CJUMP                      body
                 && 1; LABEL_BODY;           statement
                    LABEL_FINAL
    */

    statement->getCond()->accept(this);
    irt::PISubtreeWrapper cond = tree_;

    auto label_cond = std::make_shared<irt::StatementLabel>(this->addr_gen_.genAddress());
    auto label_body = std::make_shared<irt::StatementLabel>(this->addr_gen_.genAddress());
    auto label_final = std::make_shared<irt::StatementLabel>(this->addr_gen_.genAddress());

    statement->getBody()->accept(this);
    irt::PISubtreeWrapper body_wrapped = tree_;

    auto cjmp = std::make_shared<irt::StatementCJump>(
        "&&",
        cond->toExpression(),
        std::make_shared<irt::ExpressionLoadConst>(1),
        label_body->getLabel(),
        label_final->getLabel()
    );

    auto seq = std::make_shared<irt::StatementSeq>(label_body, body_wrapped->toStatement());
    auto seq2 = std::make_shared<irt::StatementSeq>(label_cond, cjmp);
    seq2 = std::make_shared<irt::StatementSeq>(seq2, seq);
    seq2 = std::make_shared<irt::StatementSeq>(seq2, std::make_shared<irt::StatementJump>(label_cond));
    seq2 = std::make_shared<irt::StatementSeq>(seq2, label_final);

    tree_ = std::make_shared<irt::StatementWrapper>(seq2);
};

void VisitorIrtBuilder::visit(const StatementIf *statement) {
    /*
                                                     root
                                                  /        \
                                              seq4         LABEL_FINAL
                                      _______/    \
                             _______/               \
                           /                          \
                     seq3                               \
                  __/    \                                \
              __/          \                                \
            /                \                                \
        CJUMP                 seq1                          seq2
    && 1; LABEL_IF;         _/      \                    _/       \
       LABEL_ELSE        _/        jump               _/         jump
                       /        LABEL_FINAL         /         LABEL_FINAL
                    seq                          seq
                 /        \                    /      \
            LABEL_IF   Statement        LABEL_ELSE  Statement
                        if body                     else body

    */

    // cond

    std::cerr << "Begin StatementIf\n";
    statement->getCond()->accept(this);
    irt::PISubtreeWrapper cond_wrap = tree_;
    irt::PExpression expr = cond_wrap->toExpression();

    std::cerr << "ok we are here ... " << std::endl;
    auto label_final = std::make_shared<irt::StatementLabel>(this->addr_gen_.genAddress());
    auto label_if_body = std::make_shared<irt::StatementLabel>(this->addr_gen_.genAddress());
    auto label_else_body = std::make_shared<irt::StatementLabel>(this->addr_gen_.genAddress());

    std::cerr << "passed this ... " << std::endl;

    statement->getIfBody()->accept(this);
    irt::PISubtreeWrapper if_body_wrap = tree_;

    statement->getElseBody()->accept(this);
    irt::PISubtreeWrapper else_body_wrap = tree_;

    // if
    auto seq1 = std::make_shared<irt::StatementSeq>(label_if_body,
        std::dynamic_pointer_cast<irt::Statement>(if_body_wrap->toStatement()));
    seq1 = std::make_shared<irt::StatementSeq>(seq1,
        std::make_shared<irt::StatementJump>(label_final));

    // else
    auto seq2 = std::make_shared<irt::StatementSeq>(label_else_body,
        std::dynamic_pointer_cast<irt::Statement>(else_body_wrap->toStatement()));
    seq2 = std::make_shared<irt::StatementSeq>(seq2,
        std::make_shared<irt::StatementJump>(label_final));

    auto cjmp = std::make_shared<irt::StatementCJump>("&&", expr,
        std::make_shared<irt::ExpressionLoadConst>(1),
        label_if_body->getLabel(), label_else_body->getLabel());

    auto seq3 = std::make_shared<irt::StatementSeq>(cjmp, seq1);
    auto seq4 = std::make_shared<irt::StatementSeq>(seq3, seq2);

    auto res = std::make_shared<irt::StatementSeq>(seq4, label_final);
    tree_ = std::make_shared<irt::StatementWrapper>(res);
    std::cerr << "End StatementIf\n";
};

void VisitorIrtBuilder::visit(const Statements *statement) {};

} // namespace ast