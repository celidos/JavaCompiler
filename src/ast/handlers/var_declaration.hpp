#pragma once

#include <string>
#include <memory>

#include <yyltype.hpp>
#include <handlers/visitable.hpp>
#include <visitors/ivisitor.hpp>

#include <handlers/types.hpp>

namespace ast {

class VarDeclaration : public IVisitable {
public:
    VarDeclaration(const PType &type, const std::string &identifier, MC::YYLTYPE pos) : type_(type), identifier_(identifier) { setPos(pos); }

    const PType &getType() const {
        return type_;
    }

    const std::string& getIdentifier() const {
        return identifier_;
    }

    void accept(IVisitor *visitor, bool need_new_line = true) const { visitor->visit(this, need_new_line); }
protected:
    std::string identifier_;
    PType type_;

    void setPos(const MC::YYLTYPE pos) { pos_ = pos; }
};

typedef std::shared_ptr<VarDeclaration> PVarDecalartion;
}
