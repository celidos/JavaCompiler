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
class Statement : public IVisitable {
public:
    Statement() = default;
protected:
    void setPos(const MC::YYLTYPE pos) { pos_ = pos; }
};

typedef std::shared_ptr<Statement> PStatement;

/***************************************************************************************************
 * */

class StatementAssign : public Statement {
public:
    StatementAssign(const std::string& identifier,
                  const PExpression& expression,
                                    MC::YYLTYPE pos) : identifier_(identifier), expression_(expression) { setPos(pos); }

    std::string getIdentifier() const { return identifier_; }
    const PExpression& getExpression() const { return expression_; }
    void accept(IVisitor *visitor) const { visitor->visit(this); }
private:
    std::string identifier_;
    PExpression expression_;
};

typedef std::shared_ptr<StatementAssign> PStatementAssign;

}

