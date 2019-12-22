#pragma once

#pragma once

#include <string>
#include <memory>
#include <vector>

#include "statements.hpp"

#include "../irt/visitors/ivisitor.hpp"
#include "memory.hpp"
#include "expression_list.hpp"


namespace irt {

class Statement;

typedef std::shared_ptr<Statement> PStatement;

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
    explicit ExpressionLoadConst(int value) : value_(value) {};

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
    ExpressionBinaryOp(const std::string &operation_type,
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

class ExpressionArg : public Expression {
public:
    ExpressionArg(const std::string &argument_address) : argument_address_(argument_address) {}

    std::string getArgument() const {
        return argument_address_;
    }

    void accept(IVisitor *visitor) const { visitor->visit(this); }

private:
    std::string argument_address_;
};

typedef std::shared_ptr<ExpressionArg> PExpressionArg;

/***************************************************************************************************
 *  Local variable
 */

class ExpressionLocal : public Expression {
public:
    ExpressionLocal(const std::string &id) : id_(id) {}

    std::string getId() const {
        return id_;
    }

    void accept(IVisitor *visitor) const { visitor->visit(this); }

private:
    std::string id_;
};

typedef std::shared_ptr<ExpressionLocal> PExpressionLocal;

/***************************************************************************************************
 *  Object name
 */

class ExpressionName : public Expression {
public:
    explicit ExpressionName(const std::string &name) : name_(name) {}

    std::string getName() const {
        return name_;
    }

    void accept(IVisitor *visitor) const { visitor->visit(this); }

private:
    std::string name_;
};

typedef std::shared_ptr<ExpressionName> PExpressionName;

/***************************************************************************************************
 *  Function call
 */

class ExpressionCall : public Expression {
public:
    ExpressionCall(PExpression function, PExpressionList arguments)
        : function_(function), arguments_(arguments) {}

    PExpression getFunction() const {
        return function_;
    }

    PExpressionList getArguments() const {
        return arguments_;
    }

    void accept(IVisitor *visitor) const { visitor->visit(this); }

private:
    PExpression function_;
    PExpressionList arguments_;
};

typedef std::shared_ptr<ExpressionCall> PExpressionCall;

/***************************************************************************************************
 *  Register in memory
 */

class ExpressionTemp : public Expression {
public:
    explicit ExpressionTemp(const Register &memory_) : register_(memory_) {}

    Register getRegister() const { return register_; }

    void accept(IVisitor *visitor) const { visitor->visit(this); }

private:
    Register register_;
};

typedef std::shared_ptr<ExpressionTemp> PExpressionTemp;

/***************************************************************************************************
 */

class ExpressionMem : public Expression {
public:
    ExpressionMem(PExpression address) : address_(address) {}

    PExpression getAddress() const { return address_; }

    void accept(IVisitor *visitor) const { visitor->visit(this); }

private:
    PExpression address_;
};

typedef std::shared_ptr<ExpressionMem> PExpressionMem;

/***************************************************************************************************
 */

class ExpressionSeq : public Expression {
public:
    ExpressionSeq(PStatement statement, PExpression expression)
        : statement_(statement), expression_(expression) {}

    PStatement getStatement() const { return statement_; }

    PExpression getExpression() const { return expression_; }

    void accept(IVisitor *visitor) const { visitor->visit(this); }

private:
    PStatement statement_;
    PExpression expression_;
};

typedef std::shared_ptr<ExpressionSeq> PExpressionSeq;

} // namespace irt