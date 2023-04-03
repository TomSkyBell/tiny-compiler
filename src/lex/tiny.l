%option noyywrap

%{
/*  The comment test for the automatic
    lexer generator tool -- flex.
*/
#include "globals.h"
#include "util.h"
%}
digit           [0-9]
number          {digit}+
letter          [a-zA-Z]
identifier      {letter}+
newline         \n
whitespace      [ \t]+

%%
"if"            {return IF;}
"then"          {return THEN;}
"else"          {return ELSE;}
"end"           {return END;}
"repeat"        {return REPEAT;}
"until"         {return UNTIL;}
"read"          {return READ;}
"write"         {return WRITE;}

"+"             {return PLUS;}
"-"             {return MINUS;}
"*"             {return TIMES;}
"/"             {return OVER;}
":="            {return ASSIGN;}
"="             {return EQ;}
"<"             {return LT;}
"("             {return LPAREN;}
")"             {return RPAREN;}
";"             {return SEMI;}

{number}        {return NUM;}
{identifier}    {return ID;}
{newline}       {lineno++;}
{whitespace}    {/* skip white space, do nothing */}
"{"             { char c; while ((c=input()) != '}') ;}

%%
int getToken_Lex()
{
    yyin = source;
    TokenType tokenType = yylex();
    printToken_Lex(tokenType, yytext);

    return tokenType ? FALSE : TRUE;
}