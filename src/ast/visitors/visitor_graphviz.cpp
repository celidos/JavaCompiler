#include "visitor_graphviz.hpp"

namespace ast {

VisitorGraphviz::VisitorGraphviz(const std::string& graph_name): graph(graph_name){
}

void VisitorGraphviz::visit(const ExpressionInt* expr) {
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(expr));
    std::string label = std::to_string(expr->getValue());
    graph.addNode(node_name, label);
    node_names.push(node_name);
}

void VisitorGraphviz::visit(const ExpressionBinaryOp* expr) {
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(expr));
    graph.addNode(node_name, expr->getOp());


    std::string left = "left" + std::to_string(reinterpret_cast<int64_t>(expr));
    graph.addNode(left, "left operand");

    std::string right = "right" + std::to_string(reinterpret_cast<int64_t>(expr));
    graph.addNode(right, "right operand");

    graph.addEdge(node_name, left);
    graph.addEdge(node_name, right);
    expr->getLeft()->accept(this);
    std::string left_child = node_names.top();
    graph.addEdge(left, left_child);
    node_names.pop();

    expr->getRight()->accept(this);
    std::string right_child = node_names.top();
    graph.addEdge(right, right_child);
    node_names.pop();

    node_names.push(node_name);
}

void VisitorGraphviz::visit(const ExpressionLogical* expr) {
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(expr));
    graph.addNode(node_name, expr->getValue());
    node_names.push(node_name);
}

void VisitorGraphviz::visit(const ExpressionId* expr) {
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(expr));
    graph.addNode(node_name, "Var: " + expr->getId());
    node_names.push(node_name);
}

void VisitorGraphviz::visit(const ExpressionSquareBracket* expr) {
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(expr));
    graph.addNode(node_name, "Expr[Expr]");

    expr->getEntity()->accept(this);
    std::string left_child = node_names.top();
    graph.addEdge(node_name, left_child);
    node_names.pop();

    expr->getIndex()->accept(this);
    std::string right_child = node_names.top();
    graph.addEdge(node_name, right_child);
    node_names.pop();



    node_names.push(node_name);
}

void VisitorGraphviz::visit(const ExpressionLen* expr) {
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(expr));
    graph.addNode(node_name, "Expr.length");
    expr->getArg()->accept(this);
    std::string child = node_names.top();
    graph.addEdge(node_name, child);
    node_names.pop();

    node_names.push(node_name);
}

void VisitorGraphviz::visit(const ExpressionUnaryNegation* expr) {
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(expr));
    graph.addNode(node_name, "!");
    expr->getArg()->accept(this);
    std::string child = node_names.top();
    graph.addEdge(node_name, child);
    node_names.pop();

    node_names.push(node_name);

}

void VisitorGraphviz::visit(const ExpressionThis* expr) {
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(expr));
    graph.addNode(node_name, "this");
    node_names.push(node_name);
}

void VisitorGraphviz::visit(const ExpressionNewId* expr) {
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(expr));
    graph.addNode(node_name, "new");
    auto child = "chld" + std::to_string(reinterpret_cast<int64_t>(expr));
    graph.addNode(child, "class: " + expr->getId());
    graph.addEdge(node_name, child);

    node_names.push(node_name);
}

void VisitorGraphviz::visit(const ExpressionNewIntArray* expr) {
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(expr));
    graph.addNode(node_name, "new int[Expr]");
    expr->getCounter()->accept(this);
    std::string child = node_names.top();
    graph.addEdge(node_name, child);
    node_names.pop();

    node_names.push(node_name);


}


void VisitorGraphviz::visit(const ExpressionCallFunction* expr) {
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(expr));
    graph.addNode(node_name, "Call Function");

    expr->getExpr()->accept(this);
    std::string left_child = node_names.top();
    graph.addEdge(node_name, left_child);
    node_names.pop();

    std::string middle_child = "chld" + std::to_string(reinterpret_cast<int64_t>(expr));
    graph.addNode(middle_child, "Func name: " + expr->getFuncName());
    graph.addEdge(node_name, middle_child);


    std::string right_child = "params" + std::to_string(reinterpret_cast<int64_t>(expr));
    graph.addNode(right_child, "Parameters");
    graph.addEdge(node_name, right_child);

    for (const auto &param : expr->getArgs()) {
        param->accept(this);
        std::string curr_child = node_names.top();
        graph.addEdge(right_child, curr_child);
        node_names.pop();
    }

    node_names.push(node_name);
}


void VisitorGraphviz::visit(const StatementAssign* statement) {
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(statement));
    graph.addNode(node_name, "Statement Assign: =");
    auto current_left_chld = "chld" + std::to_string(reinterpret_cast<int64_t>(statement));
    graph.addNode(current_left_chld, "Var: " + statement->getIdentifier());

    graph.addEdge(node_name, current_left_chld);
    statement->getExpression()->accept(this);
    std::string right_child = node_names.top();
    graph.addEdge(node_name, right_child);
    node_names.pop();

    node_names.push(node_name);
}

void VisitorGraphviz::visit(const StatementArrayAssign* statement) {
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(statement));
    graph.addNode(node_name, "Statement Array Assign: =");
    auto current_left_chld = "chld" + std::to_string(reinterpret_cast<int64_t>(statement));
    graph.addNode(current_left_chld, "Var []: " + statement->getIdentifier());
    graph.addEdge(node_name, current_left_chld);
    statement->getIndex()->accept(this);
    graph.addEdge(current_left_chld, node_names.top());
    node_names.pop();

    statement->getExpression()->accept(this);
    std::string right_child = node_names.top();
    graph.addEdge(node_name, right_child);
    node_names.pop();

    node_names.push(node_name);

}

void VisitorGraphviz::visit(const StatementPrint* statement) {
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(statement));
    graph.addNode(node_name, "print()");
    statement->getExpression()->accept(this);
    graph.addEdge(node_name, node_names.top());
    node_names.pop();

    node_names.push(node_name);
}


void VisitorGraphviz::visit(const StatementWhile* statement) {
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(statement));
    graph.addNode(node_name, "while");

    std::string cond_chld = "condchld" + std::to_string(reinterpret_cast<int64_t>(statement));
    graph.addNode(cond_chld, "condition");
    statement->getCond()->accept(this);
    graph.addEdge(node_name, cond_chld);
    graph.addEdge(cond_chld, node_names.top());
    node_names.pop();

    std::string body_chld = "bodychld" + std::to_string(reinterpret_cast<int64_t>(statement));
    graph.addNode(body_chld, "Body:");
    statement->getBody()->accept(this);
    graph.addEdge(node_name, body_chld);
    graph.addEdge(body_chld, node_names.top());
    node_names.pop();

    node_names.push(node_name);
}

void VisitorGraphviz::visit(const StatementIf* statement) {
     std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(statement));
    graph.addNode(node_name, "if");

    std::string cond_chld = "condchld" + std::to_string(reinterpret_cast<int64_t>(statement));
    graph.addNode(cond_chld, "condition");
    statement->getCond()->accept(this);
    graph.addEdge(node_name, cond_chld);
    graph.addEdge(cond_chld, node_names.top());
    node_names.pop();

    std::string body_if_chld = "bodyifchld" + std::to_string(reinterpret_cast<int64_t>(statement));
    graph.addNode(body_if_chld, "Body If:");
    statement->getIfBody()->accept(this);
    graph.addEdge(node_name, body_if_chld);
    graph.addEdge(body_if_chld, node_names.top());
    node_names.pop();

    std::string body_else_chld = "bodyelsechld" + std::to_string(reinterpret_cast<int64_t>(statement));
    graph.addNode(body_else_chld, "Body Else:");
    statement->getElseBody()->accept(this);
    graph.addEdge(node_name, body_else_chld);
    graph.addEdge(body_else_chld, node_names.top());
    node_names.pop();

    node_names.push(node_name);

}

void VisitorGraphviz::visit(const Statements* statement) {
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(statement));
    graph.addNode(node_name, "Statements:");
    for (const auto &param : statement->getStatements()) {
        param->accept(this);
        std::string curr_child = node_names.top();
        graph.addEdge(node_name, curr_child);
        node_names.pop();
    }
    node_names.push(node_name);
}


void VisitorGraphviz::visit(const TypeInt* type) {
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(type));
    graph.addNode(node_name, "Type: INT");
    node_names.push(node_name);
}


void VisitorGraphviz::visit(const TypeBoolean* type) {
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(type));
    graph.addNode(node_name, "Type: BOOL");
    node_names.push(node_name);
}

void VisitorGraphviz::visit(const TypeArray* type) {
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(type));
    graph.addNode(node_name, "Type: ARRAY");
    node_names.push(node_name);
}

void VisitorGraphviz::visit(const TypeClass* type) {
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(type));
    graph.addNode(node_name, "Type: " + type->getType());
    node_names.push(node_name);
}

void VisitorGraphviz::visit(const VarDeclaration* var_declaration) {
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(var_declaration));
    graph.addNode(node_name, "Var Declaration");

    var_declaration->getType()->accept(this);
    std::string left_child = node_names.top();
    graph.addEdge(node_name, left_child);
    node_names.pop();

    auto current_right_chld = "chld" + std::to_string(reinterpret_cast<int64_t>(var_declaration));
    graph.addNode(current_right_chld, "Var name: " + var_declaration->getIdentifier());
    graph.addEdge(node_name, current_right_chld);
    node_names.push(node_name);
}

void VisitorGraphviz::visit(const MethodBody* method_body) {
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(method_body));
    graph.addNode(node_name, "Method Body");

    std::string var_name = "var" + std::to_string(reinterpret_cast<int64_t>(method_body));
    graph.addNode(var_name, "VARS");
    graph.addEdge(node_name, var_name);

    for (const auto &var : method_body->getVarDeclaration()) {
        var->accept(this);
        std::string curr_child = node_names.top();
        graph.addEdge(var_name, curr_child);
        node_names.pop();
    }

    std::string statements_name = "statements" + std::to_string(reinterpret_cast<int64_t>(method_body));
    graph.addNode(statements_name, "STATEMENTS");
    graph.addEdge(node_name, statements_name);

    for (const auto &statement : method_body->getStatement()) {
        statement->accept(this);
        std::string curr_child = node_names.top();
        graph.addEdge(statements_name, curr_child);
        node_names.pop();
    }

    auto current_right_chld = "ret" + std::to_string(reinterpret_cast<int64_t>(method_body));
    graph.addNode(current_right_chld, "Return");
    graph.addEdge(node_name, current_right_chld);

    method_body->getExpression()->accept(this);
    std::string next_right_child = node_names.top();
    graph.addEdge(current_right_chld, next_right_child);
    node_names.pop();


    node_names.push(node_name);
}

void VisitorGraphviz::visit(const MethodDeclaration* method_declaration) {
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(method_declaration));
    graph.addNode(node_name, "Method Declaration");

    std::string info_name = "info" + std::to_string(reinterpret_cast<int64_t>(method_declaration));
    graph.addNode(info_name, "Info about Method");
    graph.addEdge(node_name, info_name);

    std::string privacy_name = "privacy" + std::to_string(reinterpret_cast<int64_t>(method_declaration));
    graph.addNode(privacy_name, "Privacy: " +  method_declaration->getPrivacy());
    graph.addEdge(info_name, privacy_name);

    method_declaration->getType()->accept(this);
    std::string left_child = node_names.top();
    graph.addEdge(info_name, left_child);
    node_names.pop();


    auto current_right_chld = "chld" + std::to_string(reinterpret_cast<int64_t>(method_declaration));
    graph.addNode(current_right_chld, "Method name: " + method_declaration->getIdentifier());
    graph.addEdge(info_name, current_right_chld);

    auto args_name = "args" + std::to_string(reinterpret_cast<int64_t>(method_declaration));
    graph.addNode(args_name, "Args");
    graph.addEdge(info_name, args_name);

    for (const auto& arg: method_declaration->getArgs()) {
        const PType& type = arg.first;
        auto name = arg.second;
        auto one_arg_name = "arg" + std::to_string(reinterpret_cast<int64_t>(&arg));
        graph.addNode(one_arg_name, "Argument");
        graph.addEdge(args_name, one_arg_name);

        auto arg_type = "type" + std::to_string(reinterpret_cast<int64_t>(&arg));
        graph.addNode(arg_type, "Type: " + type->getType());
        graph.addEdge(one_arg_name, arg_type);

        auto arg_name_name = "argname" + std::to_string(reinterpret_cast<int64_t>(&arg));
        graph.addNode(arg_name_name, "Name: " + name);
        graph.addEdge(one_arg_name, arg_name_name);
    }


    method_declaration->getMethodBody()->accept(this);
    std::string middle_child = node_names.top();
    graph.addEdge(node_name, middle_child);
    node_names.pop();

    node_names.push(node_name);
}


void VisitorGraphviz::visit(const Class* class_var) {
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(class_var));
    graph.addNode(node_name, "Class");

    auto ident_name = "left" + std::to_string(reinterpret_cast<int64_t>(class_var));
    graph.addNode(ident_name, "Name: " + class_var->getIdentifier());
    graph.addEdge(node_name, ident_name);

    auto parent_name = "parent" + std::to_string(reinterpret_cast<int64_t>(class_var));
    graph.addNode(parent_name, "Parent: " + class_var->getParent());
    graph.addEdge(node_name, parent_name);

    std::string var_name = "var" + std::to_string(reinterpret_cast<int64_t>(class_var));
    graph.addNode(var_name, "VARS");
    graph.addEdge(node_name, var_name);

    for (const auto &var : class_var->getVarDeclaration()) {
        var->accept(this);
        std::string curr_child = node_names.top();
        graph.addEdge(var_name, curr_child);
        node_names.pop();
    }

    std::string methods_name = "methods" + std::to_string(reinterpret_cast<int64_t>(class_var));
    graph.addNode(methods_name, "Methods");
    graph.addEdge(node_name, methods_name);

    for (const auto &method : class_var->getMethodDeclaration()) {
        method->accept(this);
        std::string curr_child = node_names.top();
        graph.addEdge(methods_name, curr_child);
        node_names.pop();
    }

    node_names.push(node_name);
}


void VisitorGraphviz::visit(const MainClass* main_class) {
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(main_class));
    graph.addNode(node_name, "Main Class");

    auto current_left_chld = "left" + std::to_string(reinterpret_cast<int64_t>(main_class));
    graph.addNode(current_left_chld, "Name: " + main_class->getIdentifier());
    graph.addEdge(node_name, current_left_chld);

    auto current_middle_chld = "middle" + std::to_string(reinterpret_cast<int64_t>(main_class));
    graph.addNode(current_middle_chld, "String: " + main_class->getVariable());
    graph.addEdge(node_name, current_middle_chld);


    auto current_right_chld = "right" + std::to_string(reinterpret_cast<int64_t>(main_class));
    graph.addNode(current_right_chld, "Statement");
    graph.addEdge(node_name, current_right_chld);


    main_class->getStatement()->accept(this);
    std::string right_child = node_names.top();
    graph.addEdge(current_right_chld, right_child);
    node_names.pop();

    node_names.push(node_name);
}


void VisitorGraphviz::visit(const Goal* goal) {
    std::string node_name = "class" + std::to_string(reinterpret_cast<int64_t>(goal));
    graph.addNode(node_name, "Goal");

    goal->getMainClass()->accept(this);
    std::string left_child = node_names.top();
    graph.addEdge(node_name, left_child);
    node_names.pop();

    std::string classes_name = "classes" + std::to_string(reinterpret_cast<int64_t>(goal));
    graph.addNode(classes_name, "CLASSES");
    graph.addEdge(node_name, classes_name);

    for (const auto &class_var : goal->getClasses()) {
        class_var->accept(this);
        std::string curr_child = node_names.top();
        graph.addEdge(classes_name, curr_child);
        node_names.pop();
    }


    node_names.push(node_name);
}
}
