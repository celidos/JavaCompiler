#pragma once

#pragma once

#include <string>
#include <memory>
#include <vector>

#include <statements.hpp>

namespace irt {

/// TODO TO REFACTOR REFACTOR

class Expression : public Statement {
public:

    Expression() {
        return_type_ = "int";
        register_to_return_ = "smth";
    }

    std::string getReturnType() const {
        return ret_type;
    }
    std::string GetRegister() {
        return register_to_return_;
    }

    virtual void setRetType(const std::string type) {
        return_type_ = type;
    }

    ExpressionBase(const std::string &ret_type, const std::string &register_to_return)
        : return_type_(ret_type),
          register_to_return_(register_to_return) {
    }

private:
    std::string return_type_;
    std::string register_to_return_; // still unused TODO
};

typedef std::shared_ptr<Expression> PExpression;

/***************************************************************************************************
 * load const
 */
class ExpressionLoadConst : public Expression {
public:
    ExpressionLoadConst(int value) : value_(value) {};
private:
    int value_;
};



/***************************************************************************************************
 * Simple binary op
 */

class ExpressionBinaryOp : public Expression {
public:
    enum class BinaryOperationType {
        BO_PLUS = 0,
        BO_MINUS = 1
    };
    ExpressionBinaryOperation(BinaryOperationType operation_type,
            const PExpression& left, const PExpression& right) :
        operation_type_(operation_type),
        left_(left),
        right_(right)
    {};
    const PExpression & getLeft() const { return left_; };
    const PExpression & getRight() const { return right_; };
    const BinaryOperationType getOp() const { return operation_; };

private:
    BinaryOperationType operation_;
    PExpression left_ = nullptr;
    PExpression right_ = nullptr;
};

} // namespace irt