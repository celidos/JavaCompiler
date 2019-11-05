#include "visitor_graphviz.hpp"

namespace ast {

VisitorGraphviz::VisitorGraphviz(std::string graph_name): graph(graph_name){
}

void VisitorGraphviz::visit(const ExpressionInt* expr, bool need_new_line) {
    std::string node_name = "s" + std::to_string(expr->getValue()) + "_" + std::to_string(reinterpret_cast<int64_t>(expr));
    graph.addNode(node_name);
    node_names.push(node_name);
}

void VisitorGraphviz::visit(const ExpressionBinaryOp* expr, bool need_new_line) {
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

void VisitorGraphviz::visit(const ExpressionLogical* expr, bool need_new_line){}
void VisitorGraphviz::visit(const ExpressionId* expr, bool need_new_line){}
void VisitorGraphviz::visit(const ExpressionSquareBracket* expr, bool need_new_line){}
void VisitorGraphviz::visit(const ExpressionLen* expr, bool need_new_line){}
void VisitorGraphviz::visit(const ExpressionUnaryNegation* expr, bool need_new_line){}
void VisitorGraphviz::visit(const ExpressionThis* expr, bool need_new_line) {}

void VisitorGraphviz::visit(const StatementAssign* statement, bool need_new_line) {
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

void VisitorGraphviz::visit(const TypeInt* type, bool need_new_line) {
    std::string node_name = "sINT_" + std::to_string(reinterpret_cast<int64_t>(type));
    graph.addNode(node_name);
    node_names.push(node_name);
}

void VisitorGraphviz::visit(const VarDeclaration* var_declaration, bool need_new_line) {
    std::string node_name = "sVarDeclaration_" + std::to_string(reinterpret_cast<int64_t>(var_declaration));
    graph.addNode(node_name);

    var_declaration->getType()->accept(this);
    std::string left_child = node_names.top();
    graph.addEdge(node_name, left_child);
    node_names.pop();

    auto current_right_chld = "s" + var_declaration->getIdentifier() + "_" + std::to_string(reinterpret_cast<int64_t>(var_declaration));
    graph.addNode(current_right_chld);
    graph.addEdge(node_name, current_right_chld);
    node_names.push(node_name);
}

void VisitorGraphviz::visit(const MethodBody* method_body, bool need_new_line) {
    std::string node_name = "sMethodBody_" + std::to_string(reinterpret_cast<int64_t>(method_body));
    graph.addNode(node_name);

    method_body->getVarDeclaration()->accept(this);
    std::string left_child = node_names.top();
    graph.addEdge(node_name, left_child);
    node_names.pop();


    method_body->getStatement()->accept(this);
    std::string middle_child = node_names.top();
    graph.addEdge(node_name, middle_child);
    node_names.pop();

    auto current_right_chld = "sReturn_" + std::to_string(reinterpret_cast<int64_t>(method_body));
    graph.addNode(current_right_chld);
    graph.addEdge(node_name, current_right_chld);

    method_body->getExpression()->accept(this);
    std::string next_right_child = node_names.top();
    graph.addEdge(current_right_chld, next_right_child);
    node_names.pop();


    node_names.push(node_name);
}

}
