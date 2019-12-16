#pragma once

#include <string>

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
