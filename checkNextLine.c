#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nextIsLine(FILE *fp){
    char c;
    int res = 0;

    c = fgetc(fp);
    if(c == '\r'){// \n if Linux OS
        res = 1;
    }
    ungetc(c, fp);

    return res;
}

int nextIsSpace(FILE *fp){
    char c;
    int res = 0;

    c = fgetc(fp);
    if(c == 32){
        res = 1;
    }
    ungetc(c, fp);

    return res;
}

int nextIsEOF(FILE *fp){
    char c;
    int res = 0;

    c = fgetc(fp);
    if(c == EOF){
        res = 1;
    }
    ungetc(c, fp);

    return res;
}