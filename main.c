#include <stdio.h>
#include <string.h>
#include "helpers.h"
#include "stack.h"
#include "tree.h"
#include "heaps.h"

//Global tree root
Node* ROOT=NULL;

//Wrapper Function takes key and value to insert in the BST.
void put(char *key,float value){
    ROOT=insert(ROOT, key, value);
}

void runFile(char *filename)
{
    VERBOSE("Reading the file");
    FILE *f=fopen(filename, "r");

    if(!f)
        ERROR("File doesn't exist");

    char *Line=malloc(sizeof(char)*100);
    lineNUM=0;
    while (!feof(f))
    {
        // Scan Full Line.
        fscanf(f, "%[^\n]\n", Line);
        Line = removeSpaces(Line);

        // Two-sided equation check for the equal sign '='.
        char *equalSign=strstr(Line,"=");
        if (!equalSign)
            ERROR("INVALID EXPRESSION: \"%s\"", Line);

        // Tokenizing Left Hand Side (LHS).
        if(Line[0]=='=')
            ERROR("NO LHS !");
        char *LHS=malloc(sizeof(char) * (equalSign-Line)+1);
        strcpy(LHS, strtok(Line, "="));

        // Single LHS Variable Check. (Valid Variable Name)
        for (int i = 0; i < strlen(LHS); ++i)
        {
            if (!isalpha(LHS[0]) || ispunct(LHS[i]) && LHS[i]!='_')
                ERROR("INVALID LHS: \"%s\"", LHS);
        }

        // Tokenizing Right Hand Side.
        char *RHS=strtok(NULL,"");
        if(!RHS)
            ERROR("NO RHS !");

        char *Postfix=infixToPost(format(RHS));
        float value = evaluate_postfix(Postfix, ROOT);

        put(LHS,value);

        printf("Line#%ld:\tLHS[%s]=RHS[%s]\n",lineNUM++ + 1,LHS,RHS);
//        COLOR(4);
        printf("%s=%.2f\n",LHS,value);
//        COLOR(0);
    }

    puts("------------------------");
//    COLOR(-5);
    puts("Order BY Variable Name: ");
//    COLOR(0);
    inOrder(ROOT);

    variable heap[count(ROOT)];
    fromTreeToHeap(ROOT, heap);

    puts("------------------------");
    heapSort(count(ROOT), heap);
//    COLOR(-5);
    puts("Order BY Variable Value:");
//    COLOR(0);
    printArray(heap,count(ROOT));

}

int main()
{
    runFile("src.txt");
    return 0;
}