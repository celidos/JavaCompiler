#ifndef JAVACOMPILER_VISITABLE_HPP
#define JAVACOMPILER_VISITABLE_HPP

#include <string>
#include <memory>

#include <yyltype.hpp>
#include <handlers/visitable.hpp>
#include <visitors/ivisitor.hpp>

namespace ast {

/***************************************************************************************************
 * Base class for expression handler. It is the parent for tree nodes, therefore it is
 * inherited from Visitable.
 */
class Expression : public IVisitable {
public:
    Expression() = default;
protected:
    void setPos(const MC::YYLTYPE pos) { pos_ = pos; }
};

typedef std::shared_ptr<Expression> PExpression;

/***************************************************************************************************
 * Numeric expressions.
 */
class ExpressionInt : public Expression {
public:
    ExpressionInt(int &value, MC::YYLTYPE pos) : value_(value) { setPos(pos); }

    int getValue() const { return value_; }

    void accept(IVisitor *visitor) const { visitor->visit(this); }
private:
    int value_;
};

typedef std::shared_ptr<ExpressionInt> PExpressionInt;

/***************************************************************************************************
 * All binary operations.
 */

class ExpressionBinaryOp: public Expression {
public:
    ExpressionBinaryOp(
        PExpression &left,
        PExpression &right,
        std::string &operation,
        const MC::YYLTYPE pos
    ) :
        left_(left), right_(right), operation_(operation) { setPos(pos); }

    const PExpression & getLeft() const { return left_; };
    const PExpression & getRight() const { return right_; };
    const std::string & getOp() const { return operation_; };

    void accept(IVisitor *visitor) const { visitor->visit(this); }
private:
    std::string operation_;
    PExpression left_;
    PExpression right_;
};

typedef std::shared_ptr<ExpressionBinaryOp> PExpressionBinaryOp;

}

#endif