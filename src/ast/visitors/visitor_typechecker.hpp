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
#include <unordered_set>
#include <yyltype.hpp>

#include <../symbol_table/symbol_table.hpp>

namespace ast {

    class VisitorTypecheckerBuilder : public IVisitor {
    public:
        VisitorTypecheckerBuilder(symtable::PTableGlobal symb_table) : table_(symb_table) {}

        void print_error_place(const MC::YYLTYPE& place) {
            std::cout <<  " (in line "<<place.first_line << " and in position "
                << place.first_column << ")\n";
            no_mistakes_ = false;
        }

        void check_and_print_invalid_type(const std::string& curr_type,
                                          const std::string& expected_type,
                                          const MC::YYLTYPE& place) {
            if (!CompareTypes(expected_type, curr_type)) {
                std::cout << "!!! Error: Wrong type: " << curr_type <<"; expected: " << expected_type;
                print_error_place(place);
            }
        }

        bool check_errors() const { return no_mistakes_; }
    private:
        bool no_mistakes_ = true;
        bool curr_expr_may_be_lvalue = false;
        std::shared_ptr<symtable::TableGlobal> table_;
        std::unordered_set<std::string> types_;
        std::vector<std::string> type_stack_;
        symtable::PClassInfo curr_class_info_;
        symtable::PMethodInfo curr_method_info_;
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
                  std::cout << "!!! Error: cycle in dependecies: " <<chld <<" -> " << vert;
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

        bool checkCycle() {
            std::unordered_map<std::string, int> used;
            const std::unordered_map<std::string, std::vector<std::string> >& graph = table_->getGraph();
            for (const auto& vert: graph) {
                if (used[vert.first] == 0) {
                  if (!DFScheckCycle(graph, vert.first, used)) {
                      std::cout << "\n";
                      no_mistakes_ = false;
                      return false;
                  }
                }
            }
            return true;
        }

        void initTypes() {
            for (const auto& vert: table_->getClasses()) {
                types_.insert(vert.first);
            }
        }

        bool checkType(const std::string& type) const {
            return types_.find(type) != types_.end();
        }

        bool hasChild(const std::string& parent, const std::string& chld) const {
            if (parent == chld) {
                return true;
            }
            const std::unordered_map<std::string, std::vector<std::string> >& graph = table_->getGraph();
            if (graph.find(parent) == graph.end()) {
                return false;
            }
            for (const auto& vert: graph.at(parent)) {
                if (hasChild(vert, chld)) {
                    return true;
                }
            }
            return false;
        }

        void AddParentClassesForClass(symtable::PClassInfo& pclass) {
            if (pclass->getParent() != "") {
                AddParentClassesForClass(table_->getClass(pclass->getParent()));
                pclass->addParentClass(table_->getClass(pclass->getParent()));
            }
        }

        void AddParentClasses() {
            for (auto& pclass : table_->getClasses()) {
                AddParentClassesForClass(table_->getClass(pclass.first));
            }
        }
        bool CompareTypes(const std::string& const_type, const std::string& type_may_be_casted) const {
            if (const_type == type_may_be_casted) {
                return true;
            }
            if (!checkType(const_type) || !checkType(type_may_be_casted)) {
                return false;
            }
            return hasChild(const_type, type_may_be_casted);
        }

    };

} // namespace ast;
