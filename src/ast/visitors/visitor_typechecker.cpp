#include "visitor_typechecker.hpp"
#include <unordered_map>
#include <vector>
#include <string>
#include <unordered_set>
#include <cassert>

namespace ast {
    void VisitorTypecheckerBuilder::visit(const Goal* goal) {
        // table_->Print();
        if (!checkCycle()) {
          return;
        }
        initTypes();
        AddParentClasses();
        // table_->Print();
        goal->getMainClass()->accept(this);
        std::unordered_set<std::string> class_names;
        for (const auto& pclass: goal->getClasses()) {
            if (class_names.find(pclass->getIdentifier()) == class_names.end()) {
                pclass->accept(this);
                class_names.insert(pclass->getIdentifier());
            }
            else {
                std::cout << "!!! Error: Redifinition of class " << pclass->getIdentifier();
                print_error_place(pclass->getPos());
            }
        }
    }

    void VisitorTypecheckerBuilder::visit(const MainClass* main_class) {
        curr_method_info_ = std::make_shared<symtable::MethodInfo>();
        main_class->getStatement()->accept(this);
    }

    void VisitorTypecheckerBuilder::visit(const Class* class_var) {

        curr_class_info_ = table_->getClass(class_var->getIdentifier());


        if (class_var->getParent() != "" && !checkType(class_var->getParent())) {
            std::cout << "!!! Error: Uknown parent class " << class_var->getParent();
            print_error_place(class_var->getPos());
        }
        std::unordered_set<std::string> vars;
        for (const auto& var: class_var->getVarDeclaration()) {
            if (vars.find(var->getIdentifier()) != vars.end()) {
                std::cout << "!!! Error: Repeted definition of variable " << var->getIdentifier();
                print_error_place(var->getPos());
            }
            vars.insert(var->getIdentifier());
            var->accept(this);
        }
        std::unordered_set<std::string> methods;
        for (const auto& method: class_var->getMethodDeclaration()) {
            if (methods.find(method->getIdentifier()) != methods.end()) {
                std::cout << "!!! Error: repeted definition of function " << method->getIdentifier();
                print_error_place(method->getPos());
            }
            methods.insert(method->getIdentifier());
            method->accept(this);
        }

    }

    void VisitorTypecheckerBuilder::visit(const VarDeclaration* var_declaration) {

        if (checkType(var_declaration->getIdentifier())) {
            std::cout << "!!! Error: variable called as class " << var_declaration->getIdentifier();
            print_error_place(var_declaration->getPos());
        }
        var_declaration->getType()->accept(this);
    }

    void VisitorTypecheckerBuilder::visit(const TypeClass* type) {
        if (!checkType(type->getType())) {
            std::cout << "!!! Error: Uknown type " << type->getType();
            print_error_place(type->getPos());
        }
    }

    void VisitorTypecheckerBuilder::visit(const MethodDeclaration* method_declaration) {
        curr_method_info_ = curr_class_info_->getMethod(method_declaration->getIdentifier());

        std::unordered_set<std::string> arg_names;
        for (const auto& type_var: method_declaration->getArgs()) {
            if (arg_names.find(type_var.second) != arg_names.end()) {
                std::cout << "!!! Error: Repeted definition of argument " << type_var.second;
                print_error_place(method_declaration->getPos());
            }
            type_var.first->accept(this);
            arg_names.insert(type_var.second);
        }
        type_stack_.push_back(method_declaration->getType()->getType());
        method_declaration->getMethodBody()->accept(this);
    }

    void VisitorTypecheckerBuilder::visit(const MethodBody* method_body) {
        method_body->getExpression()->accept(this);
        std::string curr_type = type_stack_.back();
        type_stack_.pop_back();
        std::string prev_type = type_stack_.back();
        type_stack_.pop_back();
        check_and_print_invalid_type(curr_type, prev_type, method_body->getExpression()->getPos());

        std::unordered_set<std::string> vars;
        for (const auto& var: method_body->getVarDeclaration()) {
            if (vars.find(var->getIdentifier()) != vars.end()) {
                std::cout << "!!! Error: Repeted definition of variable " << var->getIdentifier();
                print_error_place(var->getPos());
            }
            vars.insert(var->getIdentifier());
            var->accept(this);
        }


        for (const auto& statement: method_body->getStatement()) {
            statement->accept(this);
        }

    }

    void VisitorTypecheckerBuilder::visit(const ExpressionInt* expr) {
        type_stack_.push_back("INT");
    }
    void VisitorTypecheckerBuilder::visit(const ExpressionLogical* expr) {
        type_stack_.push_back("Boolean");
    }
    void VisitorTypecheckerBuilder::visit(const ExpressionId* expr) {
        if (curr_method_info_->hasVar(expr->getId())) {
            type_stack_.push_back(curr_method_info_->getVarType(expr->getId()));
        } else {
            std::cout << "!!! Error: Not defined variable " << expr->getId();
            print_error_place(expr->getPos());
            type_stack_.push_back("error_id_type");
        }
    }
    void VisitorTypecheckerBuilder::visit(const ExpressionBinaryOp* expr) {
        expr->getLeft()->accept(this);
        expr->getRight()->accept(this);
        std::string right_type = type_stack_.back();
        type_stack_.pop_back();
        std::string left_type = type_stack_.back();
        type_stack_.pop_back();
        if (expr->getOp() == "+" || expr->getOp() == "-" || expr->getOp() == "%" || expr->getOp() == "*") {
            check_and_print_invalid_type(right_type, "INT", expr->getRight()->getPos());
            check_and_print_invalid_type(left_type, "INT", expr->getLeft()->getPos());
            type_stack_.push_back("INT");
        } else if (expr->getOp() == "&&" || expr->getOp() == "||") {
            check_and_print_invalid_type(right_type, "Boolean", expr->getRight()->getPos());
            check_and_print_invalid_type(left_type, "Boolean", expr->getLeft()->getPos());
            type_stack_.push_back("Boolean");
        } else if (expr->getOp() == "<" || expr->getOp() == "==") {
            check_and_print_invalid_type(right_type, "INT", expr->getRight()->getPos());
            check_and_print_invalid_type(left_type, "INT", expr->getLeft()->getPos());
            type_stack_.push_back("Boolean");
        } else {
            std::cout << "!!! Error: Unknown operator: " << expr->getOp();
            print_error_place(expr->getPos());
            assert(false);
        }
    }

    void VisitorTypecheckerBuilder::visit(const ExpressionSquareBracket* expr) {
        expr->getEntity()->accept(this);
        std::string curr_type = type_stack_.back();
        type_stack_.pop_back();
        check_and_print_invalid_type(curr_type, "Array", expr->getEntity()->getPos());
        expr->getIndex()->accept(this);
        std::string ind_type = type_stack_.back();
        type_stack_.pop_back();
        check_and_print_invalid_type(ind_type, "INT", expr->getIndex()->getPos());
        type_stack_.push_back("INT");
    }

    void VisitorTypecheckerBuilder::visit(const ExpressionLen* expr) {
        expr->getArg()->accept(this);
        std::string curr_type = type_stack_.back();
        type_stack_.pop_back();
        check_and_print_invalid_type(curr_type, "Array", expr->getArg()->getPos());
        type_stack_.push_back("INT");
    }

    void VisitorTypecheckerBuilder::visit(const ExpressionUnaryNegation* expr) {
        expr->getArg()->accept(this);
        std::string curr_type = type_stack_.back();
        type_stack_.pop_back();
        check_and_print_invalid_type(curr_type, "Boolean", expr->getArg()->getPos());
        type_stack_.push_back("Boolean");
    }

    void VisitorTypecheckerBuilder::visit(const ExpressionThis* expr) {
        type_stack_.push_back(curr_class_info_->getName());
    }

    void VisitorTypecheckerBuilder::visit(const ExpressionNewId* expr) {
        std::string curr_type = expr->getId();
        if (!checkType(curr_type)) {
            std::cout << "!!! Error: Uknown type " << curr_type;
            print_error_place(expr->getPos());
        }
        type_stack_.push_back(curr_type);
    }

    void VisitorTypecheckerBuilder::visit(const ExpressionNewIntArray* expr) {
        expr->getCounter()->accept(this);
        std::string curr_type = type_stack_.back();
        type_stack_.pop_back();
        check_and_print_invalid_type(curr_type, "INT", expr->getCounter()->getPos());
        type_stack_.push_back("Array");
    }

    void VisitorTypecheckerBuilder::visit(const ExpressionCallFunction* expr) {
        expr->getExpr()->accept(this);
        std::string curr_type = type_stack_.back();
        type_stack_.pop_back();
        if (!checkType(curr_type)) {
            type_stack_.push_back("error_call_type");
            return;
        }
        symtable::PClassInfo curr_class = table_->getClass(curr_type);
        std::string func_name = expr->getFuncName();
        if (!curr_class->HasPublicFunc(func_name)) {
            std::cout << "!!! Error: Function " << func_name << " not found in " << curr_class->getName();
            print_error_place(expr->getPos());
            type_stack_.push_back("error_call_type");
            return;
        }
        symtable::PMethodInfo curr_method = curr_class->getMethod(func_name);
        std::string returned_type = curr_method->getReturnType();
        if (expr->getArgs().size() != curr_method->getArgsNum()) {
            std::cout << "!!! Error: Expected " << curr_method->getArgsNum() << " args, got " << expr->getArgs().size()
              << " in function " << func_name <<" of class " << curr_type;
            print_error_place(expr->getPos());
            type_stack_.push_back(returned_type);
            return;
        }
        for (int ind = 0; ind < static_cast<int>(expr->getArgs().size()); ++ind) {
            const auto& curr_arg = expr->getArgs()[ind];
            curr_arg->accept(this);
            std::string curr_type = type_stack_.back();
            type_stack_.pop_back();
            check_and_print_invalid_type(curr_type, curr_method->getParamType(ind), curr_arg->getPos());
        }
        type_stack_.push_back(returned_type);
    };

    void VisitorTypecheckerBuilder::visit(const StatementAssign* statement) {
        std::string id = statement->getIdentifier();
        if (curr_method_info_->hasVar(id)) {
            type_stack_.push_back(curr_method_info_->getVarType(id));
        } else {
            std::cout << "!!! Error: Not defined variable " << id;
            print_error_place(statement->getPos());
            return;
        }
        statement->getExpression()->accept(this);
        std::string right_type = type_stack_.back();
        type_stack_.pop_back();
        std::string left_type = type_stack_.back();
        type_stack_.pop_back();
        check_and_print_invalid_type(right_type, left_type, statement->getPos());
    }

    void VisitorTypecheckerBuilder::visit(const StatementArrayAssign* statement) {
        std::string id = statement->getIdentifier();
        if (!curr_method_info_->hasVar(id)) {
            std::cout << "!!! Error: Not defined variable " << id;
            print_error_place(statement->getPos());
            return;
        }
        check_and_print_invalid_type(curr_method_info_->getVarType(id), "Array", statement->getPos());
        statement->getExpression()->accept(this);
        std::string expr_type = type_stack_.back();
        type_stack_.pop_back();
        check_and_print_invalid_type(expr_type, "INT", statement->getExpression()->getPos());
        statement->getIndex()->accept(this);
        std::string ind_type = type_stack_.back();
        type_stack_.pop_back();
        check_and_print_invalid_type(ind_type, "INT", statement->getIndex()->getPos());
    };


    void VisitorTypecheckerBuilder::visit(const StatementPrint* statement) {
        statement->getExpression()->accept(this);
        std::string expr_type = type_stack_.back();
        type_stack_.pop_back();
        check_and_print_invalid_type(expr_type, "INT", statement->getExpression()->getPos());
    };

    void VisitorTypecheckerBuilder::visit(const StatementWhile* statement) {
        statement->getCond()->accept(this);
        std::string expr_type = type_stack_.back();
        type_stack_.pop_back();
        check_and_print_invalid_type(expr_type, "Boolean", statement->getCond()->getPos());
        statement->getBody()->accept(this);
    };

    void VisitorTypecheckerBuilder::visit(const StatementIf* statement) {
        statement->getCond()->accept(this);
        std::string expr_type = type_stack_.back();
        type_stack_.pop_back();
        check_and_print_invalid_type(expr_type, "Boolean", statement->getCond()->getPos());
        statement->getIfBody()->accept(this);
        statement->getElseBody()->accept(this);
    };

    void VisitorTypecheckerBuilder::visit(const Statements* statements) {
        for (const auto& statement: statements->getArgs()) {
            statement->accept(this);
        }
    };

    void VisitorTypecheckerBuilder::visit(const TypeInt* type) { }
    void VisitorTypecheckerBuilder::visit(const TypeBoolean* type) { };
    void VisitorTypecheckerBuilder::visit(const TypeArray* type) { };
} // namespace ast
