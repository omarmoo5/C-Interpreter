#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

Node* newNode(char* word,float value)
{
    Node* n=malloc(sizeof(Node));
    n->name=malloc(strlen(word)+1);
    strcpy(n->name,word);
    n->value=value;
    n->left=n->right=NULL;
    return n;
}

int max(int x,int y){return x>y?x:y;}

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

void inOrder(Node* root)
{
    if(root)
    {
        inOrder((Node *) root->left);
        printf("%s=%.2f\n", root->name, root->value);
        inOrder((Node *) root->right);
    }

}

int height(Node* root)
{
    if(root==NULL)
        return -1;
    else
        return 1+max(height((Node *) root->left), height((Node *) root->right));
}
int count(Node* root)
{
    if(root==NULL)
        return 0;
    else
        return 1 + count((Node *) root->left) + count((Node *) root->right);
}

void showTreeINFO(Node*root, char*label){
    puts("---------------------------------");
    printf("%s\n",label);
    puts("---------------------------------");
    printf("Nodes = %d\t",count(root));
    printf("Height = %d\n",height(root));
    puts("---------------------------------");
}

Node* minNode(Node* root){
    if (!root->left)
        return root;
    return minNode(root->left);
}

Node *maxNode(Node* root){
    if(!root)return NULL;
    if(!root->right)
        return root;
    return maxNode(root->right);
}

Node *inOrderSuccessor(Node* root,Node* n){
    if(!n)return NULL;
    if (n->right) return minNode(n->right);
    Node *Successor = NULL;
    while (root){
        if (strcasecmp(n->name,root->name)<0){
            Successor=root;
            root=root->left;
        }
        else if (strcasecmp(n->name,root->name)>0){root=root->right;}
        else break;
    }
    return Successor;
}

Node *inOrderPredecessor(Node*root,Node*n){
    if( n->left != NULL )
        return maxNode(n->left);
    Node *Pre=NULL;
    while (root) {
        if (strcasecmp(root->name, n->name) > 0) {
            root=root->left;
        } else if (strcasecmp(root->name, n->name) < 0){
            Pre=root;
            root=root->right;
        } else break;
    }
    return Pre;
}


