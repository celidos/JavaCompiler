#pragma once

#include <memory>
#include <string>
#include "ExpressionBase.h"

class ExpressionBinaryOp: public ExpressionBase {
public:
    ExpressionBinaryOp(const std::shared_ptr<ExpressionBase> &left, const std::shared_ptr<ExpressionBase> &right,
                    std::string operation) : left(left), right(right), operation(operation) {}

    const std::shared_ptr<ExpressionBase>& GetLeft() const { return left; };
    const std::shared_ptr<ExpressionBase>& GetRight() const { return right; };
    const std::string& GetOperation() const { return operation; };
private:
    std::shared_ptr<ExpressionBase> left, right;
    std::string operation;

};
