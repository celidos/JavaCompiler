#include "visitor_pretty_printer.hpp"

namespace irt{
using namespace MC;

// std::ostream & operator<<(std::ostream &os, const YYLTYPE &pos) {
//     os << pos.first_line << ':' << pos.first_column << " - "
//        << pos.last_line  << ':' << pos.last_column;
//     return os;
// }

void VisitorPrettyPrinter::visit(const ExpressionConst* expr) {
//    // std::cout << "INT(" << expr->getValue() << ") " << expr->getPos() << std::endl;
//
//    std::cout << "Int(" << expr->getValue() << ")";
//
//    // std::cout << expr->getPos();
}

void VisitorPrettyPrinter::visit(const ExpressionBinaryOp* expr) {
//	YYLTYPE pos = expr->getPos();
//	// std::cout << pos;
//	// std::cout << pos.first_line << ':' << pos.first_column << " - "
// //       << pos.last_line  << ':' << pos.last_column;
//    std::cout << "BinaryOp(";
//    expr->getLeft()->accept(this);
//    std::cout << ", ";
//    expr->getRight()->accept(this);
//    std::cout << ", ";
//    std::cout << expr->getOp();
//    std::cout << ")";
//    // std::cout << expr->getPos();
}

void VisitorPrettyPrinter::visit(const ExpressionName* expr) {
//    std::cout << "Bool(" << expr->getValue() << ")";
}

void VisitorPrettyPrinter::visit(const ExpressionTemp* expr) {
//    std::cout << "Var(" << expr->getId() <<")";
}

void VisitorPrettyPrinter::visit(const ExpressionMem* expr) {
//    expr->getEntity()->accept(this);
//    std::cout << "[";
//    expr->getIndex()->accept(this);
//    std::cout <<"]";
}

void VisitorPrettyPrinter::visit(const ExpressionCall* expr) {
//    expr->getArg()->accept(this);
//    std::cout <<".length";
}

void VisitorPrettyPrinter::visit(const ExpressionEseq* expr) {
//    std::cout << "!";
//    expr->getArg()->accept(this);
}

void VisitorPrettyPrinter::visit(const ExpressionArg* expr) {
//    std::cout <<"this";
}

void VisitorPrettyPrinter::visit(const ExpressionLocal* expr) {
//    std::cout << "(new " <<expr->getId()<<")";
}

void VisitorPrettyPrinter::visit(const StatementMove* statement) {
//    std::cout << "StatementAssign(" << statement->getIdentifier() <<" = ";
//    statement->getExpression()->accept(this);
//    std::cout << ")";
}


void VisitorPrettyPrinter::visit(const StatementExp* statement) {
//  std::cout << statement->getIdentifier() << "[";
//  statement->getIndex()->accept(this);
//  std::cout << "] = ";
//  statement->getExpression()->accept(this);
}


void VisitorPrettyPrinter::visit(const StatementJump* statement) {
//  std::cout << "(Print: ";
//  statement->getExpression()->accept(this);
//  std::cout << ")";
}

void VisitorPrettyPrinter::visit(const StatementCJump* statement) {
//  std::cout << "(while (";
//  statement->getCond()->accept(this);
//  std::cout << ") ";
//  statement->getBody()->accept(this);
//  std::cout <<")";
}

void VisitorPrettyPrinter::visit(const StatementSeq* statement) {
//  std::cout << "(if (";
//  statement->getCond()->accept(this);
//  std::cout << ") ";
//  statement->getIfBody()->accept(this);
//  std::cout <<" else ";
//  statement->getElseBody()->accept(this);
//  std::cout <<")";
}

void VisitorPrettyPrinter::visit(const StatementLabel* statement) {
//  std::cout << "{ ";
//  for (const auto& val: statement->getArgs()) {
//    std::cout << "(";
//    val->accept(this);
//    std::cout <<"); ";
//  }
//  std::cout << " }";

}

}

