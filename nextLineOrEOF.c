#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// res = 1 -> EOF
// res = 0 -> line break
int nextLineOrEOF(FILE *fp){
    char c;
    int res = 0;

    fseek(fp, 1, SEEK_CUR);
    c = fgetc(fp);
    if(c == 13){
        res = 1;
    }
    ungetc(c, fp);
    fseek(fp, -1, SEEK_CUR);
    // printf("%ld", ftell(fp));

    return res;
}