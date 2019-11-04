#ifndef JAVACOMPILER_SRC_AST_VISITORS_VISITOR_PRETTY_PRINTER_HPP_
#define JAVACOMPILER_SRC_AST_VISITORS_VISITOR_PRETTY_PRINTER_HPP_

#include <iostream>

#include <handlers/statements.hpp>

namespace ast {

class VisitorPrettyPrinter : public IVisitor {
public:
    VisitorPrettyPrinter() = default;

private:
    void visit(const ExpressionInt* expr);
    void visit(const ExpressionBinaryOp* expr);
    void visit(const ExpressionLogical* expr);
    void visit(const ExpressionId* expr);
    void visit(const ExpressionSquareBracket* expr);
    void visit(const ExpressionLen* expr);
    void visit(const ExpressionUnaryNegation* expr);
    void visit(const ExpressionThis* expr);
    void visit(const StatementAssign* statement);
};

}

#endif //JAVACOMPILER_SRC_AST_VISITORS_VISITOR_PRETTY_PRINTER_HPP_
