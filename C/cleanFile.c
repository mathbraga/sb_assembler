#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "checkNextLine.c"
#include "skipfunc.c"

void cleanFile(FILE *inputfile, FILE *outputfile){
    int ws_flag = 1, nl_flag = 1, ln = 0, sp = 0, endf = 0, com = 0;
    char ch;

    while((ch = fgetc(inputfile)) != EOF){
        // printf("%d\n", ch);
        switch (ch){
            case '\r':
                break;
            case '\n':
                if(!nl_flag && !nextIsEOF(inputfile) && !nextIsLine(inputfile)){
                    fprintf(outputfile, "%c", ch);
                    nl_flag = 1;
                }
                break;
            case 32: // white space
                if(nextIsTab(inputfile)){
                    skipAllTabs(inputfile);
                }
                ln = nextIsLine(inputfile);
                sp = nextIsSpace(inputfile);
                endf = nextIsEOF(inputfile);
                com = nextIsComment(inputfile);
                if(!ws_flag && !nl_flag && !ln && !sp && !endf && !com){
                    fprintf(outputfile, "%c", ch);
                    ws_flag = 1;
                }
                else if(nl_flag){
                    ws_flag = 1;
                }
                break;
            case '\t':
                break;
            case ';':
                skipAllComments(inputfile);
                // if(nextIsLine(inputfile)){
                //     fprintf(new_file, "\n");
                //     nl_flag = 1;
                // }
                break;
            default:
                fprintf(outputfile, "%c", ch);
                ws_flag = 0;
                nl_flag = 0;
                break;
        }
    }
}