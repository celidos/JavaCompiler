#include "visitor_graphviz.hpp"

namespace irt {

void VisitorIrtGraphviz::visit(const ExpressionLoadConst *loader) {
    std::cerr << "Begin ExpressionLoadConst\n";

    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(loader));
    std::string label = "CONST " + std::to_string(loader->getValue());
    graph_.addNode(node_name, label);
    node_names_.push(node_name);

    std::cerr << "End ExpressionLoadConst\n";
}

void VisitorIrtGraphviz::visit(const ExpressionBinaryOp *expr) {
    std::cerr << "Begin ExpressionBinaryOp\n";

    // Graphviz не может распарсить названия вершин, содержащие +
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(expr));
    graph_.addNode(node_name, "BINOP(" + expr->getOp() + ")");

    std::string left = "left" + std::to_string(reinterpret_cast<int64_t>(expr));
    graph_.addNode(left, "left operand");

    std::string right = "right" + std::to_string(reinterpret_cast<int64_t>(expr));
    graph_.addNode(right, "right operand");

    graph_.addEdge(node_name, left);
    graph_.addEdge(node_name, right);
    expr->getLeft()->accept(this);
    std::string left_child = node_names_.top();
    graph_.addEdge(left, left_child);
    node_names_.pop();

    expr->getRight()->accept(this);
    std::string right_child = node_names_.top();
    graph_.addEdge(right, right_child);
    node_names_.pop();

    node_names_.push(node_name);

    std::cerr << "End ExpressionBinaryOp\n";
}

void VisitorIrtGraphviz::visit(const ExpressionName *expr) {
    std::cerr << "Begin ExpressionName\n";
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(expr));
    graph_.addNode(node_name, "Function:");

    std::string label_name = "label" + std::to_string(reinterpret_cast<int64_t>(expr));
    std::string label = expr->getName();
    graph_.addNode(label_name, label);

    graph_.addEdge(node_name, label_name);
    node_names_.push(node_name);
    std::cerr << "End ExpressionName\n";
}

void VisitorIrtGraphviz::visit(const ExpressionTemp* expr){
    std::cerr << "Begin ExpressionTemp\n";
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(expr));
    std::string label = "TEMP " + static_cast<std::string>(expr->getRegister());
    graph_.addNode(node_name, label);
    node_names_.push(node_name);
    std::cerr << "End ExpressionTemp\n";
}

// TODO: fill other classes for irt graphviz ------------------------------------------------------

void VisitorIrtGraphviz::visit(const ExpressionMem* expr){
    std::cerr << "Begin ExpressionMem\n";
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(expr));
    std::string label = "MEM";
    graph_.addNode(node_name, label);

    expr->getAddress()->accept(this);
    graph_.addEdge(node_name, node_names_.top());
    node_names_.pop();

    node_names_.push(node_name);
    std::cerr << "End ExpressionMem\n";
};


void VisitorIrtGraphviz::visit(const ExpressionCall *expr) {
    std::cerr << "Begin ExpressionCall\n";
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(expr));
    graph_.addNode(node_name, "CALL");
    graph_.addNode(node_name, "CALL");

    expr->getFunction()->accept(this);
    std::string func_node = node_names_.top();
    graph_.addEdge(node_name, func_node);
    node_names_.pop();

    expr->getArguments()->accept(this);
    std::string arg_node = node_names_.top();
    graph_.addEdge(node_name, arg_node);
    node_names_.pop();

    node_names_.push(node_name);
    std::cerr << "End ExpressionCall\n";
}

// TODO: fill other classes for irt graphviz ------------------------------------------------------

void VisitorIrtGraphviz::visit(const ExpressionSeq* expr){};

void VisitorIrtGraphviz::visit(const ExpressionArg* expr) {
    std::cerr << "Begin ExpressionArg\n";
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(expr));
    std::string label = "ARG " + expr->getArgument();
    graph_.addNode(node_name, label);
    node_names_.push(node_name);
    std::cerr << "End ExpressionArg\n";
};

void VisitorIrtGraphviz::visit(const ExpressionLocal* expr) {
    std::cerr << "Begin ExpressionLocal\n";
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(expr));
    std::string label = "LOCAL " + expr->getId();
    graph_.addNode(node_name, label);
    node_names_.push(node_name);

    std::cerr << "End ExpressionLocal\n";
};

void VisitorIrtGraphviz::visit(const StatementMove* statement){
    std::cerr << "Begin StatementMove\n";
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(statement));
    graph_.addNode(node_name, "Move:");

    std::string destination_node = "destination" + std::to_string(reinterpret_cast<int64_t>(statement));
    graph_.addNode(destination_node, "Destination:");
    graph_.addEdge(node_name, destination_node);

    std::string source_node = "source" + std::to_string(reinterpret_cast<int64_t>(statement));
    graph_.addNode(source_node, "Source:");
    graph_.addEdge(node_name, source_node);

    statement->getDestination()->accept(this);
    graph_.addEdge(destination_node, node_names_.top());
    node_names_.pop();

    statement->getSource()->accept(this);
    graph_.addEdge(source_node, node_names_.top());
    node_names_.pop();

    node_names_.push(node_name);
    std::cerr << "End StatementMove\n";
}

void VisitorIrtGraphviz::visit(const StatementExp* statement){
    std::cerr << "Begin StatementExp\n";
    statement->getExpression()->accept(this);
    std::cerr << "End StatementExp\n";
}

// TODO: fill other classes for irt graphviz ------------------------------------------------------

void VisitorIrtGraphviz::visit(const StatementJump* statement){};

void VisitorIrtGraphviz::visit(const StatementCJump* statement){};

void VisitorIrtGraphviz::visit(const StatementSeq* statement){
    std::cerr << "Begin StatementSeq\n";
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(statement));
    graph_.addNode(node_name, "SEQ");

    statement->getLeftStatement()->accept(this);
    graph_.addEdge(node_name, node_names_.top());
    node_names_.pop();

    statement->getRightStatement()->accept(this);
    graph_.addEdge(node_name, node_names_.top());
    node_names_.pop();

    node_names_.push(node_name);
    std::cerr << "End StatementSeq\n";
};

// TODO: fill other classes for irt graphviz ------------------------------------------------------

void VisitorIrtGraphviz::visit(const StatementLabel* statement){};

void VisitorIrtGraphviz::visit(const StatementNan* statement){
    std::cerr << "Begin StatementNan\n";
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(statement));
    graph_.addNode(node_name, "NaN");
    node_names_.push(node_name);
    std::cerr << "End StatementNan\n";
};

void VisitorIrtGraphviz::visit(const ExpressionList* expressions){
    std::cerr << "Begin ExpressionList\n";
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(expressions));
    graph_.addNode(node_name, "Arguments:");

    for(auto expr: expressions->getExpressions()){
        expr->accept(this);
        std::string func_node = node_names_.top();
        graph_.addEdge(node_name, func_node);
        node_names_.pop();
    }

    node_names_.push(node_name);
    std::cerr << "End ExpressionList\n";
}

} // namespace irt