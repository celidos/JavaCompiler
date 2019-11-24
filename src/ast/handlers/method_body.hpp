#pragma once

#include <string>
#include <memory>

#include <yyltype.hpp>
#include <handlers/visitable.hpp>
#include <visitors/ivisitor.hpp>

#include <handlers/var_declaration.hpp>
#include <handlers/statements.hpp>

namespace ast {

class MethodBody : public IVisitable {
public:
    MethodBody(const PVarDecalartion &var_declarations,
                const PStatement &statements,
                const PExpression &expression,
            MC::YYLTYPE pos) : var_declaration_(var_declarations), statement_(statements), expr_(expression) { setPos(pos); }

    const PVarDecalartion &getVarDeclaration() const {
        return var_declaration_;
    }

    const PStatement& getStatement() const {
        return statement_;
    }

    const PExpression& getExpression() const {
        return expr_;
    }

    void accept(IVisitor *visitor, bool need_new_line = true) const { visitor->visit(this, need_new_line); }
protected:
    PVarDecalartion var_declaration_;
    PStatement statement_;
    PExpression expr_;

    void setPos(const MC::YYLTYPE pos) { pos_ = pos; }
};

typedef std::shared_ptr<MethodBody> PMethodBody;
}
