#include "visitor_pretty_printer.hpp"

namespace ast{
using namespace MC;

// std::ostream & operator<<(std::ostream &os, const YYLTYPE &pos) {
//     os << pos.first_line << ':' << pos.first_column << " - "
//        << pos.last_line  << ':' << pos.last_column;
//     return os;
// }

void VisitorPrettyPrinter::visit(const ExpressionInt* expr) {
    // std::cout << "INT(" << expr->getValue() << ") " << expr->getPos() << std::endl;

    std::cout << "Int(" << expr->getValue() << ")";

    // std::cout << expr->getPos();
}

void VisitorPrettyPrinter::visit(const ExpressionBinaryOp* expr) {
	// YYLTYPE pos = expr->getPos();
	// std::cout << pos;
	// std::cout << pos.first_line << ':' << pos.first_column << " - "
    //     << pos.last_line  << ':' << pos.last_column;
    std::cout << "BinaryOp(";
    expr->getLeft()->accept(this);
    std::cout << ", ";
    expr->getRight()->accept(this);
    std::cout << ", ";
    std::cout << expr->getOp();
    std::cout << ")";
    // std::cout << expr->getPos();
}

void VisitorPrettyPrinter::visit(const ExpressionLogical* expr) {
    std::cout << "Bool(" << expr->getValue() << ")";
}

void VisitorPrettyPrinter::visit(const ExpressionId* expr) {
    std::cout << "Var(" << expr->getId() <<")";
}

void VisitorPrettyPrinter::visit(const ExpressionSquareBracket* expr) {
    expr->getEntity()->accept(this);
    std::cout << "[";
    expr->getIndex()->accept(this);
    std::cout <<"]";
}

void VisitorPrettyPrinter::visit(const ExpressionLen* expr) {
    expr->getArg()->accept(this);
    std::cout <<".length";
}

void VisitorPrettyPrinter::visit(const ExpressionUnaryNegation* expr) {
    std::cout << "!";
    expr->getArg()->accept(this);
}

void VisitorPrettyPrinter::visit(const ExpressionThis* expr) {
    std::cout <<"this";
}

void VisitorPrettyPrinter::visit(const ExpressionNewId* expr) {
    std::cout << "(new " <<expr->getId()<<")";
}

void VisitorPrettyPrinter::visit(const ExpressionNewIntArray* expr) {
    std::cout << "(new int[";
    expr->getCounter()->accept(this);
    std::cout <<"])";

}

void VisitorPrettyPrinter::visit(const ExpressionCallFunction* expr) {
    expr->getExpr()->accept(this);
    std::cout << "." <<expr->getFuncName() << "(";
    for (const auto& val: expr->getArgs()) {
        val->accept(this);
        std::cout <<", ";
    }
    std::cout << ")";
}

void VisitorPrettyPrinter::visit(const StatementAssign* statement) {

    std::cout << "StatementAssign(" << statement->getIdentifier() <<" = ";
    statement->getExpression()->accept(this);
    std::cout << ")";
}


void VisitorPrettyPrinter::visit(const StatementArrayAssign* statement) {
  std::cout << statement->getIdentifier() << "[";
  statement->getIndex()->accept(this);
  std::cout << "] = ";
  statement->getExpression()->accept(this);
}


void VisitorPrettyPrinter::visit(const StatementPrint* statement) {
  std::cout << "(Print: ";
  statement->getExpression()->accept(this);
  std::cout << ")";
}

void VisitorPrettyPrinter::visit(const StatementWhile* statement) {
  std::cout << "(while (";
  statement->getCond()->accept(this);
  std::cout << ") ";
  statement->getBody()->accept(this);
  std::cout <<")";
}

void VisitorPrettyPrinter::visit(const StatementIf* statement) {
  std::cout << "(if (";
  statement->getCond()->accept(this);
  std::cout << ") ";
  statement->getIfBody()->accept(this);
  std::cout <<" else ";
  statement->getElseBody()->accept(this);
  std::cout <<")";
}

void VisitorPrettyPrinter::visit(const Statements* statement) {
  std::cout << "{ ";
  for (const auto& val: statement->getStatements()) {
    std::cout << "(";
    val->accept(this);
    std::cout <<"); ";
  }
  std::cout << " }";

}


void VisitorPrettyPrinter::visit(const TypeInt* type) {
    std::cout << "INT";
}


void VisitorPrettyPrinter::visit(const TypeBoolean* type) {
    std::cout << "BOOL";
}


void VisitorPrettyPrinter::visit(const TypeArray* type) {
    std::cout << "Array";
}


void VisitorPrettyPrinter::visit(const TypeClass* type) {
    std::cout << "Type " << type->getType() <<" ";
}


void VisitorPrettyPrinter::visit(const VarDeclaration* var_declaration) {

    std::cout << "VarDeclaration(";
    var_declaration->getType()->accept(this);
    std::cout <<" "<<var_declaration->getIdentifier()<<")";
}

void VisitorPrettyPrinter::visit(const MethodBody* method_body) {

    std::cout << "MethodBody( VARS(";
    for (const auto& val: method_body->getVarDeclaration()) {
        val->accept(this);
        std::cout <<", ";
    }
    std::cout << "); Statements(";
    for (const auto& val: method_body->getStatement()) {
        val->accept(this);
        std::cout <<", ";
    }
    std::cout << "); Return: ";
    method_body->getExpression()->accept(this);
    std::cout <<";)";
}

void VisitorPrettyPrinter::visit(const MethodDeclaration* method_declaration) {

    std::cout << "MethodDeclaration( Privacy: "<<method_declaration->getPrivacy() <<"; Type: ";
    method_declaration->getType()->accept(this);
    std::cout << "; Name: "<<method_declaration->getIdentifier() <<"; Args: ";
    for (const auto& arg: method_declaration->getArgs()) {
        const auto& type = arg.first;
        const auto& name = arg.second;
        std::cout << "(" <<type->getType() <<" " <<name <<"), ";
    }
    std::cout <<"; Body: ";
    method_declaration->getMethodBody()->accept(this);
    std::cout <<")";
}

void VisitorPrettyPrinter::visit(const Class* class_var) {
    std::cout << "Class("<<class_var->getIdentifier() <<
    "Parent: "<< class_var->getParent()<<"; VARS(";
    for (const auto& val:class_var->getVarDeclaration()) {
        val->accept(this);
        std::cout <<", ";
    }
    std::cout << "); ( Declarations: (";
    for (const auto& val: class_var->getMethodDeclaration()) {
        val->accept(this);
        std::cout <<", ";
    }
    std::cout <<"));";

}

void VisitorPrettyPrinter::visit(const MainClass* main_class) {

    std::cout << "MainClass("<<main_class->getIdentifier() <<"; String[] "<<main_class->getVariable() <<"; ";

    main_class->getStatement()->accept(this);
    std::cout <<")";
}

void VisitorPrettyPrinter::visit(const Goal* goal) {

    std::cout << "Goal(";
    goal->getMainClass()->accept(this);
    std::cout << "; Classes: ";
    for (const auto& val: goal->getClasses()) {
        std::cout <<"(";
        val->accept(this);
        std::cout <<"), ";
    }

    std::cout <<")\n";
}

}

