#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generate_pre.h"
#include "remove_ext.c"
#include "checkNextLine.c"

void generate_pre(char * filename){
    char ch, *new_file_name, *old_file_name;
    int ws_flag = 1, nl_flag = 1, len = 0;
    FILE *old_file, *new_file;

    len = (unsigned)strlen(filename);
    new_file_name = (char*) malloc(len);
    old_file_name = (char*) malloc(len);

    strcpy(old_file_name, filename);
    strcpy(new_file_name, remove_ext(filename));
    strcat(new_file_name, ".pre");

    printf("%s\n", new_file_name);

    old_file = fopen(old_file_name, "r");
    new_file = fopen(new_file_name, "w");

    if(old_file == NULL){
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    if(new_file == NULL){
        perror("Error while creating new file.\n");
        exit(EXIT_FAILURE);
    }

    while((ch = fgetc(old_file)) != EOF){
        switch (ch){
            case '\r':
                break;
            case '\n':
                if(!nl_flag){
                    fprintf(new_file, "%c", ch);
                    nl_flag = 1;
                }
                break;
            case 32: // white space
                if(!ws_flag && !nl_flag && !nextIsLine(old_file) && !nextIsSpace(old_file) && !nextIsEOF(old_file)){
                    fprintf(new_file, "%c", ch);
                    ws_flag = 1;
                }
                else if(!ws_flag && nl_flag){
                    ws_flag = 1;
                    nl_flag = 0;
                }
                break;
            default:
                fprintf(new_file, "%c", ch);
                ws_flag = 0;
                nl_flag = 0;
                break;
        }
    }

    fclose(old_file);
    fclose(new_file);

    free(new_file_name);
    free(old_file_name);
}