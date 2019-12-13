#pragma once

#include <string>
#include <memory>
#include <cassert>

#include <yyltype.hpp>
#include <src/ast/visitors/visitable.hpp>
#include <src/ast/visitors/ivisitor.hpp>

#include <handlers/var_declaration.hpp>
#include <handlers/statements.hpp>


namespace ast {

class MainClass : public IVisitable {
public:
    MainClass(const std::string &identifier,
                const std::string &privacy,
                const std::string &variable,
                const PStatement &statement,
            MC::YYLTYPE pos) : variable_(variable), statement_(statement), identifier_(identifier) {
        setPos(pos);
        assert(privacy == "public");
    }

    const std::string& getVariable() const {
        return variable_;
    }

    const std::string& getIdentifier() const {
        return identifier_;
    }

    const PStatement& getStatement() const {
        return statement_;
    }

    void accept(IVisitor *visitor) const { visitor->visit(this); }
protected:
    std::string identifier_;
    std::string variable_;
    PStatement statement_;

    void setPos(const MC::YYLTYPE pos) { pos_ = pos; }
};

typedef std::shared_ptr<MainClass> PMainClass;
}
