#ifndef INTERPRETER_STACK_H
#define INTERPRETER_STACK_H
#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include "tree.h"

#define SIZE 100

typedef union
{
    float fData;
    char cData;
} Item;


//-----------------------------------------------------
//------------------------- A Struct Representing Stack
typedef struct
{
    Item items[SIZE];
    int top ;
} stack;


//-----------------------------------------------------
//---------------------------------- Initializing Stack
stack *initialize();


//-----------------------------------------------------
//Calculates According To The Function Of Each Operator
float calculate (char x,float op1,float op2);


//-----------------------------------------------------
//---------------------- Checks If An Operator Is Found
int isOperator(const char* character);


//-----------------------------------------------------
//---------------- Assign Precedence for each operator
int precedence(char c);


//-----------------------------------------------------
//-------------------- Evaluates The PostFix Expression
float evaluate_postfix(char *expression,Node* root);


//-----------------------------------------------------
//------------- Puts The Expression In The Right Format
char* format(char *expression);


//-----------------------------------------------------
// Reform & Change The Expression From InFix to PostFix
void infixToPost(char *infix, char *postfix);

#endif //INTERPRETER_STACK_H
