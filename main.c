#include <stdio.h>
#include "stack.h"

void reading(char *filename)
{
    FILE *f=fopen(filename, "r");
    char expression[100];
    if(!f)
    {
        perror("File doesn't exist");
        exit(-1);
    }
    stack *s=initialize();
    while (!feof(f))
    {
        fscanf(f,"%[^\n]\n",expression);
        char *varName=malloc(strlen(expression)+1);
        strcpy(varName,strtok(expression,"="));
        if(!strcmp(varName,expression))
        {
            printf("%s \n this expression isn't valid ",expression);
            exit(-1);
        }
        char *postfix=malloc(strlen(expression)+1);
        //   postfix=infixToPost(expression,)


    }


}
///////////////////////////////////////////////////////////////////////
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
    reading("aa");
    char*t="2+(-2.5+3.14)*(-5.4+8.1)^(-0.5)";
    char i[100];
    infixToPost(format(t),i);
    printf("Result = %f\n",evaluate_postfix(i));
    return 0;
}
