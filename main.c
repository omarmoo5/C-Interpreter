#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "stack.h"

#include <stdio.h>

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
        printf("Line#%ld:\tLHS[%s]=RHS[%s]\n",lineNUM,LHS,RHS);
        printf("%s=%.2f\n",LHS,evaluate_postfix(i));
        lineNUM++;
    }
}
/*typedef struct
{
    char *varName;
    float value;
    struct  Node* left;
    struct Node*right;
} Node;
Node* newNode(char *w,float value)
{
    Node* n=malloc(sizeof(Node));
    n->varName=malloc(strlen(w)+1);
    strcpy(n->varName,w);
    n->value=value;
    n->left=NULL;
    n->right=NULL;
    return n;
}
Node* insert(Node* Root,char* key,float value)
{
    if(Root==NULL)
        return newNode(key,value);
    else if(strcasecmp(key,Root->varName) > 0)
        Root->right=insert(Root->right, key);
    else
        Root->left=insert(Root->left, key);
    return Root;
}
Node* search(Node* root,char *w)
{
    if(root==NULL||w==NULL)
        return NULL;
    else if (strcasecmp(root->varName,w)==0)
        return root;
    else if(strcasecmp(root->varName,w)>0)
    {
        if(root->left==NULL)
            return root;
        else
            return search(root->left,w);
    }

    else
    {
        if(root->right==NULL)
            return root;
        else
            return search(root->right,w);
    }
}
*/

int main()
{
    runFile("src.txt");
    return 0;
}
