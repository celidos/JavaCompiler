#ifndef JAVACOMPILER_SRC_IRT_VISITORS_VISITOR_PRETTY_PRINTER_HPP_
#define JAVACOMPILER_SRC_IRT_VISITORS_VISITOR_PRETTY_PRINTER_HPP_

#include <iostream>

#include <handlers/statements.hpp>
#include <handlers/types.hpp>
#include <handlers/var_declaration.hpp>
#include <handlers/method_body.hpp>
#include <handlers/method_declaration.hpp>
#include <handlers/main_class.hpp>
#include <handlers/class.hpp>
#include <handlers/goal.hpp>

namespace irt {

class VisitorPrettyPrinter : public IVisitor {
public:
    VisitorPrettyPrinter() = default;

private:
    void visit(const ExpressionConst* expr);
    void visit(const ExpressionBinaryOp* expr);
    void visit(const ExpressionName* expr);
    void visit(const ExpressionTemp* expr);
    void visit(const ExpressionMem* expr);
    void visit(const ExpressionCall* expr);
    void visit(const ExpressionEseq* expr);
    void visit(const ExpressionArg* expr);
    void visit(const ExpressionLocal* expr);
    void visit(const StatementMove* statement);
    void visit(const StatementExp* statement);
    void visit(const StatementJump* statement);
    void visit(const StatementCJump* statement);
    void visit(const StatementSeq* statement);
    void visit(const StatementLabel* statement);

};

}

#endif //JAVACOMPILER_SRC_IRT_VISITORS_VISITOR_PRETTY_PRINTER_HPP_
