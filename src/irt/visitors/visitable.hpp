#pragma once

#include "ivisitor.hpp"

namespace irt {

class IVisitable {
public:
    IVisitable() = default;
    virtual ~IVisitable() = default;
    virtual void accept(IVisitor *visitor) const = 0;
};

} // namespace irt