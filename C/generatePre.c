#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "generatePre.h"
#include "removeExt.c"
#include "cleanFile.c"
#include "findNextEQU.c"

void generatePre(char * filename){
    char ch, move1, *new_file_name, *old_file_name;
    int len = 0;
    FILE *old_file, *new_file, *tempfile;

    len = (unsigned)strlen(filename);
    new_file_name = (char*) malloc(len);
    old_file_name = (char*) malloc(len);

    strcpy(old_file_name, filename);
    strcpy(new_file_name, removeExt(filename));
    strcat(new_file_name, ".pre");

    printf("%s\n", new_file_name);

    old_file = fopen(old_file_name, "r");
    tempfile = fopen("tempfile.txt", "w");
    new_file = fopen(new_file_name, "w");

    if(old_file == NULL){
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    if(tempfile == NULL){
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    if(new_file == NULL){
        perror("Error while creating new file.\n");
        exit(EXIT_FAILURE);
    }

    cleanFile(old_file, tempfile);
    freopen("tempfile.txt", "r", tempfile);

    //treat EQUs and IFs --------------------
    int n = 0, i = 0, e_flag = 0;
    char *line, *aux1, *aux2, *labelVal, *label, c, *l;
    fpos_t pos1, pos2;

    fgetpos(tempfile, &pos1);
    while(1){
        fgetpos(tempfile, &pos2);
        while(1){
            n++;
            c = fgetc(tempfile);
            if(c == '\n'){
                // printf("%d\n", n);
                break;
            }
        }
        fsetpos(tempfile, &pos2);
        line = (char*)malloc(n);
        label = (char*)malloc(50);
        aux1 = (char*)malloc(n);
        aux2 = (char*)malloc(n);
        fgets(line, n, tempfile);
        c = fgetc(tempfile); //offset

        for(i = 0; i < n; i++){
            if(line[i] == ':'){
                strcpy(aux2, line);
                labelVal = findNextEQU(tempfile, aux2);
                printf("%s: %s\n", label, labelVal);
                break;
            }
            label[i] = line[i];
        }

        for(i = 0; i < n; i++)
            aux1[i] = toupper(line[i]);

        if(!strcmp(aux1, "SECTION TEXT")){
            printf("strings match!\n%s\n", line);
            free(line);
            free(aux1);
            free(aux2);
            break;
        }
        free(line);
        free(label);
        free(aux1);
        free(aux2);
        n = 0;
    }
    fsetpos(tempfile, &pos1);
    //---------------------------------------

    while((ch = fgetc(tempfile)) != EOF){
        fprintf(new_file, "%c", ch);
    }

    fclose(tempfile);
    fclose(old_file);
    fclose(new_file);
    // remove("tempfile.txt");

    free(new_file_name);
    free(old_file_name);
}