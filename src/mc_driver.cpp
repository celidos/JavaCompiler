#include <cctype>
#include <fstream>
#include <cassert>

#include "mc_driver.hpp"

MC::MC_Driver::~MC_Driver()
{
   delete(scanner);
   scanner = nullptr;
   delete(parser);
   parser = nullptr;
}

void MC::MC_Driver::parse( const char * const filename )
{
   assert( filename != nullptr );
   std::ifstream in_file( filename );
   if( ! in_file.good() )
   {
       exit( EXIT_FAILURE );
   }
   parse_helper( in_file );
   return;
}


void MC::MC_Driver::parse_helper( std::istream &stream )
{
   
   delete(scanner);
   scanner = new MC::MC_Scanner( &stream );
   
   delete(parser); 
      
   parser = new MC::MC_Parser( (*scanner) /* scanner */, 
                                  (*this) /* driver */ );
   const int accept( 0 );
   if( parser->parse() != accept )
   {
      std::cerr << "Parse failed!!\n";
   }
   return;
}
