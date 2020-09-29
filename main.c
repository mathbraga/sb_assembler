#include <stdio.h>
#include <stdlib.h>
#include "edit_file.h"

int main(){
    char file_name[50];

    printf("File name: \n");
    gets(file_name);

    edit_file(file_name);

    return 0;
}