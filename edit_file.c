#include <stdio.h>
#include <stdlib.h>
#include "edit_file.h"

void edit_file(char* file_name){
    char ch;
    FILE *old_file, *new_file;

    printf("%s \n", file_name);

    old_file = fopen(file_name, "r");
    new_file = fopen("edited.txt", "w");

    if(old_file == NULL){
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    if(new_file == NULL){
        perror("Error while creating new file.\n");
        exit(EXIT_FAILURE);
    }

    while((ch = fgetc(old_file)) != EOF){
        if(ch == '\r')
            fprintf(new_file, " ");
        else if(ch == '\n')
            fprintf(new_file, "");
        else
        fprintf(new_file, "%c", ch);
    }

    fclose(old_file);
    fclose(new_file);
}