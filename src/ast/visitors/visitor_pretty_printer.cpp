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
	YYLTYPE pos = expr->getPos();
	// std::cout << pos;
	// std::cout << pos.first_line << ':' << pos.first_column << " - "
 //       << pos.last_line  << ':' << pos.last_column;
    std::cout << "BinaryOp(";
    expr->getLeft()->accept(this, false);
    std::cout << ", ";
    expr->getRight()->accept(this, false);
    std::cout << ", ";
    std::cout << expr->getOp();
    std::cout << "); ";
    if (need_new_line) {
        std::cout << "\n";
    }
    // std::cout << expr->getPos();
}


void VisitorPrettyPrinter::visit(const ExpressionLogical* expr){}
void VisitorPrettyPrinter::visit(const ExpressionId* expr){}
void VisitorPrettyPrinter::visit(const ExpressionSquareBracket* expr){}
void VisitorPrettyPrinter::visit(const ExpressionLen* expr){}
void VisitorPrettyPrinter::visit(const ExpressionUnaryNegation* expr){}
void VisitorPrettyPrinter::visit(const ExpressionThis* expr) {}

void VisitorPrettyPrinter::visit(const StatementAssign* statement) {

    std::cout << "StatementAssign(" << statement->getIdentifier() <<"; ";
    statement->getExpression()->accept(this, false);
    std::cout << "); ";
    if (need_new_line) {
        std::cout << "\n";
    }
}


void VisitorPrettyPrinter::visit(const TypeInt* type) {

    std::cout << "INT ";
    if (need_new_line) {
        std::cout << "\n";
    }
}

void VisitorPrettyPrinter::visit(const VarDeclaration* var_declaration) {

    std::cout << "VarDeclaration(";
    var_declaration->getType()->accept(this, false);
    std::cout <<var_declaration->getIdentifier()<<")";
    if (need_new_line) {
        std::cout << "\n";
    }
}

void VisitorPrettyPrinter::visit(const MethodBody* method_body) {

    std::cout << "MethodBody(\n";
    method_body->getVarDeclaration()->accept(this, false);
    std::cout << ";\n";
    method_body->getStatement()->accept(this, false);
    std::cout << ";\n";
    std::cout << "Return: ";
    method_body->getExpression()->accept(this, false);
    std::cout <<";\n)";
    if (need_new_line) {
        std::cout <<"\n";
    }
}

void VisitorPrettyPrinter::visit(const MethodDeclaration* method_declaration) {

    std::cout << "MethodDeclaration("<<method_declaration->getPrivacy() <<"; ";
    method_declaration->getType()->accept(this, false);
    std::cout << " "<<method_declaration->getIdentifier() <<"\n";
    method_declaration->getMethodBody()->accept(this, false);
    std::cout <<"\n)";
    if (need_new_line) {
        std::cout <<"\n";
    }
}

void VisitorPrettyPrinter::visit(const MainClass* main_class) {

    std::cout << "MainClass("<<main_class->getIdentifier() <<"; String[] "<<main_class->getVariable() <<"; ";

    main_class->getStatement()->accept(this, false);
    std::cout <<")";
    if (need_new_line) {
        std::cout <<"\n";
    }
}

void VisitorPrettyPrinter::visit(const Goal* goal) {

    std::cout << "Goal(\n";
    goal->getMainClass()->accept(this, true);
    std::cout <<")";
    if (need_new_line) {
        std::cout <<"\n";
    }
}

void VisitorPrettyPrinter::visit(const ExpressionNewId* expr, bool need_new_line) {}
void VisitorPrettyPrinter::visit(const ExpressionNewIntArray* expr, bool need_new_line) {}
}

