#include "visitor_graphviz.hpp"

namespace ast {

VisitorGraphviz::VisitorGraphviz(std::string graph_name): graph(graph_name){
}

void VisitorGraphviz::visit(const ExpressionInt* expr) {
    std::string node_name = "s" + std::to_string(expr->getValue()) + "_" + std::to_string(reinterpret_cast<int64_t>(expr));
    graph.addNode(node_name);
    node_names.push(node_name);
}

void VisitorGraphviz::visit(const ExpressionBinaryOp* expr) {
    // Graphviz не может распарсить названия вершин, содержащие +
    std::string node_name = "s" + expr->getOp() + "_" + std::to_string(reinterpret_cast<int64_t>(expr));
    graph.addNode(node_name);

    expr->getLeft()->accept(this);
    std::string left_child = node_names.top();
    graph.addEdge(node_name, left_child);
    node_names.pop();

    expr->getRight()->accept(this);
    std::string right_child = node_names.top();
    graph.addEdge(node_name, right_child);
    node_names.pop();

    node_names.push(node_name);
}

void VisitorGraphviz::visit(const ExpressionLogical* expr){}
void VisitorGraphviz::visit(const ExpressionId* expr){}
void VisitorGraphviz::visit(const ExpressionSquareBracket* expr){}
void VisitorGraphviz::visit(const ExpressionLen* expr){}
void VisitorGraphviz::visit(const ExpressionUnaryNegation* expr){}
void VisitorGraphviz::visit(const ExpressionThis* expr) {}

void VisitorGraphviz::visit(const StatementAssign* statement) {
    std::string node_name = "sStatementAssign_" + std::to_string(reinterpret_cast<int64_t>(statement));
    graph.addNode(node_name);
    auto current_left_chld = "s" + statement->getIdentifier() + "_" + std::to_string(reinterpret_cast<int64_t>(statement));
    graph.addNode(current_left_chld);
    graph.addEdge(node_name, current_left_chld);
    statement->getExpression()->accept(this);
    std::string right_child = node_names.top();
    graph.addEdge(node_name, right_child);
    node_names.pop();

    node_names.push(node_name);
}
}
