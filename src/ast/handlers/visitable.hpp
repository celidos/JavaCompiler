#pragma once

#include <yyltype.hpp>
#include <visitors/ivisitor.hpp>

namespace ast {

class IVisitable {
public:
    IVisitable() = default;
    virtual ~IVisitable() = default;
    virtual void accept(IVisitor* visitor) const = 0;

    MC::YYLTYPE getPos() const { return pos_; };
protected:
    MC::YYLTYPE pos_;
};

}

//#endif //JAVACOMPILER_VISITABLE_HPP
