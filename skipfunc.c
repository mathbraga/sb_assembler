#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void skipAllTabs(FILE *fp){
    char c;
    int res = 0;

    c = fgetc(fp);
    if(c == '\t'){
        if(nextIsTab(fp))
            skipAllTabs(fp);
    }
}

void skipAllComments(FILE *fp){
    char c;
    int res = 0;

    while((c = fgetc(fp)) != '\n');
    ungetc(c, fp);
}