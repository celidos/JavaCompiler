#pragma once

#include <iostream>
#include <string>
#include <stack>

#include "ivisitor.hpp"
#include "../irt/handlers/expressions.hpp"
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

    // TODO: FILL IN

};

}