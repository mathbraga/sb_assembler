#include <stdio.h>
#include <stdlib.h>
#include "generate_pre.c"

int main(int argc, char **argv){
    int comp_pre, comp_obj = 1;

    comp_pre = strcmp(argv[1], "-p");
    comp_obj = strcmp(argv[1], "-o");

    if(!comp_pre)
        generate_pre(argv[2]);
    else if(!comp_obj)
        printf("generate object\n");


    return 0;
}