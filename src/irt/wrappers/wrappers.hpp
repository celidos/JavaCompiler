#pragma once

#include <cassert>
#include <memory>
#include "../irt/handlers/expressions.hpp"
#include "../irt/handlers/statements.hpp"
#include "../irt/handlers/memory.hpp"


namespace irt {

class ISubtreeWrapper {
public:
    virtual ~ISubtreeWrapper() = default;
    virtual irt::PExpression toExpression() = 0;
    virtual irt::PStatement toStatement() = 0;
//    virtual irt::PStatement toConditional(MemoryAddress labelTrue, MemoryAddress labelFalse) = 0;
};

typedef std::shared_ptr<ISubtreeWrapper> PISubtreeWrapper;

class ExpressionWrapper : public ISubtreeWrapper {
public:
    explicit ExpressionWrapper(irt::PExpression expression) : expression_(expression) {}

    virtual ~ExpressionWrapper() = default;

    virtual irt::PExpression toExpression() {
        return expression_;
    };
    irt::PStatement toStatement(){
        irt::StatementExp statement(expression_);
        return std::make_shared<irt::StatementExp>(statement);
    }
//    irt::PStatement toConditional(MemoryAddress labelTrue, MemoryAddress labelFalse);

protected:
    irt::PExpression expression_;
};

typedef std::shared_ptr<ExpressionWrapper> PExpressionWrapper;

class StatementWrapper : public ISubtreeWrapper {
public:
    explicit StatementWrapper(irt::PStatement statement) : statement_(statement) {}

    virtual ~StatementWrapper() = default;

    virtual irt::PExpression toExpression(){
        assert(false);
    };
    virtual irt::PStatement toStatement(){
        return statement_;
    };
//    virtual std::unique_ptr<const Statement> ToConditional(
//        MemoryAddress labelTrue, MemoryAddress labelFalse){
//        assert(false);
//    }

private:
    irt::PStatement statement_;
};

typedef std::shared_ptr<StatementWrapper> PStatementWrapper;

}  // namespace irt
