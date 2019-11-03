#ifndef JAVACOMPILER_SRC_AST_VISITORS_VISITOR_GRAPHVIZ_HPP_
#define JAVACOMPILER_SRC_AST_VISITORS_VISITOR_GRAPHVIZ_HPP_

#include <iostream>
#include <string>
#include <stack>

#include "visitors/ivisitor.hpp"
#include "handlers/expressions.hpp"
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
};

}

#endif //JAVACOMPILER_SRC_AST_VISITORS_VISITOR_GRAPHVIZ_HPP_
