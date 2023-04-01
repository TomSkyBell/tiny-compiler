#include "scan.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define BUFLEN          1024
#define TOKENLEN        50

typedef enum {
    START, NUM, ID, COMMENT, ASSIGN, DONE
} STATE;

static char buf[BUFLEN];
static size_t bufPos = 0, bufSize;
static int lineno;
static char* reservedWords[7] = {
    "if", "then", "end", "repeat", "until",
    "read", "write"
};

static int isReservedWord(const char* str)
{
    int i;
    for (i=0; i<7; i++) {
        if (strcmp(reservedWords[i], str) == 0) {
            return TRUE;
        }
    }
    return FALSE;
}

static int iswhitespace(int ch)
{
    return ch==' ' || ch=='\n' || ch=='\t';
}

static int isoperator(int ch)
{
    return ch=='+' || ch=='-' || ch=='*' || ch=='/' 
        || ch==';' || ch=='<' || ch=='=';
}

static int getNextChar()
{
    /* read new line from file when the buffer is full */
    if (bufPos>=bufSize) {
        lineno++;
        if (fgets(buf, BUFLEN, source)) {
            bufSize = strlen(buf);
            bufPos = 0;
        } else {
            return EOF;
        }
    }
    return (int)buf[bufPos++];
}

static void ungetChar()
{
    --bufPos;
}

static void printToken(const char* tokenString)
{
    if (isReservedWord(tokenString)) {
        fprintf(stdout, "Reserved Word: %s\n", tokenString);
    } else {
        fprintf(stdout, "%s\n", tokenString);
    }
}

int getToken()
{
    int tokenStringIndex = 0;
    char tokenString[TOKENLEN] = {0};
    STATE state = START;
    while (state != DONE) {
        int saveFlag = TRUE;
        int ch = getNextChar();
        switch (state) {
        case START:
            if (iswhitespace(ch)) {
                saveFlag = FALSE;
                // state = START;
            } else if (isdigit(ch)) {
                state = NUM;
            } else if (isalpha(ch)) {
                state = ID;
            } else if (ch == '{') {
                saveFlag = FALSE;
                state = COMMENT;
            } else if (ch == ':') {
                state = ASSIGN;
            } else if (isoperator(ch)) {
                state = DONE;
            } else if (ch == EOF) {
                fprintf(stdout, "reach the end of file\n");
                return TRUE;
            } else {
                saveFlag = FALSE;
                state = DONE;
                fprintf(stderr, "Error, unrecognized symbol, lineno: %d\n", lineno);
            }
            break;
        case NUM:
            if (isdigit(ch)) {
                // state = NUM;
            } else {
                saveFlag = FALSE;
                ungetChar();
                state = DONE;
            }
            break;
        case ID:
            if (isalpha(ch)) {
                // state = ID;
            } else {
                saveFlag = FALSE;
                ungetChar();
                state = DONE;
            }
            break;
        case COMMENT:
            saveFlag = FALSE;
            if (ch == '}') {
                state = START;
            } else {
                // state = COMMENT;
            }
            break;
        case ASSIGN:
            if (ch == '=') {
                state = DONE;
            } else {
                saveFlag = FALSE;
                ungetChar();
                state = DONE;
            }
            break;
        case DONE:  /* It should never reach here */
        default:
            break;
        }
        if (saveFlag) tokenString[tokenStringIndex++] = ch;
    }
    printToken(tokenString);
    return FALSE;
}