#pragma once

#include <memory>
#include <string>
#include "ExpressionBase.h"

class ExpressionInt: public ExpressionBase {
public:
    ExpressionInt(int value): value_(value) {}
    int GetValue() const { 
    	return value_;
    }
private:
    int value_ = 0;
};
