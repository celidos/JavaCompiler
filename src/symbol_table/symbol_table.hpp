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
///
/* inline std::string GetTypeName(const std::shared_ptr<Type>& type) {
    if (type->GetType() == Type::EType::STANDARD_TYPE_ARRAY) {
        return "int[]";
    }
    return type->getTypeName();
} */

inline std::vector<std::string> GetTypeName(const std::vector<std::pair<std::shared_ptr<Type>, std::string>>& args) {
    std::vector<std::string> types;
    for (const auto& type: args) {
        types.push_back(GetTypeName(type.first));
    }
    return types;
}

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
    MethodInfo(const std::string& name, const std::shared_ptr<Type>& type) :
        name_(name)
    {

    }

    void addVar(const int position, const ast::PVarDeclaration& variable) {
        table_[variable->getName()] = std::make_shared<VariableInfo>(variable->getType());
    }

    void addVar(const int position, const std::string& name_, const std::string& variable) {
        table_[name_] = std::make_shared<SimpleVariable>(position, var);
    }

    PVariableInfo getVar(const std::string& name) {
        return table_[name];
    }

    std::string getName() const {
        return name_;
    }

    std::string getReturnType() const {
        return return_type_;
    }

    int getSize() const {
        return table_.size();
    }

private:
    bool is_public;
    std::string name_;
    std::string return_type_;
    std::map<std::string, PvariableInfo> table_params_;
    // std::map<std::string, PVariableInfo> table_vars_;
};

typedef std::shared_ptr<MethodInfo> PMethodInfo;

/***************************************************************************************************
 * Class info
 */

class ClassInfo
{
    ClassInfo(const std::string& name): name_(name) {

    }

    void addVar(const int position, const PVarDeclaration& variable) {
        table_var_[variable->getName()] = {variable->getType()};
    }

    void addMethodTable(const int position, const PMethodInfo& method) {
        table_method_[method->getName()] = method;
    }

    PVariableInfo getVariable(const std::string& name) {
        return table_var_[name];
    }

    PMethodInfo getMethod(const std::string& name, const std::vector<std::string>& variable_list) {
        // ??
    }

    std::string GetName() {
        return name_;
    }
private:
    std::string name_;
    std::parent_class_name_;
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

    void addVar(const PClassInfo& table) {
        table_[class_table->GetName()] = class_table;
    }

    PClassInfo getClass(const std::string& name) {
        return table[name];
    }

private:
    std::map<std::string, PClassInfo> table_;
};

} // namespace symtable