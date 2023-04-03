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
"{"             { 
                    char c;
                    do {
                        c = input();
                        if (c == ENDFILE) break;
                        if (c == '\n') lineno++;
                    } while (c != '}');
                }
.               {return ERROR;}

%%
int getToken_Lex()
{
    static int firstTime = TRUE;
    if (firstTime) {
        firstTime = FALSE;
        yyin = source;
        lineno++;
    }
    TokenType tokenType = yylex();
    fprintf(stdout, "%4d: ", lineno);
    printToken_Lex(tokenType, yytext);

    return tokenType;
}