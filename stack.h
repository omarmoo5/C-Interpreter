#ifndef INTERPRETER_STACK_H
#define INTERPRETER_STACK_H
#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#define SIZE 100

typedef union
{
    float fData;
    char cData;
} floata;
typedef struct
{
    floata items[SIZE];
    int top ;
    //the index of the last element in the stack
} stack;

stack *initialize();
float calculate (char x,float op1,float op2);
int isOperator(const char* character);
int precedence(char c);
float evaluate_postfix(char *expression);
char* format(char *expression);
void infixToPost(char *infix, char *postfix);

#endif //INTERPRETER_STACK_H
