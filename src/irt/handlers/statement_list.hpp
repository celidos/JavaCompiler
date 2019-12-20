#pragma once

#include "../irt/visitors/ivisitor.hpp"
#include "statements.hpp"


namespace irt {

class Statement;

typedef std::shared_ptr<Statement> PStatement;

class StatementList : public IVisitable {
public:
    StatementList(const std::vector<PStatement> &statements) : statements_(statements) { }

    StatementList(PStatement statement) {
        addStatement(statement);
    }

    void addStatement(PStatement statement) {
        statements_.push_back(statement);
    }

    const std::vector<PStatement> &getStatements() const {
        return statements_;
    }

    void accept(IVisitor *visitor) const { visitor->visit(this); }

private:
    std::vector<PStatement> statements_;
};

typedef std::shared_ptr<StatementList> PStatementList;

}
