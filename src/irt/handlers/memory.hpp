#pragma once

#include <string>

class Register {
public:
    Register() : register_("register_" + std::to_string(counter_++)) {}

    operator std::string() const {
        return register_;
    }

private:
    std::string register_;
    static int counter_;
};

class MemoryAddress {
public:
    MemoryAddress() : address_("memory_address_" + std::to_string(counter_++)) {}

    operator std::string() const{
        return address_;
    }

private:
    std::string address_;
    static int counter_;
};
