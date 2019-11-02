#include "visitor_pretty_printer.hpp"

void ast::VisitorPrettyPrinter::visit(const ExpressionInt* expr) {
    std::cout << "INT(" << expr->getValue() << ") " << expr->getPos() << std::endl;
}

void ast::VisitorPrettyPrinter::visit(const ExpressionBinaryOp* expr) {
    std::cout << "BINOP(" << expr->getOp() << ") " << expr->getPos() << std::endl;
}