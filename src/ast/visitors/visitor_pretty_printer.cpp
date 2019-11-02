#include "visitor_pretty_printer.hpp"

void ast::VisitorPrettyPrinter::visit(const PExpressionInt expr) {
    std::cout << "INT(" << expr->getValue() << ") " << expr->getPos() << std::endl;
}

void ast::VisitorPrettyPrinter::visit(const PExpressionBinaryOp expr) {
    std::cout << "BINOP(" << expr->getOp() << ") " << expr->getPos() << std::endl;
}