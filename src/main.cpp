#include <iostream>

#include "mc_driver.hpp"

int main(const int argc, const char **argv)
{
    if (argc != 4) {
        std::cout << "javacompiler called with wrong parameters, expected 3, got "
            << argc - 1 << std::endl;
        return 1;
    }

    MC::MC_Driver driver;
    driver.parse(argv[1], argv[2], argv[3]);

    std::cout << "Parsing finished" << std::endl;
    return 0;
}
