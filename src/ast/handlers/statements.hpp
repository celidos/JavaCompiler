#pragma once

#include <vector>
#include <string>
#include <memory>

#include <yyltype.hpp>
#include <visitors/visitable.hpp>
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

    const std::string& getIdentifier() const { return identifier_; }
    const PExpression& getExpression() const { return expression_; }
    void accept(IVisitor *visitor) const { visitor->visit(this); }
private:
    std::string identifier_;
    PExpression expression_;
};


typedef std::shared_ptr<StatementAssign> PStatementAssign;


class Statements : public Statement {
public:
    Statements(const std::vector<PStatement>& statements,
                                    MC::YYLTYPE pos) : args_(statements) { setPos(pos); }

    const std::vector<PStatement>& getArgs() const { return args_; }
    void accept(IVisitor *visitor) const { visitor->visit(this); }

private:
    std::vector<PStatement> args_;
};

typedef std::shared_ptr<Statements> PStatements;



class StatementIf : public Statement {
public:
    StatementIf(const PExpression& expression,
                const PStatement& body_if,
                const PStatement& body_else,
                                    MC::YYLTYPE pos) :
        condition_(expression), body_if_(body_if), body_else_(body_else)
    { setPos(pos); }

    const PExpression& getCond() const { return condition_; }
    const PStatement& getIfBody() const { return body_if_; }
    const PStatement& getElseBody() const { return body_else_; }
    void accept(IVisitor *visitor) const { visitor->visit(this); }

private:
    PExpression condition_;
    PStatement body_if_;
    PStatement body_else_;
};

typedef std::shared_ptr<StatementIf> PStatementIf;


class StatementWhile : public Statement {
public:
    StatementWhile(const PExpression& expression,
                const PStatement& body,
                                    MC::YYLTYPE pos) :
        condition_(expression), body_(body)
    { setPos(pos); }

    const PExpression& getCond() const { return condition_; }
    const PStatement& getBody() const { return body_; }
    void accept(IVisitor *visitor) const { visitor->visit(this); }

private:
    PExpression condition_;
    PStatement body_;
};

typedef std::shared_ptr<StatementWhile> PStatementWhile;


class StatementPrint : public Statement {
public:
    StatementPrint(const PExpression& expression,
                                    MC::YYLTYPE pos) : expr_(expression) { setPos(pos); }

    const PExpression& getExpression() const { return expr_; }
    void accept(IVisitor *visitor) const { visitor->visit(this); }
private:
    PExpression expr_;
};



typedef std::shared_ptr<StatementPrint> PStatementPrint;


class StatementArrayAssign : public Statement {
public:
    StatementArrayAssign(const std::string& identifier,
                        const PExpression& index,
                        const PExpression& expr,
                                    MC::YYLTYPE pos) : identifier_(identifier), index_(index),
                                                        expr_(expr) { setPos(pos); }

    const std::string& getIdentifier() const { return identifier_; }
    const PExpression& getExpression() const { return expr_; }
    const PExpression& getIndex() const { return index_; }
    void accept(IVisitor *visitor) const { visitor->visit(this); }
private:
    std::string identifier_;
    PExpression expr_;
    PExpression index_;
};

typedef std::shared_ptr<StatementArrayAssign> PStatementArrayAssign;

}

