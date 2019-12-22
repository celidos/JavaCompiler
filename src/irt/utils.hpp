#pragma once

#include <string>

namespace irt
{

class AddressGenerator
{
public:
    AddressGenerator() = default;
    static const std::string genAddress() {
        ++counter_;
        return "_" + std::to_string(counter_);
    }

private:
    static int counter_;
};

}