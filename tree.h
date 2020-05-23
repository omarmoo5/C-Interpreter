#ifndef INTERPRETER_TREE_H
#define INTERPRETER_TREE_H

typedef struct Node
{
    char*   name;
    float value;
    struct Node* left;
    struct Node*right;
} Node;

Node* newNode(char* word,float);
Node* insert(Node* Root,char* key,float);
Node* search(Node* root, char* key);
void PostOrder(Node* root);
void PreOrder(Node* root);
void inOrder(Node* root);
void showTreeINFO(Node*root, char*label);

#endif //INTERPRETER_TREE_H
