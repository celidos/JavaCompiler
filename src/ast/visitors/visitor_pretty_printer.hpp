#ifndef JAVACOMPILER_SRC_AST_VISITORS_VISITOR_PRETTY_PRINTER_HPP_
#define JAVACOMPILER_SRC_AST_VISITORS_VISITOR_PRETTY_PRINTER_HPP_

#include <iostream>

#include <handlers/statements.hpp>
#include <handlers/types.hpp>
#include <handlers/var_declaration.hpp>
#include <handlers/method_body.hpp>

namespace ast {

class VisitorPrettyPrinter : public IVisitor {
public:
    VisitorPrettyPrinter() = default;

private:
    void visit(const ExpressionInt* expr, bool need_new_line = true);
    void visit(const ExpressionBinaryOp* expr, bool need_new_line = true);
    void visit(const ExpressionLogical* expr, bool need_new_line = true);
    void visit(const ExpressionId* expr, bool need_new_line = true);
    void visit(const ExpressionSquareBracket* expr, bool need_new_line = true);
    void visit(const ExpressionLen* expr, bool need_new_line = true);
    void visit(const ExpressionUnaryNegation* expr, bool need_new_line = true);
    void visit(const ExpressionThis* expr, bool need_new_line = true);
    void visit(const StatementAssign* statement, bool need_new_line = true);
    void visit(const TypeInt* type, bool need_new_line = true);
    void visit(const VarDeclaration* var_declaration, bool need_new_line = true);
    void visit(const MethodBody* method_body, bool need_new_line = true);

};

}

#endif //JAVACOMPILER_SRC_AST_VISITORS_VISITOR_PRETTY_PRINTER_HPP_
