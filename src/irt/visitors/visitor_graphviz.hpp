#pragma once

#include <iostream>
#include <string>
#include <stack>

#include "ivisitor.hpp"
#include "../irt/handlers/expressions.hpp"
#include "../irt/handlers/expression_list.hpp"
#include "../irt/handlers/statements.hpp"

#include "../smart_graphviz/graph.h"

namespace irt {

class VisitorIrtGraphviz : public IVisitor {
public:
    explicit VisitorIrtGraphviz(std::string graph_name) : graph_(graph_name) { };

    const Graphs::UndirectedGraph& GetGraph() {
        return graph_;
    }

private:
    Graphs::UndirectedGraph graph_;
    std::stack<std::string> node_names_;

    void visit(const ExpressionLoadConst* loader);
    void visit(const ExpressionBinaryOp* expr);
    void visit(const ExpressionName* expr);
//    void visit(const ExpressionTemp* expr);
//    void visit(const ExpressionMem* expr);
    void visit(const ExpressionCall* expr);
//    void visit(const ExpressionEseq* expr);
//    void visit(const ExpressionArg* expr);
//    void visit(const ExpressionLocal* expr);
//    void visit(const StatementMove* statement);
//    void visit(const StatementExp* statement);
//    void visit(const StatementJump* statement);
//    void visit(const StatementCJump* statement);
//    void visit(const StatementSeq* statement);
//    void visit(const StatementLabel* statement);

    void visit(const ExpressionList* expressions);

    // TODO: FILL IN

};

}