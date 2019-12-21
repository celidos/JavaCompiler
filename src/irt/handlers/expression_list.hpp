#pragma once

#include <memory>

#include "../irt/visitors/ivisitor.hpp"
#include "expressions.hpp"

namespace irt {

class Expression;
typedef std::shared_ptr<Expression> PExpression;

class ExpressionList : public IVisitable {
public:
    ExpressionList(){}
    ExpressionList(PExpression expression) {
        addExpression(expression);
    }

    void addExpression(PExpression expression) {
        expressions_.push_back(std::move(expression));
    }
    const std::vector<PExpression>& getExpressions() const {
        return expressions_;
    }

    void accept(IVisitor *visitor) const { visitor->visit(this); }

private:
    std::vector<PExpression> expressions_;
};

typedef std::shared_ptr<ExpressionList> PExpressionList;

}
