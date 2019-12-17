#pragma once

#include <../irt/visitors/visitable.hpp>


namespace irt {

class Statement : public IVisitable {
    Statement() {};
};

typedef std::shared_ptr<Statement> PStatement;

} // namespace irt