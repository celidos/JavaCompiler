#pragma once

#pragma once

#include <string>
#include <memory>
#include <vector>

#include "statements.hpp"

#include "../irt/visitors/ivisitor.hpp"


namespace irt {

/// TODO TO REFACTOR REFACTOR

class Expression : public IVisitable {
public:
    Expression() {};
};

typedef std::shared_ptr<Expression> PExpression;

/***************************************************************************************************
 * load const
 */
class ExpressionLoadConst : public Expression {
public:
    ExpressionLoadConst(int value) : value_(value) {};

    int getValue() const {
        return value_;
    }

    void accept(IVisitor *visitor) const { visitor->visit(this); }

private:
    int value_; // TODO: later should be replaced with loading from some static table or something
};

typedef std::shared_ptr<ExpressionLoadConst> PExpressionLoadConst;

/***************************************************************************************************
 * Simple binary op
 */

class ExpressionBinaryOp : public Expression {
public:
    ExpressionBinaryOp(std::string operation_type,
                       const PExpression &left, const PExpression &right) :
        operation_(operation_type),
        left_(left),
        right_(right) {};

    const PExpression &getLeft() const { return left_; };

    const PExpression &getRight() const { return right_; };

    const std::string getOp() const { return operation_; };

    void accept(IVisitor *visitor) const { visitor->visit(this); }

private:
    std::string operation_;
    PExpression left_ = nullptr;
    PExpression right_ = nullptr;
};

typedef std::shared_ptr<ExpressionBinaryOp> PExpressionBinaryOp;

/***************************************************************************************************
 *  Function argument
 */

// TODO: недоделано
class ExpressionArg : public Expression {
public:
    ExpressionArg(const PExpression &argument) : argument_(argument) {}

    PExpression getArgument() {
        return argument_;
    }

private:
    PExpression argument_;
};

typedef std::shared_ptr<ExpressionArg> PExpressionArg;

/***************************************************************************************************
 *  Local variable
 */

class ExpressionLocal : public Expression {
public:
    ExpressionLocal(const std::string& id) : id_(id) {}

    std::string getId() {
        return id_;
    }

private:
    std::string id_;
};

typedef std::shared_ptr<ExpressionLocal> PExpressionLocal;

} // namespace irt
