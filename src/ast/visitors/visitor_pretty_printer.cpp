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
    expr->getLeft()->accept(this);
    std::cout << ", ";
    expr->getRight()->accept(this);
    std::cout << ", ";
    std::cout << expr->getOp();
    std::cout << ") " << std::endl;

    // std::cout << expr->getPos();
}
}