#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "stack.h"
#include "tree.h"

void ERROR(long lineNUM, char *c, ...)
{
    fprintf( stderr, "ERROR:line:%ld>> ",lineNUM);
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

void runFile(char *filename)
{
    FILE *f=fopen(filename, "r");
    if(!f){perror("File doesn't exist");exit(-1);}
    char *Line=malloc(sizeof(char )*100);
    long lineNUM=0;
    Node*root=NULL;
    while (!feof(f))
    {
        // Scan Full Line.
        fscanf(f, "%[^\n]\n", Line);

        // Two-sided equation check "=".
        char *equalSign=strstr(Line,"=");
        if (!equalSign)
        {
            ERROR(lineNUM,"INVALID EXPRESSION: \"%s\"", Line);
            exit(-1);
        }
        // Tokenizing Left Hand Side.
        char *LHS=malloc(sizeof(char) * (equalSign-Line)+1);
        strcpy(LHS, strtok(Line, "="));
        // Single LHS Variable Check.
        for (int i = 0; i < strlen(LHS); ++i)
        {
            if (!isalpha(LHS[0]) || ispunct(LHS[i]) && LHS[i]!='_')
                { ERROR(lineNUM,"INVALID LHS: \"%s\"\n", LHS);exit(-1);}
        }
        // Tokenizing Right Hand Side.
        char *RHS=strtok(NULL,"");
        char i[100];
        infixToPost(format(RHS),i);
        float value = evaluate_postfix(i,root);
        root = insert(root,LHS,value);
        printf("Line#%ld:\tLHS[%s]=RHS[%s]\n",lineNUM,LHS,RHS);
        printf("%s=%.2f\n",LHS,value);
        lineNUM++;
    }
    puts("");
    inOrder(root);
}
int main()
{
    runFile("src.txt");
    return 0;
}
