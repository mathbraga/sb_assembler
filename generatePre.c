#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generatePre.h"
#include "removeExt.c"
#include "checkNextLine.c"
#include "skipfunc.c"

void generatePre(char * filename){
    char ch, move1, *new_file_name, *old_file_name;
    int ws_flag = 1, nl_flag = 1, len = 0, ln = 0, sp = 0, endf = 0, com = 0;
    FILE *old_file, *new_file;

    len = (unsigned)strlen(filename);
    new_file_name = (char*) malloc(len);
    old_file_name = (char*) malloc(len);

    strcpy(old_file_name, filename);
    strcpy(new_file_name, removeExt(filename));
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
        // printf("%d\n", ch);
        switch (ch){
            case '\r':
                break;
            case '\n':
                if(!nl_flag && !nextIsEOF(old_file) && !nextIsLine(old_file)){
                    fprintf(new_file, "%c", ch);
                    nl_flag = 1;
                }
                break;
            case 32: // white space
                if(nextIsTab(old_file)){
                    skipAllTabs(old_file);
                }
                ln = nextIsLine(old_file);
                sp = nextIsSpace(old_file);
                endf = nextIsEOF(old_file);
                com = nextIsComment(old_file);
                if(!ws_flag && !nl_flag && !ln && !sp && !endf && !com){
                    fprintf(new_file, "%c", ch);
                    ws_flag = 1;
                }
                else if(nl_flag){
                    ws_flag = 1;
                }
                break;
            case '\t':
                break;
            case ';':
                skipAllComments(old_file);
                if(nextIsLine(old_file)){
                    fprintf(new_file, "\n");
                    nl_flag = 1;
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