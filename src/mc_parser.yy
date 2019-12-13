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
   #include "src/ast/handlers/statements.hpp"
   #include "src/ast/handlers/types.hpp"
   #include "src/ast/handlers/var_declaration.hpp"
   #include "src/ast/handlers/method_body.hpp"
   #include "src/ast/handlers/method_declaration.hpp"
   #include "src/ast/handlers/main_class.hpp"
   #include "src/ast/handlers/goal.hpp"

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
%parse-param { ast::PGoal* root }

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

///

%token<int> INTEGER_LITERAL
%token<bool> LOGICAL_LITERAL
%token<std::string> OPERATION_LITERAL
%token<std::string> IDENTIFIER
%token<std::string> PRIVACY
%token RETURN
%token INT
%token ASSIGN
%token DOT_COMMA
%token LBRACKET
%token RBRACKET
%token LSQUAREBRACKET
%token RSQUAREBRACKET
%token LBRACE
%token RBRACE
%token DOT
%token LENGTH
%token UNARY_NEGATION
%token THIS
%token MAIN
%token CLASS
%token VOID
%token STRING
%token STATIC
%token END 0
%token NEW
%token BINOR
%token BINAND
%token BINLESS
%token BINGREATER

%type<ast::PExpression> expr
%type<ast::PStatement> statement
%type<ast::PType> type;
%type<ast::PVarDeclaration> var_declaration;
%type<ast::PMethodBody> method_body;
%type<ast::PMethodDeclaration> method_declaration
%type<ast::PMainClass> main_class
%type<ast::PGoal> goal
%locations

%left ASSIGN
%left BINOR
%left BINAND
%left BINLESS
%left BINGREATER

%left OPERATION_LITERAL
%right UNARY_NEGATION
%left LSQUAREBRACKET DOT LBRACKET

%%

list_option: expr '\n' {std::cout << std::endl; };
list_option: statement '\n' {std::cout << std::endl; };
list_option: type '\n' {std::cout << std::endl; };
list_option: var_declaration '\n' {std::cout << std::endl; };
list_option: method_body '\n' {std::cout << std::endl; };
list_option: method_declaration '\n' {std::cout << std::endl; };
list_option: main_class '\n' {std::cout << std::endl; };
list_option: goal '\n' {std::cout << std::endl; };

// TODO: REPLACE ROOT WITH SOMETHING ELSE

goal
      : main_class END{$$ = std::make_shared<ast::Goal>($1, LLCAST(@$)); *root = $$;}


main_class
      : CLASS IDENTIFIER LBRACE PRIVACY STATIC VOID MAIN LBRACKET STRING LSQUAREBRACKET RSQUAREBRACKET IDENTIFIER RBRACKET LBRACE statement RBRACE RBRACE
        {$$ = std::make_shared<ast::MainClass>($2, $4, $12, $15, LLCAST(@$));}

method_declaration
      : PRIVACY type IDENTIFIER LBRACKET RBRACKET method_body {$$ = std::make_shared<ast::MethodDeclaration>($1, $2, $3, $6, LLCAST(@$));}

method_body
      : LBRACE var_declaration statement RETURN expr DOT_COMMA RBRACE {$$ = std::make_shared<ast::MethodBody>($2, $3, $5, LLCAST(@$));}

var_declaration
      : type IDENTIFIER DOT_COMMA {$$ = std::make_shared<ast::VarDeclaration>($1, $2, LLCAST(@$));}

type
      : INT {$$ = std::make_shared<ast::TypeInt>(LLCAST(@$)); }

statement
      : IDENTIFIER ASSIGN expr DOT_COMMA {$$ = std::make_shared<ast::StatementAssign>($1, $3, LLCAST(@$));}

/*
      : LBRACE statement_sequence  RBRACE {$$ = std::make_shared<ast::StatementSequence>($2);}
      | RBRACE LBRACE {$$ = std::make_shared<ast::Statement>();}
statement_sequence
    : statement {std::vector<std::shared_ptr<ast::Statement> > statements; statements.push_back($1); $$ = statement; }
    | statement_sequence statement{$1.push_back($2); $$ = $1;}
*/

expr
    : INTEGER_LITERAL
        { $$ = std::make_shared<ast::ExpressionInt>    ($1, LLCAST(@$)); }
    | LOGICAL_LITERAL
        { $$ = std::make_shared<ast::ExpressionLogical>($1, LLCAST(@$)); }
    | NEW INT LSQUAREBRACKET expr RSQUAREBRACKET
        { $$ = std::make_shared<ast::ExpressionNewIntArray>($4, LLCAST(@$)); }
    | IDENTIFIER
        { $$ = std::make_shared<ast::ExpressionId>     ($1, LLCAST(@$)); }
    | NEW IDENTIFIER LBRACKET RBRACKET
        { $$ = std::make_shared<ast::ExpressionNewId>  ($2, LLCAST(@$)); }

    | LBRACKET expr RBRACKET { $$ = $2; }

    | expr OPERATION_LITERAL expr
        { $$ = std::make_shared<ast::ExpressionBinaryOp>($1, $3, $2, LLCAST(@$));}
    | expr LSQUAREBRACKET expr RSQUAREBRACKET
        { $$ = std::make_shared<ast::ExpressionSquareBracket>($1, $3, LLCAST(@$)); }
    | expr DOT LENGTH
        { $$ = std::make_shared<ast::ExpressionLen>($1, LLCAST(@$)); }

    | UNARY_NEGATION expr
        { $$ = std::make_shared<ast::ExpressionUnaryNegation>($2, LLCAST(@$)); }
    | THIS
        { $$ = std::make_shared<ast::ExpressionThis>(LLCAST(@$)); }
%%

void
MC::MC_Parser::error( const location_type &l, const std::string &err_message )
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}
