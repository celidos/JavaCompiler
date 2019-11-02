%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {MC}
%define api.parser.class {MC_Parser}

// %define api.location.type {master::location}
// %code requires { #include "src/ast/yyltype.hhp" }

%code requires{
   #include <iostream>
   #include <cstdlib>
   #include <fstream>
   #include <string>

   #include "src/ast/handlers/expressions.hpp"

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
%parse-param { std::shared_ptr<ast::Expression>* root  }

%code{
   #include <memory>

   /* include for all driver functions */
   #include "src/mc_driver.hpp"

   MC::YYLTYPE LLCAST(MC::location x) { return MC::YYLTYPE({(x.begin.line), (x.begin.column), (x.end.line), (x.end.column)} ); }

#undef yylex
#define yylex scanner.yylex
}

%define api.value.type variant
%define parse.assert

%token<int> INTEGER_LITERAL
%token<bool> LOGICAL_LITERAL
%token<std::string> OPERATION_LITERAL
%token<std::string> IDENTIFIER
%token LBRACKET
%token RBRACKET
%token LSQUAREBRACKET
%token RSQUAREBRACKET
%token LBRACE
%token RBRACE
%token DOT
%token LENGTH
%token UNARY_NEGATION

%type<std::shared_ptr<ast::Expression>> expr

%locations

%%

list_option: expr '\n' {std::cout << std::endl; };

expr
    : INTEGER_LITERAL
        { $$ = std::make_shared<ast::ExpressionInt>    ($1, LLCAST(@$)); }
    | LOGICAL_LITERAL
        { $$ = std::make_shared<ast::ExpressionLogical>($1, LLCAST(@$)); }
    | IDENTIFIER
        { $$ = std::make_shared<ast::ExpressionId>     ($1, LLCAST(@$)); }

    | LBRACKET expr RBRACKET { $$ = $2; }

    | expr OPERATION_LITERAL expr
        { $$ = std::make_shared<ast::ExpressionBinaryOp>($1, $3, $2, LLCAST(@$)); *root = $$; }
    | expr LSQUAREBRACKET expr RSQUAREBRACKET
        { $$ = std::make_shared<ast::ExpressionSquareBracket>($1, $3, LLCAST(@$)); }
    | expr DOT LENGTH
        { $$ = std::make_shared<ast::ExpressionLen>($1, LLCAST(@$)); }

    | UNARY_NEGATION expr
        { $$ = std::make_shared<ast::ExpressionUnaryNegation>($2, LLCAST(@$)); }
        
%%

void 
MC::MC_Parser::error( const location_type &l, const std::string &err_message )
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}
