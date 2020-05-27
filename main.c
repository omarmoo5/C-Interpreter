#include <stdio.h>
#include <string.h>
#include "helpers.h"
#include "stack.h"
#include "tree.h"
#include "heaps.h"

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
    lines++;
    rewind(f);
    printf("Lines = %ld\n",lines);
    variable heap[lines];

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
        for(int p=strlen(LHS)-1;p>=0;p--)
        {
            if(LHS[p]!=' ')break;
            LHS[p]='\0';
        }
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
        heap[lineNUM].value=value;
        heap[lineNUM].name=malloc(strlen(LHS)+1);
        strcpy(heap[lineNUM].name,LHS);
        heapifyUp(heap,lineNUM);
        lineNUM++;
        printf("Line#%ld:\tLHS[%s]=RHS[%s]\t",lineNUM,LHS,RHS);
        printf("%s=%.2f\n",LHS,value);
    }

    printf("\n----- \n");
    heapSort(lineNUM,heap);
    printArray(heap,lineNUM-1);
    printf("-----\n");

    puts("");
    inOrder(root);
}
int main()
{
    runFile("src.txt");

    return 0;
}
