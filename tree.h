#ifndef INTERPRETER_TREE_H
#define INTERPRETER_TREE_H

#include "heaps.h"

//-----------------------------------------------------
//----------------- A Struct Representing a Node in BST
typedef struct Node
{
    char*  name;
    float value;
    struct Node* left;
    struct Node*right;
} Node;


//-----------------------------------------------------
//--------------------------------- Creating A New Node
Node* newNode(char* word,float);


//-----------------------------------------------------
//----------------------------- Insert Node To The Tree
Node* insert(Node* Root,char* key,float);


//-----------------------------------------------------
//----------------------------- Search Through The tree
Node* search(Node* root, char* key);


//-----------------------------------------------------
//----------------------------------- Inorder Traversal
void inOrder(Node* root);


//-----------------------------------------------------
//----------------------------------- Num of tree elements
int count(Node* root);


//-----------------------------------------------------
//-----------------------------------from tree to heap
void fromTreeToHeap(Node * root,variable heap[]);

#endif //INTERPRETER_TREE_H
