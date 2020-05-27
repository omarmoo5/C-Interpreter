#include <stdio.h>
#include <string.h>
#include "helpers.h"
#include "stack.h"
#include "tree.h"

void runFile(char *filename)
{
    FILE *f=fopen(filename, "r");
    if(!f)
    {
        ERROR("File doesn't exist");
        exit(-1);
    }
    char *Line=malloc(sizeof(char)*100);
    lineNUM=0;
    Node*root=NULL;
    char c = (char)fgetc(f);
    long lines =0;
    while (!feof(f))
    {
        if (c == '\n')lines++;
        c=(char)getc(f);
    }
    rewind(f);
    printf("Lines = %ld\n",lines);
    while (!feof(f))
    {
        // Scan Full Line.
        fscanf(f, "%[^\n]\n", Line);

        // Two-sided equation check "=".
        char *equalSign=strstr(Line,"=");
        if (!equalSign)
        {
            ERROR("INVALID EXPRESSION: \"%s\"", Line);
            exit(-1);
        }

        // Tokenizing Left Hand Side.
        char *LHS=malloc(sizeof(char) * (equalSign-Line)+1);
        strcpy(LHS, strtok(Line, "="));

        // Single LHS Variable Check.
        for (int i = 0; i < strlen(LHS); ++i)
        {
            if (!isalpha(LHS[0]) || ispunct(LHS[i]) && LHS[i]!='_'){
                ERROR("INVALID LHS: \"%s\"\n", LHS);
                exit(-1);
            }
        }

        // Tokenizing Right Hand Side.
        char *RHS=strtok(NULL,"");
        char i[100];
        infixToPost(format(RHS),i);
        float value = evaluate_postfix(i,root);
        root = insert(root,LHS,value);
        lineNUM++;
        printf("Line#%ld:\tLHS[%s]=RHS[%s]\t",lineNUM,LHS,RHS);
        printf("%s=%.2f\n",LHS,value);
    }
    puts("");
    inOrder(root);
}
int main()
{
    runFile("src.txt");
    return 0;
}
