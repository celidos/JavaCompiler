#ifndef JAVACOMPILER_SRC_AST_VISITORS_VISITOR_GRAPHVIZ_HPP_
#define JAVACOMPILER_SRC_AST_VISITORS_VISITOR_GRAPHVIZ_HPP_

#include <iostream>
#include <string>
#include <stack>

#include "visitors/ivisitor.hpp"
#include "handlers/expressions.hpp"
#include "handlers/statements.hpp"
#include "handlers/types.hpp"
#include "handlers/var_declaration.hpp"
#include "handlers/method_body.hpp"
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

#endif //JAVACOMPILER_SRC_AST_VISITORS_VISITOR_GRAPHVIZ_HPP_
