#include "util.h"
#include <stdio.h>
#include <stdlib.h>

void printToken_Lex(TokenType type, const char *str)
{
    switch (type) {
    case ENDFILE:
        fprintf(stdout, "reach the end of file\n");
        break;
    case ERROR:
        fprintf(stderr, "scanner error\n");
        exit(1);
        break;
    case IF:
    case THEN:
    case ELSE:
    case END:
    case REPEAT:
    case UNTIL:
    case READ:
    case WRITE:
        fprintf(stdout, "reserved word: %s\n", str);
        break;
    case ID:
        fprintf(stdout, "ID, name = %s\n", str);
        break;
    case NUM:
        fprintf(stdout, "num, value = %s\n", str);
        break;
    case ASSIGN:
    case EQ:
    case LT:
    case PLUS:
    case MINUS:
    case TIMES:
    case OVER:
    case LPAREN:
    case RPAREN:
    case SEMI:
        fprintf(stdout, "%s\n", str);
        break;
    }
}