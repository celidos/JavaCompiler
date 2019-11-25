#pragma once

#include <string>
#include <vector>
#include <memory>
#include <cassert>

#include <yyltype.hpp>
#include <handlers/visitable.hpp>
#include <visitors/ivisitor.hpp>

#include <handlers/var_declaration.hpp>
#include <handlers/statements.hpp>
#include <handlers/main_class.hpp>
#include <handlers/class.hpp>

namespace ast {

class Goal : public IVisitable {
public:
    Goal(const PMainClass& main_class,
        const std::vector<PClass>& classes,
            MC::YYLTYPE pos) : main_class_(main_class), classes_(classes)  { setPos(pos);}

    const PMainClass& getMainClass() const {
        return main_class_;
    }

    const std::vector<PClass>& getClasses() const {
        return classes_;
    }

    void accept(IVisitor *visitor) const { visitor->visit(this); }
private:
    std::vector<PClass> classes_;
    PMainClass main_class_;

    void setPos(const MC::YYLTYPE pos) { pos_ = pos; }
};

typedef std::shared_ptr<Goal> PGoal;
}
