%{
/* C++ string header, for string ops below */
#include <string>

/* Implementation of yyFlexScanner */ 
#include "src/mc_scanner.hpp"
#undef  YY_DECL
#define YY_DECL int MC::MC_Scanner::yylex( MC::MC_Parser::semantic_type * const lval, MC::MC_Parser::location_type *loc )

/* typedef to make the returns for the tokens shorter */
using token = MC::MC_Parser::token;


/* msvc2010 requires that we exclude this header file. */
#define YY_NO_UNISTD_H

/* update location on matching */
#define YY_USER_ACTION loc->step(); loc->columns(yyleng);

%}

%option debug
%option nodefault
%option yyclass="MC::MC_Scanner"
%option noyywrap
%option c++

LEX_AND        "&&"
LEX_OR         "||"
LEX_CLASS      "class"
LEX_PUBLIC     "public"
LEX_PRIVATE    "private"    
LEX_STATIC     "static"
LEX_VOID       "void"
LEX_MAIN       "main"
LEX_EXTENDS    "extends"
LEX_RETURN     "return"
LEX_IF         "if"
LEX_ELSE       "else"
LEX_WHILE      "while"
LEX_SOUT       "System.out.println"
LEX_LENGTH     "length"
LEX_NEW        "new"
LEX_THIS       "this"
LEX_TRUE       "true"
LEX_FALSE      "false"
LEX_STRING     "String"
LEX_BOOLEAN    "boolean"
LEX_INT        "int"
LEX_DIGIT      [0-9]
LEX_LETTER     [a-zA-Z_]
LEX_INTEGER_LITERAL   [1-9]{LEX_DIGIT}*|0
LEX_LOGIC_LITERAL     {LEX_TRUE}|{LEX_FALSE}
LEX_ID         {LEX_LETTER}({LEX_DIGIT}|{LEX_LETTER})*
LEX_COMMENT    \/\/.*|\/\*((.|\n)*?)\*\/
LEX_SPACE      [\n\r\t ]+
LEX_OPERATORS  [!%\(\)*+,-./;<=\[\]\{\}]

%%

%{
  yylval = lval;
%}

{LEX_INTEGER_LITERAL} {
	//std::cout << " LEX_INTEGER_LITERAL ";
    yylval->build<int>(atoi(yytext));
    return token::INTEGER_LITERAL;
}

{LEX_LOGIC_LITERAL} {
    return std::string(yytext) == "true";
}

{LEX_ID} {
    yylval->build<std::string>(yytext);
    return token::IDENTIFIER;
}

{LEX_SPACE} {
    return yytext[0];
    //std::cout << " LEX_SPACE ";
}

{LEX_OPERATORS} {
	//std::cout << " LEX_OPERATORS ";
	yylval->build<std::string>(yytext);
    return token::OPERATION_LITERAL;
}





.  { std::cout << std::endl << "UNKNOWN  " << yytext << std::endl; }

%%

