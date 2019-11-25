#pragma once

#include <string>
#include <memory>
#include <iostream>

#include <vector>
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
 * All binary operations (+, -, ^, ||, etc)
 */

class ExpressionBinaryOp: public Expression {
public:
    ExpressionBinaryOp(
        PExpression &left,
        PExpression &right,
        std::string &operation,
        const MC::YYLTYPE pos
    ) :
        left_(left), right_(right), operation_(operation) {
            setPos(pos);
        }

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

/***************************************************************************************************
 * Logical literal (true/false)
 */
class ExpressionLogical : public Expression {
public:
    ExpressionLogical(
        std::string& value,
        const MC::YYLTYPE pos
    ) : value_(value) { setPos(pos); }

    const std::string getValue() const { return value_; }
    void accept(IVisitor* visitor) const { visitor->visit(this); }
private:
    std::string value_;
};

typedef std::shared_ptr<ExpressionLogical> PExpressionLogical;

/***************************************************************************************************
 * Identifiers
 */

class ExpressionId : public Expression {
public:
    ExpressionId(
        const std::string& identifier,
        const MC::YYLTYPE pos
    ) :
        id_(identifier) { setPos(pos); }

    const std::string& getId() const { return id_; };
    void accept(IVisitor* visitor) const { visitor->visit(this); }
private:
    std::string id_;
};

typedef std::shared_ptr<ExpressionId> PExpressionId;

/***************************************************************************************************
 * Indexation a[x]
 */
class ExpressionSquareBracket: public Expression {
public:
    ExpressionSquareBracket(
        PExpression &entity,
        PExpression &index,
        const MC::YYLTYPE pos
    ) :
        entity_(entity), index_(index) { setPos(pos); }

    const PExpression & getEntity() const { return entity_; };
    const PExpression & getIndex() const { return index_; };
    void accept(IVisitor *visitor) const { visitor->visit(this); }
private:
    PExpression entity_;
    PExpression index_;
};

typedef std::shared_ptr<ExpressionSquareBracket> PExpressionSquareBracket;

/***************************************************************************************************
 * length expression
 */

class ExpressionLen: public Expression {
public:
    ExpressionLen(
        PExpression &arg,
        const MC::YYLTYPE pos
    ) :
        arg_(arg) { setPos(pos); }

    const PExpression & getArg() const { return arg_; };
    void accept(IVisitor *visitor) const { visitor->visit(this); }
private:
    PExpression arg_;
};

typedef std::shared_ptr<ExpressionLen> PExpressionLen;

/***************************************************************************************************
 * Unary prefix negation
 */

class ExpressionUnaryNegation: public Expression {
public:
    ExpressionUnaryNegation (
        PExpression &arg,
        const MC::YYLTYPE pos
    ) :
        arg_(arg) { setPos(pos); }

    const PExpression & getArg() const { return arg_; };
    void accept(IVisitor *visitor) const { visitor->visit(this); }
private:
    PExpression arg_;
};

typedef std::shared_ptr<ExpressionUnaryNegation> PExpressionUnaryNegation;

/***************************************************************************************************
 * "this" expression
 */

class ExpressionThis : public Expression {
public:
    explicit ExpressionThis(
        const MC::YYLTYPE pos
    ) { setPos(pos); }

    void accept(IVisitor* visitor) const override { visitor->visit(this); }
};

typedef std::shared_ptr<ExpressionThis> PExpressionThis;

/***************************************************************************************************
 * New Identifiers expression
 */

class ExpressionNewId : public Expression {
public:
    ExpressionNewId(const std::string& identifier,
            const MC::YYLTYPE pos
            ) :
                id_(identifier) { setPos(pos); }

    const std::string& getId() const { return id_; };
    void accept(IVisitor* visitor) const { visitor->visit(this);}
private:
    std::string id_;
};

typedef std::shared_ptr<ExpressionNewId> PExpressionNewId;

/***************************************************************************************************
 * New Int Array expression
 */

class ExpressionNewIntArray : public Expression {
public:
    ExpressionNewIntArray(
            PExpression &counter,
            const MC::YYLTYPE pos
            ) : counter_(counter) { setPos(pos); }

    const PExpression & getCounter() const { return counter_; };
    void accept(IVisitor* visitor) const { visitor->visit(this);}
private:
    PExpression counter_;
};

typedef std::shared_ptr<ExpressionNewIntArray> PExpressionNewIntArray;



class ExpressionCallFunction : public Expression {
public:
    ExpressionCallFunction(
            PExpression& expr,
            const std::string& func_name,
            const std::vector<PExpression>& args,
            const MC::YYLTYPE pos
            ) :  expr_(expr), func_name_(func_name), args_(args) { setPos(pos); }

    const PExpression & getExpr() const { return expr_; }
    const std::string & getFuncName() const { return func_name_; }
    const std::vector<PExpression> & getArgs() const { return args_; }
    void accept(IVisitor* visitor) const { visitor->visit(this);}
private:
    PExpression expr_;
    std::string func_name_;
    std::vector<PExpression> args_;
};

typedef std::shared_ptr<ExpressionCallFunction> PExpressionCallFunction;


}

