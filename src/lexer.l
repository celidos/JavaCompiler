%{
#include <iostream>
#include "mini_scanner.h"
%}

%option c++
%option noyywrap
%option yyclass="MiniScanner"

%{
    int lexem_iterator = 0;
%}

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
LEX_STRING     "String"
LEX_BOOLEAN    "boolean"
LEX_INT        "int"
LEX_DIGIT      [0-9]
LEX_LETTER     [a-zA-Z_]
LEX_INTEGER_LITERAL   [1-9]{LEX_DIGIT}*|0
LEX_LOGIC_LITERAL     "True"|"False"
LEX_ID         {LEX_LETTER}({LEX_DIGIT}|{LEX_LETTER})*
LEX_COMMENT    \/\/.*|\/\*((.|\n)*?)\*\/
LEX_SPACE      [\n\r\t ]+
LEX_OPERATORS  [!%\(\)*+,-./;<=\[\]\{\}]

LEX_OPERATORS  "+"|"-"|"*"|"/"|"%"|LEX_AND|LEX_OR
LEX_ASSIGN     "="

LEX_DOT_COMMA ";"
LEX_DOT "."
LEX_LBRACKET "("
LEX_RBRACKET ")"
LEX_LSQUAREBRACKET "["
LEX_RSQUAREBRACKET "]"
LEX_LBRACE "{"
LEX_RBRACE "}"
LEX_UNARY_NEGATION "!"

%%

{LEX_INTEGER_LITERAL} {
    handleToken("INTEGER_LITERAL", lexem_iterator);
}

{LEX_LOGIC_LITERAL} {
    handleToken("LOGIC_LITERAL", lexem_iterator);
}

{LEX_CLASS} {
    handleToken("CLASS", lexem_iterator);
}

{LEX_PUBLIC} {
    handleToken("PUBLIC", lexem_iterator);
}

{LEX_PRIVATE} {
    handleToken("PRIVATE", lexem_iterator);
}

{LEX_STATIC} {
    handleToken("STATIC", lexem_iterator);
}

{LEX_VOID} {
    handleToken("VOID", lexem_iterator);
}

{LEX_MAIN} {
    handleToken("MAIN", lexem_iterator);
}

{LEX_EXTENDS} {
    handleToken("EXTENDS", lexem_iterator);
}

{LEX_RETURN} {
    handleToken("RETURN", lexem_iterator);
}

{LEX_IF} {
    handleToken("IF", lexem_iterator);
}

{LEX_ELSE} {
    handleToken("ELSE", lexem_iterator);
}

{LEX_WHILE} {
    handleToken("WHILE", lexem_iterator);
}

{LEX_SOUT} {
    handleToken("SOUT", lexem_iterator);
}

{LEX_LENGTH} {
    handleToken("LENGTH", lexem_iterator);
}

{LEX_NEW} {
    handleToken("NEW", lexem_iterator);
}

{LEX_THIS} {
    handleToken("THIS", lexem_iterator);
}

{LEX_STRING} {
    handleToken("STRING", lexem_iterator);
}

{LEX_BOOLEAN} {
    handleToken("BOOLEAN", lexem_iterator);
}

{LEX_INT} {
    handleToken("INT", lexem_iterator);
}

{LEX_OR} {
    handleToken("OR", lexem_iterator);
}

{LEX_AND} {
    handleToken("AND", lexem_iterator);
}

{LEX_ID} {
    handleToken("ID(" + std::string(yytext) +")", lexem_iterator);
}

{LEX_SPACE} {
    handleToken("", lexem_iterator);
}

{LEX_COMMENT} {
    handleToken("COMMENT", lexem_iterator);
}

{LEX_OPERATORS} { handleToken(std::string(1, yytext[0]), lexem_iterator); }

.  {
    std::cout << std::endl << "UNKNOWN  " << yytext << std::endl;
    exit(-1);
}
%%
