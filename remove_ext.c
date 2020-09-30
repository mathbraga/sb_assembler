#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_ext(char* filename){
    int len = 0;
    char* no_ext;

    len = (unsigned)strlen(filename);
    no_ext = (char*) malloc(len);

    for(int i = len-1; i >= 0; i--){
        if(filename[i] == '.'){
            for(int j = 0; j < i; j++)
                no_ext[j] = filename[j];
            return no_ext;
        }
    }

    return filename;
}