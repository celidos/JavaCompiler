#ifndef JAVACOMPILER_SRC_AST_VISITORS_VISITOR_GRAPHVIZ_HPP_
#define JAVACOMPILER_SRC_AST_VISITORS_VISITOR_GRAPHVIZ_HPP_

#include <iostream>
#include <string>
#include <stack>

#include "ivisitor.hpp"
#include "handlers/expressions.hpp"
#include "handlers/statements.hpp"
#include "handlers/types.hpp"
#include "handlers/var_declaration.hpp"
#include "handlers/method_body.hpp"
#include "handlers/method_declaration.hpp"
#include <handlers/main_class.hpp>
#include <handlers/class.hpp>
#include <handlers/goal.hpp>
#include "yyltype.hpp"
#include "../smart_graphviz/graph.h"

namespace ast {

class VisitorGraphviz : public IVisitor {
public:
    VisitorGraphviz() = default;

    VisitorGraphviz(std::string graph_name);

    const Graphs::UndirectedGraph& GetGraph(){
    	return graph;
    }

private:
	Graphs::UndirectedGraph graph;
	std::stack<std::string> node_names;

    void visit(const ExpressionInt* expr);
    void visit(const ExpressionBinaryOp* expr);
    void visit(const ExpressionLogical* expr);
    void visit(const ExpressionId* expr);
    void visit(const ExpressionSquareBracket* expr);
    void visit(const ExpressionLen* expr);
    void visit(const ExpressionUnaryNegation* expr);
    void visit(const ExpressionThis* expr);
    void visit(const StatementAssign* statement);
    void visit(const TypeInt* type);
    void visit(const TypeBoolean* type);
    void visit(const TypeArray* type);
    void visit(const TypeClass* type);
    void visit(const VarDeclaration* var_declaration);
    void visit(const MethodBody* method_body);
    void visit(const MethodDeclaration* method_declaration);
    void visit(const MainClass* main_class);
    void visit(const Class* class_var);
    void visit(const Goal* goal);
    void visit(const ExpressionNewId* expr);
    void visit(const ExpressionNewIntArray* expr);
    void visit(const ExpressionCallFunction* expr);
    void visit(const StatementArrayAssign* statement);
    void visit(const StatementPrint* statement);
    void visit(const StatementWhile* statement);
    void visit(const StatementIf* statement);
    void visit(const Statements* statement);


};

}

#endif //JAVACOMPILER_SRC_AST_VISITORS_VISITOR_GRAPHVIZ_HPP_
