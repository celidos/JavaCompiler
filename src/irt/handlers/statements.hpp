#pragma once

#include "../irt/visitors/visitable.hpp"
#include "../irt/handlers/expressions.hpp"

namespace irt {

class Expression;
typedef std::shared_ptr<Expression> PExpression;

/***************************************************************************************************
 * Statement
 *
 * Base class
 */

class Statement : public IVisitable {
public:
    Statement() {};
};

typedef std::shared_ptr<Statement> PStatement;

/***************************************************************************************************
 * Statement Nan
 */

class StatementNan : public Statement {
public:
    StatementNan() = default;

    void accept(IVisitor *visitor) const { visitor->visit(this); }
};

typedef std::shared_ptr<StatementNan> PStatementNan;

/***************************************************************************************************
 * MOVE
 */

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

/***************************************************************************************************
 * Statement to Exp Converter
 *
 * Used in Wrapper
 */

class StatementExp : public Statement {
public:
    explicit StatementExp(PExpression expression) : expression_(expression) {};

    PExpression getExpression() const { return expression_; }

    void accept(IVisitor *visitor) const { visitor->visit(this); }

private:
    PExpression expression_;
};

typedef std::shared_ptr<StatementExp> PStatementExp;

/***************************************************************************************************
 * SEQ
 *
 * Sequence of statements
 */

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

/***************************************************************************************************
 * LABEL
 *
 * Creates possible destination for jump
 */

class StatementLabel : public Statement {
public:
    explicit StatementLabel(const std::string& label) : label_(label) { };
    const std::string& getLabel() const { return label_; }
    void accept(IVisitor* visitor) const { visitor->visit(this); };

private:
    std::string label_;
};

typedef std::shared_ptr<StatementLabel> PStatementLabel;

/***************************************************************************************************
 * JUMP
 *
 * Acts like goto operator
 */

class StatementJump : public Statement {
public:
    explicit StatementJump(const std::string& target) : target_(target) { };
    explicit StatementJump(const PStatementLabel target) : target_(target->getLabel()) { };
    ~StatementJump() = default;

    const std::string& getTarget() const { return target_; }
    void accept(IVisitor* visitor) const { visitor->visit(this); }

private:
    const std::string& target_;
};

typedef std::shared_ptr<StatementJump> PStatementJump;

/***************************************************************************************************
 * CJUMP
 *
 * Conditional jump
 */

class StatementCJump : public Statement {
public:

    StatementCJump(const std::string& operation,
        const PExpression left, const PExpression right,
        const std::string& label_true, const std::string& label_false) :
        operation_(operation),
        left_(left),
        right_(right),
        label_true_(label_true),
        label_false_(label_false)
    {};
    ~StatementCJump() = default;

    PExpression getLeft() const { return left_; }
    PExpression getRight() const { return right_; }
    const std::string& getTrueLabel() const { return label_true_; }
    const std::string& getFalseLabel() const { return label_false_; }
    const std::string& getOperation() const { return operation_; }

    void accept(IVisitor* visitor) const { visitor->visit(this); }

private:
    const std::string& operation_;
    PExpression left_;
    PExpression right_;
    const std::string& label_true_;
    const std::string& label_false_;

};

} // namespace irt