#ifndef JAVACOMPILER_SRC_AST_VISITORS_VISITOR_PRETTY_PRINTER_HPP_
#define JAVACOMPILER_SRC_AST_VISITORS_VISITOR_PRETTY_PRINTER_HPP_

#include <iostream>

#include "visitors/ivisitor.hpp"
#include "handlers/expressions.hpp"
#include "yyltype.hpp"

namespace ast {

class VisitorPrettyPrinter : public IVisitor {
public:
    VisitorPrettyPrinter() = default;

private:
    void visit(const ExpressionInt* expr);
    void visit(const ExpressionBinaryOp* expr);
};

}

#endif //JAVACOMPILER_SRC_AST_VISITORS_VISITOR_PRETTY_PRINTER_HPP_
