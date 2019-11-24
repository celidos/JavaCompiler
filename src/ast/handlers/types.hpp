#pragma once

#include <string>
#include <memory>

#include <yyltype.hpp>
#include <handlers/visitable.hpp>
#include <visitors/ivisitor.hpp>

#include <handlers/expressions.hpp>

namespace ast {

/***************************************************************************************************
 * Base class for expression handler. It is the parent for tree nodes, therefore it is
 * inherited from Visitable.
 */
class Type : public IVisitable {
public:
    Type() = default;
protected:
    void setPos(const MC::YYLTYPE pos) { pos_ = pos; }
};

typedef std::shared_ptr<Type> PType;

/***************************************************************************************************
 * */

class TypeInt : public Type {
public:
    TypeInt(MC::YYLTYPE pos) { setPos(pos); }

    std::string getType() const { return "INT"; }
    void accept(IVisitor *visitor) const { visitor->visit(this); }
};

typedef std::shared_ptr<TypeInt> PTypeInt;

}

