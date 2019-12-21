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

/***************************************************************************************************
 * Method info
 */

class MethodInfo
{
public:
    explicit MethodInfo() = default;
    MethodInfo(const std::string& name, const std::string& privacy, const std::string& type) :
        name_(name), return_type_(type), privacy_(privacy)
    { }

    void addParam(const std::string& name, const std::string& type) {
        table_vars_[name] = type;
        param_types_.push_back(type);
        address_table_[name] = "argument_" + std::to_string(curr_arg++);
    }

    void addVar(const ast::PVarDeclaration& variable) {
        table_vars_[variable->getIdentifier()] = variable->getType()->getType();
        address_table_[variable->getIdentifier()] = "local_" + variable->getIdentifier();
    }

    void addVar(const std::string& var_name, const std::string& type, const int number_of_var = -1) {
        if (number_of_var == -1) {
            address_table_[var_name] = "local_" + var_name;
        } else {
            address_table_[var_name] = "address_" + std::to_string(number_of_var * 4);
        }
        table_vars_[var_name] = type;
    }

    const std::string& getVarType(const std::string& name) const {
        return table_vars_.at(name);
    }

    const std::string& getParamType(int param_id) const {
        return param_types_[param_id];
    }

    const std::string& getAddress(const std::string& name) const {
        return address_table_.at(name);
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
            std::cout << "      " <<var.second <<" "<<var.first << " " << address_table_.at(var.first)<<"\n";
        }
    }
private:
    bool is_public = false;
    int curr_arg = 0;
    std::string name_;
    std::string return_type_;
    std::string privacy_;
    std::vector<std::string> param_types_;
    std::unordered_map<std::string, std::string> table_vars_;
    std::unordered_map<std::string, std::string> address_table_;
};

typedef std::shared_ptr<MethodInfo> PMethodInfo;

/***************************************************************************************************
 * Class info
 */

class ClassInfo
{
public:
    explicit ClassInfo() = default;
    explicit ClassInfo(const std::string& name): name_(name) { };
    ClassInfo(const std::string& name, const std::string& parent): name_(name), parent_(parent) { };

    void addVar(const ast::PVarDecalartion& variable) {
        table_var_[variable->getIdentifier()] = variable->getType()->getType();
        address_table_[variable->getIdentifier()] = arg_num_++;
    }

    void addMethod(PMethodInfo& method) {
        for (const auto& variable : table_var_) {
            if (!method->hasVar(variable.first)) {
                method->addVar(variable.first, variable.second, address_table_.at(variable.first));
            }
        }
        table_method_[method->getName()] = method;
    }

    void addParentClass(const  std::shared_ptr<ClassInfo>& pclass) {
        for (const auto& arg: pclass->getAllVars()) {
            if (table_var_.find(arg.first) == table_var_.end()) {
                table_var_[arg.first] = arg.second;
                address_table_[arg.first] = arg_num_ + pclass->getAddress(arg.first);
                for (auto& method: table_method_) {
                    method.second->addVar(arg.first, arg.second, address_table_[arg.first]);
                }
            }
        }
    }

    int getAddress(const std::string& name) const {
        return address_table_.at(name);
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
    int arg_num_ = 0;
    std::unordered_map<std::string, int> address_table_;
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
