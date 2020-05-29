#include <stdio.h>
#include <stdarg.h>
#include "helpers.h"
void ERROR(char *c, ...)
{
    fprintf( stderr, "ERROR:line:%ld>> ",lineNUM+1);
    char *s;
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
}

char*removeSpaces(char* str){
    int count = 0;
    for(int i = 0;str[i];i++){
        if (str[i]!=' ')
            str[count++] = str[i];
    }
    str[count]= '\0';
    return str;
}