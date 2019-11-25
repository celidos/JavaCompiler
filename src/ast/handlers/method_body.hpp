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
    MethodBody(const std::vector<PVarDecalartion> &var_declarations,
                const std::vector<PStatement> &statements,
                const PExpression &expression,
            MC::YYLTYPE pos) : var_declaration_(var_declarations), statement_(statements), expr_(expression) { setPos(pos); }


    const std::vector<PVarDecalartion>& getVarDeclaration() const {
        return var_declaration_;
    }

    const std::vector<PStatement>& getStatement() const {
        return statement_;
    }

    const PExpression& getExpression() const {
        return expr_;
    }

    void accept(IVisitor *visitor) const { visitor->visit(this); }
private:
    std::vector<PVarDecalartion> var_declaration_;
    std::vector<PStatement> statement_;
    PExpression expr_;

    void setPos(const MC::YYLTYPE pos) { pos_ = pos; }
};

typedef std::shared_ptr<MethodBody> PMethodBody;
}
