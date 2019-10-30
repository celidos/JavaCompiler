%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {MC}
%define parser_class_name {MC_Parser}

%code requires{
   #include <iostream>
   #include <cstdlib>
   #include <fstream>
   #include <string>

   #include "Expression/ExpressionBase.h"
   #include "Expression/ExpressionInt.h"
   #include "Expression/ExpressionBinaryOp.h"
   
   namespace MC {
      class MC_Driver;
      class MC_Scanner;
   }

// The following definitions is missing when %locations isn't used
# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

}

%parse-param { MC_Scanner  &scanner  }
%parse-param { MC_Driver  &driver  }

%code{
   #include <memory>
   
   /* include for all driver functions */
   #include "mc_driver.hpp"

#undef yylex
#define yylex scanner.yylex
}

%define api.value.type variant
%define parse.assert

%token<int> INTEGER_LITERAL
%token<std::string> OPERATION_LITERAL

%type<std::shared_ptr<ExpressionBase>> expr

%locations

%%

list_option: expr '\n' {std::cout << std::endl; };

expr: INTEGER_LITERAL {$$ = std::make_shared<ExpressionInt>($1); }
  | expr OPERATION_LITERAL expr {$$ = std::make_shared<ExpressionBinaryOp>($1, $3, $2); }
  ;
%%


void 
MC::MC_Parser::error( const location_type &l, const std::string &err_message )
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}
