#pragma once

#include <string>
#include <map>
#include <vector>
#include <memory>

#include <../ast/handlers/types.hpp>
#include <../ast/handlers/var_declaration.hpp>

namespace symtable
{

/// TODO REFACTOR ADD MORE REFACTOR ADD MORE REFACTOR ADD MORE

/***************************************************************************************************
 * variable info
 */

class VariableInfo
{
public:
    VariableInfo(const std::string type) : type_(type) { };
    std::string getType() const { return type_; }
private:
    std::string type_;
};

typedef std::shared_ptr<VariableInfo> PVariableInfo;

/***************************************************************************************************
 * Method info
 */

class MethodInfo
{
public:
    MethodInfo(const std::string& name) :
        name_(name)
    { }

    void addVar(const int position, const ast::PVarDeclaration& variable) {
        table_vars_[variable->getIdentifier()] = std::make_shared<VariableInfo>(variable->getType()->getType());
    }

    void addVar(const int position, const std::string& name_, const std::string& variable) {
        table_vars_[name_] = std::make_shared<VariableInfo>(variable);
    }

    PVariableInfo getVar(const std::string& name) {
        return table_vars_[name];
    }

    std::string getName() const {
        return name_;
    }

    std::string getReturnType() const {
        return return_type_;
    }

    int getSize() const {
        return table_vars_.size();
    }

private:
    bool is_public;
    std::string name_;
    std::string return_type_;
    std::map<std::string, PVariableInfo> table_params_;
    std::map<std::string, PVariableInfo> table_vars_;
};

typedef std::shared_ptr<MethodInfo> PMethodInfo;

/***************************************************************************************************
 * Class info
 */

class ClassInfo
{
public:
    ClassInfo(const std::string& name): name_(name) {
        // TODO
    }

    void addVar(const int position, const ast::PVarDeclaration& variable) {
        table_var_[variable->getIdentifier()] = std::make_shared<VariableInfo>(variable->getType()->getType());
    }

    void addMethodTable(const int position, const PMethodInfo& method) {
        table_method_[method->getName()] = method;
    }

    PVariableInfo getVariable(const std::string& name) {
        return table_var_[name];
    }

    PMethodInfo getMethod(const std::string& name, const std::vector<std::string>& variable_list) {
        // TODO
    }

    std::string getName() {
        return name_;
    }
private:
    std::string name_;
    std::map<std::string, PVariableInfo> table_var_;
    std::map<std::string, PMethodInfo> table_method_;
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
    }

    PClassInfo getClass(const std::string& name) {
        return table_[name];
    }

private:
    std::map<std::string, PClassInfo> table_;
};

} // namespace symtable