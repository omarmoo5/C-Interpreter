#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

//----------------------------------------------------------------
//-------------------------------------------- Creating A New Node

Node* newNode(char* word,float value)
{
    Node* n=malloc(sizeof(Node));
    n->name=malloc(strlen(word)+1);
    strcpy(n->name,word);
    n->value=value;
    n->left=n->right=NULL;
    return n;
}


//----------------------------------------------------------------
//---------------------------------------- Insert Node To The Tree

Node* insert(Node* Root,char* key,float value)
{
    if(Root==NULL)
        return newNode(key,value);
    else if(strcasecmp(key,Root->name) > 0)
        Root->right=insert(Root->right, key,value);
    else
        Root->left=insert(Root->left, key,value);
    return Root;
}


//----------------------------------------------------------------
//---------------------------------------- Search Through The tree

Node* search(Node* root, char* key)
{
    if(!root||!key)
        return NULL;
    else if (strcasecmp(key,root->name)==0)
        return root;
    else if (strcasecmp(key,root->name)<0) {
        return search((Node *) root->left, key);
    }
    else{
        return search((Node *) root->right, key);
    }
}


//----------------------------------------------------------------
//---------------------------------------------- InOrder Traversal

void inOrder(Node* root)
{
    if(root)
    {
        inOrder((Node *) root->left);
        printf("%s = %.2f\n", root->name, root->value);
        inOrder((Node *) root->right);
    }
}