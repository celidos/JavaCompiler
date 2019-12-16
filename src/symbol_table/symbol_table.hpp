#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

#include <../ast/handlers/types.hpp>
#include <../ast/handlers/var_declaration.hpp>

namespace symtable
{

/// TODO REFACTOR ADD MORE REFACTOR ADD MORE REFACTOR ADD MORE

/***************************************************************************************************
 * Method info
 */

class MethodInfo
{
public:
    MethodInfo(const std::string& name, const std::string& privacy, const std::string& type) :
        name_(name),
        privacy_(privacy),
        return_type_(type)
    { }

    void addParam(const std::string& name, const std::string& type) {
        table_vars_[name] = type;
        param_types_.push_back(type);
    }

    void addVar(const ast::PVarDeclaration& variable) {
        table_vars_[variable->getIdentifier()] = variable->getType()->getType();
    }

    void addVar(const std::string& var_name, const std::string& type) {
        table_vars_[var_name] = type;
    }

    const std::string& getVarType(const std::string& name) const {
        return table_vars_.at(name);
    }

    const std::string& getParamType(int param_id) const {
        return param_types_[param_id];
    }

    const std::string& getName() const {
        return name_;
    }
    const std::string& getPrivacy() const {
        return privacy_;
    }

    const std::string& getReturnType() const {
        return return_type_;
    }

    size_t getArgsNum() const {
        return param_types_.size();
    }

    bool hasVar(const std::string& name) const {
        return table_vars_.find(name) != table_vars_.end();
    }

    void Print() const {
        std::cout <<"    Privacy: " << privacy_ <<"\n";
        std::cout <<"    Param types: ";
        for (const auto& param_type: param_types_) {
            std::cout << param_type <<", ";
        }
        std::cout <<"\n";
        std::cout <<"    Return type: " << return_type_ <<"\n";
        std::cout <<"    vars:\n";
        for (const auto& var: table_vars_) {
            std::cout << "      " <<var.second <<" "<<var.first <<"\n";
        }
    }
private:
    bool is_public;
    std::string name_;
    std::string return_type_;
    std::string privacy_;
    std::vector<std::string> param_types_;
    std::unordered_map<std::string, std::string> table_vars_;
};

typedef std::shared_ptr<MethodInfo> PMethodInfo;

/***************************************************************************************************
 * Class info
 */

class ClassInfo
{
public:
    ClassInfo(const std::string& name): name_(name) {}
    ClassInfo(const std::string& name, const std::string& parent): name_(name), parent_(parent) {}

    void addVar(const ast::PVarDecalartion& variable) {
        table_var_[variable->getIdentifier()] = variable->getType()->getType();
    }

    void addMethod(PMethodInfo& method) {
        for (const auto& variable : table_var_) {
            if (!method->hasVar(variable.first)) {
                method->addVar(variable.first, variable.second);
            }
        }
        table_method_[method->getName()] = method;
    }

    void addParamFromParentClass(const std::string& name, const std::string& type) {
        table_var_[name] = type;
        for (auto& method: table_method_) {
             method.second->addVar(name, type);
        }
    }

    const std::string& getVariableType(const std::string& name) const {
        return table_var_.at(name);
    }

    const PMethodInfo& getMethod(const std::string& name) const {
        return table_method_.at(name);
    }

    const std::string& getName() const {
        return name_;
    }

    const std::string& getParent() const {
        return parent_;
    }

    bool HasPublicFunc(const std::string& name) const {
        return table_method_.find(name) != table_method_.end() &&
                table_method_.at(name)->getPrivacy() == "public";
    }

    const std::unordered_map<std::string, std::string>& getAllVars() const {
        return table_var_;
    }

    const std::unordered_map<std::string, PMethodInfo>& getAllMethods() const {
        return table_method_;
    }

    void Print() const {
        std::cout <<" Parent: " << parent_ <<"\n";
        std::cout <<" Methods:\n";
        for (const auto& method: table_method_) {
            std::cout <<"  method "<<method.first<<";\n";
            method.second->Print();
            std::cout <<"-----------------------------\n";
        }
    }
private:
    std::string name_;
    std::string parent_ = "";
    std::unordered_map<std::string, std::string> table_var_;
    std::unordered_map<std::string, PMethodInfo> table_method_;
};

typedef std::shared_ptr<ClassInfo> PClassInfo;

/***************************************************************************************************
 * Table Global
 */

class TableGlobal
{
public:
    explicit TableGlobal() = default;

    void addClass(const PClassInfo& new_class) {
        table_[new_class->getName()] = new_class;
        class_graph_[new_class->getParent()].push_back(new_class->getName());
    }

    PClassInfo& getClass(const std::string& name) {
        return table_[name];
    }

    const std::unordered_map<std::string, std::vector<std::string> >& getGraph() const {
        return class_graph_;
    }

    const std::unordered_map<std::string, PClassInfo>& getClasses() const {
        return table_;
    }

    void Print() const {
        for (const auto& value : table_) {
          std::cout <<"class "<< value.first <<":\n";
          value.second->Print();
          std::cout <<"==========================\n";
        }
    }
private:
    std::unordered_map<std::string, PClassInfo> table_;
    std::unordered_map<std::string, std::vector<std::string> > class_graph_;
};

typedef std::shared_ptr<TableGlobal> PTableGlobal;

} // namespace symtable
