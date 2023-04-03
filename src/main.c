#include "globals.h"

#ifndef LEX
int getToken();
#define GETTOKEN()  getToken()
#else
int getToken_Lex();
#define GETTOKEN()    getToken_Lex()
#endif

/* external variable define */
FILE* source;
int lineno = 1;

int main(int argc, char* argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: <filename> %s\n", argv[0]);
    }    
    fopen_s(&source, argv[1], "r");

    while (!GETTOKEN()) ;

    return 0;
}