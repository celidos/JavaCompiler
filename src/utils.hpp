#pragma

namespace irt
{

class AddressGenerator
{
public:
    AddressGenerator() = default;
    const std::string genAddress() {
        return "_" + std::to_string(counter_);
    }

private:
    static int counter_;

};

}