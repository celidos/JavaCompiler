#pragma once

#include <iostream>  // for verbose output
#include <string>
#include <unordered_map>
#include <vector>


namespace Irt {

class ConstExpressio;
class NameExpression;
class TempExpression;
class BinaryExpression;
class MemExpression;
class CallExpression;
class ESeqExpression;
class ArgExpression;
class LocalExpression;
class MoveStatement;
class ExpStatement;
class JumpStatement;
class CJumpStatement;
class SeqStatement;
class LabelStatement;
class ExpList;
class StmList;

class IVisitor {
public:
    virtual ~IVisitor() {}

    virtual void Visit(const ConstExpression *expression) = 0;
    virtual void Visit(const NameExpression *expression) = 0;
    virtual void Visit(const TempExpression *expression) = 0;
    virtual void Visit(const BinaryExpression *expression) = 0;
    virtual void Visit(const MemExpression *expression) = 0;
    virtual void Visit(const CallExpression *expression) = 0;
    virtual void Visit(const ESeqExpression *expression) = 0;
    virtual void Visit(const ArgExpression *expression) = 0;
    virtual void Visit(const LocalExpression *expression) = 0;

    virtual void Visit(const MoveStatement *statement) = 0;
    virtual void Visit(const ExpStatement *statement) = 0;
    virtual void Visit(const JumpStatement *statement) = 0;
    virtual void Visit(const CJumpStatement *statement) = 0;
    virtual void Visit(const SeqStatement *statement) = 0;
    virtual void Visit(const LabelStatement *statement) = 0;

    virtual void Visit(const ExpList *list) = 0;
    virtual void Visit(const StmList *list) = 0;
};
}