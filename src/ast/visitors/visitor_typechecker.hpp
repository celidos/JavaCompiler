#pragma once

#include <iostream>
#include <string>
#include <stack>
#include <memory>

#include "ivisitor.hpp"
#include <handlers/expressions.hpp>
#include <handlers/statements.hpp>
#include <handlers/types.hpp>
#include <handlers/var_declaration.hpp>
#include <handlers/method_body.hpp>
#include <handlers/method_declaration.hpp>
#include <handlers/main_class.hpp>
#include <handlers/goal.hpp>
#include <unordered_map>
#include <vector>
#include <yyltype.hpp>

#include <../symbol_table/symbol_table.hpp>

namespace ast {

    class VisitorTypecheckerBuilder : public IVisitor {
    public:
        VisitorTypecheckerBuilder(symtable::PTableGlobal symb_table) : table_(symb_table) {}

        bool DFScheckCycle(const std::unordered_map<std::string, std::vector<std::string> >& graph,  const std::string& vert,
                           std::unordered_map<std::string, int>& used) const {
            used[vert] = 1;
            if (graph.find(vert) == graph.end()) {
                used[vert] = 2;
                return true;
            }
            for (const auto& chld: graph.at(vert)) {
                if (used[chld] == 2) {
                  continue;
                }
                if (used[chld] == 1) {
                  std::cout << "Error: cycle in dependecies: " <<chld <<" -> " << vert;
                  return false;
                }
                if (!DFScheckCycle(graph, chld, used)) {
                  std::cout <<" -> "<< vert;
                  return false;
                }
            }
            used[vert] = 2;
            return true;
        }

        bool checkCycle() const {
            std::unordered_map<std::string, int> used;
            const std::unordered_map<std::string, std::vector<std::string> >& graph = table_->getGraph();
            for (const auto& vert: graph) {
                if (used[vert.first] == 0) {
                  std::cout << vert.first <<"\n";
                  if (!DFScheckCycle(graph, vert.first, used)) {
                      std::cout <<"\n";
                      return false;
                  }
                }
            }
            return true;
        }

    private:
        std::shared_ptr<symtable::TableGlobal> table_;

        void visit(const ExpressionInt* expr);
        void visit(const ExpressionBinaryOp* expr);
        void visit(const ExpressionLogical* expr);
        void visit(const ExpressionId* expr);
        void visit(const ExpressionSquareBracket* expr);
        void visit(const ExpressionLen* expr);
        void visit(const ExpressionUnaryNegation* expr);
        void visit(const ExpressionThis* expr);
        void visit(const StatementAssign* statement);
        void visit(const TypeInt* type);
        void visit(const TypeBoolean* type);
        void visit(const TypeArray* type);
        void visit(const TypeClass* type);
        void visit(const VarDeclaration* var_declaration);
        void visit(const MethodBody* method_body);
        void visit(const MethodDeclaration* method_declaration);
        void visit(const Class* class_var);
        void visit(const MainClass* main_class);
        void visit(const Goal* goal);
        void visit(const ExpressionNewId* expr);
        void visit(const ExpressionNewIntArray* expr);
        void visit(const ExpressionCallFunction* expr);
        void visit(const StatementArrayAssign* statement);
        void visit(const StatementPrint* statement);
        void visit(const StatementWhile* statement);
        void visit(const StatementIf* statement);
        void visit(const Statements* statement);
    };

} // namespace ast;
