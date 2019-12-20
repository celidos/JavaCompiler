#pragma once

#include "../irt/visitors/visitable.hpp"
#include "../irt/handlers/expressions.hpp"


namespace irt {

class Expression;
typedef std::shared_ptr<Expression> PExpression;

class Statement : public IVisitable {
public:
    Statement() {};
};

typedef std::shared_ptr<Statement> PStatement;

class StatementNan : public Statement {
public:
    StatementNan() {};

    void accept(IVisitor *visitor) const { visitor->visit(this); }
};

typedef std::shared_ptr<StatementNan> PStatementNan;

class StatementMove : public Statement {
public:
    StatementMove(PExpression destination, PExpression source)
    : destination_(destination), source_(source) {};

    PExpression getDestination() const { return destination_; }

    PExpression getSource() const { return source_; }

    void accept(IVisitor *visitor) const { visitor->visit(this); }

private:
    PExpression destination_;
    PExpression source_;
};

typedef std::shared_ptr<StatementMove> PStatementMove;

//-----------------------------------------------------------------------------------------------//

class StatementExp : public Statement {
public:
    explicit StatementExp(PExpression expression) : expression_(expression) {};

    PExpression getExpression() const { return expression_; }

    void accept(IVisitor *visitor) const { visitor->visit(this); }

private:
    PExpression expression_;
};

typedef std::shared_ptr<StatementExp> PStatementExp;

class StatementSeq : public Statement {
public:
    StatementSeq(PStatement left_statement, PStatement right_statement): left_statement_(left_statement),
                                                                          right_statement_(right_statement){}

    PStatement getLeftStatement() const { return left_statement_; }
    PStatement getRightStatement() const { return right_statement_; }

    void accept(IVisitor* visitor) const { visitor->visit(this); }

private:
    PStatement left_statement_;
    PStatement right_statement_;
};

typedef std::shared_ptr<StatementSeq> PStatementSeq;

} // namespace irt