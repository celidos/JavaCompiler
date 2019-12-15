#include "visitor_typechecker.hpp"

namespace ast {

    void VisitorTypecheckerBuilder::visit(const ExpressionInt* expr) { }
    void VisitorTypecheckerBuilder::visit(const ExpressionBinaryOp* expr) { }
    void VisitorTypecheckerBuilder::visit(const ExpressionLogical* expr) { }
    void VisitorTypecheckerBuilder::visit(const ExpressionId* expr) { }
    void VisitorTypecheckerBuilder::visit(const ExpressionSquareBracket* expr) { }
    void VisitorTypecheckerBuilder::visit(const ExpressionLen* expr) { }
    void VisitorTypecheckerBuilder::visit(const ExpressionUnaryNegation* expr) { }
    void VisitorTypecheckerBuilder::visit(const ExpressionThis* expr) { }
    void VisitorTypecheckerBuilder::visit(const StatementAssign* statement) { }
    void VisitorTypecheckerBuilder::visit(const TypeInt* type) { }
    void VisitorTypecheckerBuilder::visit(const VarDeclaration* var_declaration) { }
    void VisitorTypecheckerBuilder::visit(const MethodBody* method_body) { }
    void VisitorTypecheckerBuilder::visit(const MethodDeclaration* method_declaration) { }
    void VisitorTypecheckerBuilder::visit(const MainClass* main_class) { }
    void VisitorTypecheckerBuilder::visit(const Goal* goal) {
        goal->getMainClass()->accept(this);
    }
    void VisitorTypecheckerBuilder::visit(const ExpressionNewId* expr) { }
    void VisitorTypecheckerBuilder::visit(const ExpressionNewIntArray* expr) { }

    void VisitorTypecheckerBuilder::visit(const TypeBoolean* type) { };
    void VisitorTypecheckerBuilder::visit(const TypeArray* type) { };
    void VisitorTypecheckerBuilder::visit(const TypeClass* type) { };
    void VisitorTypecheckerBuilder::visit(const Class* class_var) { };

    void VisitorTypecheckerBuilder::visit(const ExpressionCallFunction* expr) { };
    void VisitorTypecheckerBuilder::visit(const StatementArrayAssign* statement) { };
    void VisitorTypecheckerBuilder::visit(const StatementPrint* statement) { };
    void VisitorTypecheckerBuilder::visit(const StatementWhile* statement) { };
    void VisitorTypecheckerBuilder::visit(const StatementIf* statement) { };
    void VisitorTypecheckerBuilder::visit(const Statements* statement) { };

} // namespace ast