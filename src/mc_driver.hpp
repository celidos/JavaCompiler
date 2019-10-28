#pragma once

#include <string>
#include <cstddef>
#include <istream>

#include "mc_scanner.hpp"
#include "mc_parser.tab.hh"

namespace MC{

class MC_Driver{
public:
   MC_Driver() = default;

   virtual ~MC_Driver();


   // читаем из файла
   void parse( const char * const filename );
private:

   void parse_helper( std::istream &stream );
   MC::MC_Parser  *parser  = nullptr;
   MC::MC_Scanner *scanner = nullptr;
};

}
