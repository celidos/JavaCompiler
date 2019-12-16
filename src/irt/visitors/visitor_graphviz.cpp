#include "visitor_graphviz.hpp"


namespace irt {

void VisitorIrtGraphviz::visit(const ExpressionLoadConst *loader) {
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(loader));
    std::string label = std::to_string(loader->getValue());
    graph_.addNode(node_name, label);
    node_names_.push(node_name);
}

void VisitorIrtGraphviz::visit(const ExpressionBinaryOp *expr) {
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
}

//void VisitorIrtGraphviz::visit(const ExpressionLocal* expr){
//    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(expr));
//    std::string label = std::to_string(expr->getId());
//    graph_.addNode(node_name, label);
//    node_names_.push(node_name);
//}

void VisitorIrtGraphviz::visit(const ExpressionName *expr) {
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(expr));
    std::string label = expr->getName();
    graph_.addNode(node_name, label);
    node_names_.push(node_name);
}

void VisitorIrtGraphviz::visit(const ExpressionCall *expr) {
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(expr));
    graph_.addNode(node_name, "call");

    expr->getFunction()->accept(this);
    std::string func_node = node_names_.top();
    graph_.addEdge(node_name, func_node);
    node_names_.pop();

    expr->getArguments()->accept(this);
    std::string arg_node = node_names_.top();
    graph_.addEdge(node_name, arg_node);
    node_names_.pop();

    node_names_.push(node_name);
}

void VisitorIrtGraphviz::visit(const ExpressionList* expressions){
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(expressions));
    graph_.addNode(node_name, "Arguments:");

    for(auto expr: expressions->getExpressions()){
        expr->accept(this);
        std::string func_node = node_names_.top();
        graph_.addEdge(node_name, func_node);
        node_names_.pop();
    }

    node_names_.push(node_name);
}

// TODO: fill in

} // namespace irt