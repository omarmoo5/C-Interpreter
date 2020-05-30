#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "helpers.h"

void COLOR(int color){
    // NEGATIVE:BOLD    // 0:RESET
    // 1:RED            // 2:GREEN
    // 3:YELLOW         // 4:BLUE
    // 5:MAGENTA        // 6:CYAN
    if (!color)
        printf("\033[0m");
    else
        printf(color>0?"\033[0;3%dm":"\033[1;3%dm",abs(color));
}

void ERROR(char *c, ...)
{
    fprintf( stderr, "ERROR:line:%ld>> ",lineNUM+1);
    va_list lst;
    va_start(lst, c);
    while(*c!='\0')
    {
        if(*c!='%')
        {
            fprintf( stderr, "%c",*c);
            c++;
            continue;
        }
        c++;
        switch(*c)
        {
            case 's': fputs(va_arg(lst, char *), stderr); break;
            case 'c': fprintf(stderr,"%c",(va_arg(lst, int))); break;
        }
        c++;
    }
    printf("\n");
    exit(-1);
}

void VERBOSE(char *c, ...)
{
    if (!Verbose) return;
    COLOR(-2);
    fprintf(stdout, "VERBOSE>> ");
    COLOR(3);
    va_list lst;
    va_start(lst, c);
    while (*c != '\0') {
        if (*c != '%') {
            fprintf(stdout, "%c", *c);
            c++;
            continue;
        }
        c++;
        switch (*c) {
            case 's':
                fputs(va_arg(lst, char *), stdout);
                break;
            case 'c':
                fprintf(stdout, "%c", (va_arg(lst, int)));
                break;
            case 'd':
                fprintf(stdout,"%d",(va_arg(lst, int)));
        }
        c++;
    }
    COLOR(0);
    printf("\n");
}

char* removeSpaces(char* str){
    int count = 0;
    for(int i = 0;str[i];i++){
        if (str[i]!=' ')
            str[count++] = str[i];
    }
    str[count]= '\0';
    return str;
}