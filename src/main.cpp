#include <iostream>

#include "mc_driver.hpp"

int main (const int argc, const char **argv)
{
    if (argc != 2) {
         return 1;
    }

    MC::MC_Driver driver;
    driver.parse(argv[1]);

    std::cout << "Parsing finished" << std::endl;
    return 0;
}
