#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "heaps.h"
#include "helpers.h"
int heapIndex=0;
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
    Node *n=search(Root,key);

    if(Root==NULL)
        return newNode(key,value);
    else if(n)
        n->value=value;
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
int count(Node* root)
{
    if(root==NULL)
        return 0;
    else
        return 1+count(root->left)+count(root->right);

}

//----------------------------------------------------------------
//----------------------------------------------
void fromTreeToHeap(Node * root,variable heap[])
{
    if(root)
    {
        fromTreeToHeap((Node *) root->left,heap);

        heap[heapIndex].value=root->value;
        heap[heapIndex].name=malloc(strlen(root->name)+1);
        strcpy(heap[heapIndex].name,root->name);
        heapifyUp(heap,heapIndex);

        ++heapIndex;

        fromTreeToHeap((Node *) root->right,heap);

    }

}





