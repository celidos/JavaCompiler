#pragma once

#include <yyltype.hpp>
#include "ivisitor.hpp"

class IVisitable {
public:
    IVisitable() = default;
    virtual ~IVisitable() = default;
    virtual void accept(ast::IVisitor *visitor) const = 0;

    MC::YYLTYPE getPos() const { return pos_; };
protected:
    MC::YYLTYPE pos_;
};