#pragma once

#include <string>
#include <map>
#include <vector>
#include <memory>

#include <../ast/handlers/types.hpp>
#include <../ast/handlers/var_declaration.hpp>

namespace symtable
{

/***************************************************************************************************
 * variable info
 */

class VariableInfo
{
    std::string type_name;
};

typedef std::shared_ptr<VariableInfo> PVariableInfo;

/***************************************************************************************************
 * Method info
 */

class MethodInfo
{
public:
    MethodInfo(const std::string& name) : name_(name) {

    }

    void addVar(const int position, const ast::PVarDeclaration& variable) {
        table_[variable->getName()] = {variable->getType()};
    }

    PVariableInfo getVar(const std::string& name) {
        return table_[name];
    }

    std::string getName() {
        return name_;
    }

private:
    std::string name_;
    std::string type_name_;
    std::map<std::string, PVariableInfo> table_;
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