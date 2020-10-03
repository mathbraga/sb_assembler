#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char ch, *line;
    int n = 0, flag = 0;
    FILE *old_file, *new_file;
    fpos_t pos;

    old_file = fopen("myprogram.asm", "r");
    new_file = fopen("test.pre", "w");

    do{
        do{
            n++;
        }while(((ch = fgetc(old_file)) != '\r') && (ch != EOF));
        line = (char *) malloc(n);
        if(ch == EOF){
            flag = 1;
            n--;
        }
        fseek(old_file, -n, SEEK_CUR);
        fgets(line, (n+1), old_file);
        printf("%s\n", line);
        fseek(old_file, 1, SEEK_CUR);
        fprintf(new_file, "%s", line);
        free(line);

        n = 0;
    }while(!flag);

    return 0;
}