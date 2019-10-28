#include <iostream>
#include <cstdlib>
#include <cstring>

#include "mc_driver.hpp"

int 
main( const int argc, const char **argv )
{
	if(argc != 2){
		return 1;
	}
	
	MC::MC_Driver driver;
	// чтение из файла
	driver.parse( argv[1] );

    std::cout << "Successful Parsing!" << std::endl;
    return 0;
}
