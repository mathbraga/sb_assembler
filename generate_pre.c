#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generate_pre.h"
#include "remove_ext.c"

void generate_pre(char * filename){
    char ch, file_name[50], new_file_name[50];
    int ws_flag = 0;
    FILE *old_file, *new_file;

    strcpy(new_file_name, remove_ext(filename));
    strcat(new_file_name, ".pre");

    printf("%s\n", new_file_name);

    old_file = fopen(filename, "r");
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
                if(ws_flag == 0){
                    fprintf(new_file, " ");
                    ws_flag = 1;
                }
                break;
            case 32: // white space
                if(ws_flag == 0){
                    fprintf(new_file, "%c", ch);
                    ws_flag = 1;
                }
                break;
            default:
                fprintf(new_file, "%c", ch);
                ws_flag = 0;
                break;
        }
    }

    fclose(old_file);
    fclose(new_file);
}