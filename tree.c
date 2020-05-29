#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "heaps.h"
#include "helpers.h"

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
void fromTreeToHeap(Node * root)
{
    FILE *f=fopen("src.txt","r");

    Node *current, *pre;

    if (root == NULL)
        return;

    current = root;

    variable heap[count(root)];
    int index=0;


    while (current != NULL) {

        if (current->left == NULL) {
            heap[index].value=current->value;
            heap[index].name=malloc(strlen(current->name)+1);
            strcpy(heap[index].name,current->name);
            heapifyUp(heap,index);


            current = current->right;
        }
        else {

            /* Find the inorder predecessor of current */
            pre = current->left;
            while (pre->right != NULL && pre->right != current)
                pre = pre->right;

            /* Make current as the right child of its inorder
               predecessor */
            if (pre->right == NULL) {
                pre->right = current;
                current = current->left;
            }

                /* Revert the changes made in the 'if' part to restore
                   the original tree i.e., fix the right child
                   of predecessor */
            else {
                pre->right = NULL;

                heap[index].value=current->value;
                heap[index].name=malloc(strlen(current->name)+1);
                strcpy(heap[index].name,current->name);
                heapifyUp(heap,index);

                current = current->right;
            } /* End of if condition pre->right == NULL */
        }/* End of if condition current->left == NULL*/
       index++;
    }
    puts("------------------------");
    heapSort(index,heap);
    // COLOR(-5);
    puts("Order BY Variable Value:");
    //COLOR(0);
    printArray(heap,index);
}





