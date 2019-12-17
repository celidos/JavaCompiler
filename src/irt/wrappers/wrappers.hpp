#pragma once

#include <memory>
#include "../irt/handlers/expressions.hpp"
#include "../irt/handlers/statements.hpp"
#include "../irt/handlers/memory_address.hpp"

namespace irt {

class ISubtreeWrapper {
public:
    virtual ~ISubtreeWrapper() = default;
    virtual irt::PExpression toExpression() = 0;
//    virtual irt::PStatement toStatement() = 0;
//    virtual irt::PStatement toConditional(MemoryAddress labelTrue, MemoryAddress labelFalse) = 0;
};

typedef std::shared_ptr<ISubtreeWrapper> PISubtreeWrapper;

class ExpressionWrapper : public ISubtreeWrapper {
public:
    explicit ExpressionWrapper(irt::PExpression expression)
        : expression_(expression) {}

    virtual ~ExpressionWrapper() = default;

    virtual irt::PExpression toExpression() {
        return expression_;
    };
//    irt::PStatement toStatement();
//    irt::PStatement toConditional(MemoryAddress labelTrue, MemoryAddress labelFalse);

protected:
    irt::PExpression expression_;
};

typedef std::shared_ptr<ExpressionWrapper> PExpressionWrapper;

}