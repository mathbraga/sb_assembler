#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* findNextEQU(FILE* fp, char *line){
    char *subs, *str, c;
    int len = 0;
    fpos_t pos1, pos2;

    fgetpos(fp, &pos1);
    subs = strtok(line, " ");
    while(subs != NULL){
        if(!strcmp(subs, "EQU")){
            subs = strtok(NULL, " ");
            return subs;
        }
        subs = strtok(NULL, " ");
    }
    if(subs == NULL){
        fgetpos(fp, &pos2);
        while(1){
            len++;
            c = fgetc(fp);
            if(c == '\n'){
                // printf("%d\n", n);
                break;
            }
        }
        fsetpos(fp, &pos2);
        str = (char*)malloc(len);
        fgets(str, len, fp);
        subs = findNextEQU(fp, str);
        // free(str);
        fsetpos(fp, &pos1);
        return subs;
    }
}