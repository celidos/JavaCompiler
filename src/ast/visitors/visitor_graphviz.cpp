#include "visitor_graphviz.hpp"

namespace ast {

VisitorGraphviz::VisitorGraphviz(std::string graph_name): graph(graph_name){
}

void VisitorGraphviz::visit(const ExpressionInt* expr) {
    std::string node_name = std::to_string(expr->getValue());
    graph.addNode(node_name);
    node_names.push(node_name);
}

void VisitorGraphviz::visit(const ExpressionBinaryOp* expr) {
    // Graphviz не может распарсить названия вершин, содержащие +
    std::string node_name = "ExpressionBinaryOp: " + expr->getOp();
    graph.addNode(node_name + "_" + std::to_string(reinterpret_cast<int64_t>(expr)));

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
    std::string node_name = "StatementAssign";
    graph.addNode(node_name + "_" + std::to_string(reinterpret_cast<int64_t>(statement)));
    auto current_left_chld = statement->getIdentifier() + std::to_string(reinterpret_cast<int64_t>(statement));
    graph.addNode(current_left_chld);
    graph.addEdge(node_name, current_left_chld);
    statement->getExpression()->accept(this);
    std::string right_child = node_names.top();
    graph.addEdge(node_name, right_child);
    node_names.pop();

    node_names.push(node_name);
}
}
