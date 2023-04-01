#include "scan.h"

FILE* source;

int main(int argc, char* argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: <filename> %s\n", argv[0]);
    }    
    fopen_s(&source, argv[1], "r");

    while (!getToken()) ;

    return 0;
}