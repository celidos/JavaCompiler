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
void VisitorGraphviz::visit(const ExpressionThis* expr){}
void VisitorGraphviz::visit(const ExpressionNewId* expr){}
void VisitorGraphviz::visit(const ExpressionNewIntArray* expr){}

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

void VisitorGraphviz::visit(const TypeInt* type) {
    std::string node_name = "sINT_" + std::to_string(reinterpret_cast<int64_t>(type));
    graph.addNode(node_name);
    node_names.push(node_name);
}

void VisitorGraphviz::visit(const VarDeclaration* var_declaration) {
    std::string node_name = "sVarDeclaration_" + std::to_string(reinterpret_cast<int64_t>(var_declaration));
    graph.addNode(node_name);

    var_declaration->getType()->accept(this);
    std::string left_child = node_names.top();
    graph.addEdge(node_name, left_child);
    node_names.pop();

    auto current_right_chld = "s" + var_declaration->getIdentifier() + "_" + std::to_string(reinterpret_cast<int64_t>(var_declaration));
    graph.addNode(current_right_chld);
    graph.addEdge(left_child, current_right_chld);
    node_names.push(node_name);
}

void VisitorGraphviz::visit(const MethodBody* method_body) {
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

void VisitorGraphviz::visit(const MethodDeclaration* method_declaration) {
    std::string node_name = "s" + method_declaration->getPrivacy() + \
                             "__MethodDeclaration_" + std::to_string(reinterpret_cast<int64_t>(method_declaration));
    graph.addNode(node_name);

    method_declaration->getType()->accept(this);
    std::string left_child = node_names.top();
    graph.addEdge(node_name, left_child);
    node_names.pop();

    auto current_right_chld = "s" + method_declaration->getIdentifier() + "_" + std::to_string(reinterpret_cast<int64_t>(method_declaration));
    graph.addNode(current_right_chld);
    graph.addEdge(left_child, current_right_chld);

    method_declaration->getMethodBody()->accept(this);
    std::string middle_child = node_names.top();
    graph.addEdge(node_name, middle_child);
    node_names.pop();

    node_names.push(node_name);
}

void VisitorGraphviz::visit(const MainClass* main_class) {
    std::string node_name = "sMainClass_" + std::to_string(reinterpret_cast<int64_t>(main_class));
    graph.addNode(node_name);

    auto current_left_chld = "sName__" + main_class->getIdentifier() + "_" + std::to_string(reinterpret_cast<int64_t>(main_class));
    graph.addNode(current_left_chld);
    graph.addEdge(node_name, current_left_chld);

    auto current_middle_chld = "sString__" + main_class->getVariable() + "_" + std::to_string(reinterpret_cast<int64_t>(main_class));
    graph.addNode(current_middle_chld);
    graph.addEdge(node_name, current_middle_chld);


    auto current_right_chld = "sStatement_" + std::to_string(reinterpret_cast<int64_t>(main_class));
    graph.addNode(current_right_chld);
    graph.addEdge(node_name, current_right_chld);


    main_class->getStatement()->accept(this);
    std::string right_child = node_names.top();
    graph.addEdge(current_right_chld, right_child);
    node_names.pop();

    node_names.push(node_name);
}


void VisitorGraphviz::visit(const Goal* goal) {
    std::string node_name = "sGoal_" + std::to_string(reinterpret_cast<int64_t>(goal));
    graph.addNode(node_name);

    goal->getMainClass()->accept(this);
    std::string left_child = node_names.top();
    graph.addEdge(node_name, left_child);
    node_names.pop();

    node_names.push(node_name);
}
}
