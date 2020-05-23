#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "tree.h"

#define SIZE 100

typedef union
{
    float fData;
    char cData;
} Item;

typedef struct
{
    Item items[SIZE];
    int top ;
    //the index of the last element in the stack
} stack;

char* tok (char *sr)
{
    char *token=strtok(sr," ");
    return token;
}

stack *initialize()
{
    stack *s=malloc(sizeof(stack));
    s->top=0;
    return s;
}

void push(stack *s,Item value)
{
    s->items[s->top++]=value;
    //adding item in the last index
}

Item pop(stack *s)
{
    Item value;
    s->top--;
    value = s->items[s->top];
    return value;
    //removing the last element in the

}

Item peek(stack *s)
{
    return s->items[s->top-1];
    //returning the last element in the stack
}
int isempty(stack *s)
{
    if(s->top==0)
        return 1;
    else
        return 0;
    //check if the  is empty
}

float calculate (char x,float op1,float op2)
{
    switch (x)
    {
        case '+':return op1+op2;
        case '-':return op1-op2;
        case '/':return op1/op2;
        case '*':return op1*op2;
        case '%':return (float)((int)op1%(int)op2);
        case '^':return powf(op1,op2);
        default: return 0;
    }
}

int isOperator(const char* character)
{
    switch (character[0])
    {
        case '-':case '+':case '/':case '*':case '^':case '%':case '(':case ')': return 1;
        default: return 0;
    }
}

int precedence(char c)
{
    switch (c)
    {
        case '+':return 2;
        case '-':return 1;
        case '/':return 3;
        case '*':return 4;
        case '^':return 5;
        case '(':case ')':return 6;
        default:return -99999;
    }
}

float evaluate_postfix(char *expression,Node *root)
{
    stack *s=initialize();
    Item i1,i2,value;
    float op1,op2,val;
    char *token=strtok(expression," ");
    // loop through the string to extract all other tokens
    while( token )
    {
        //printf( "%s\n", token );
        //printing each token
        if(strlen(token)==1 && isOperator(token))
        {
            i2=pop(s);op2=i2.fData;
            i1=pop(s);op1=i1.fData;
            val=calculate(token[0],op1,op2);
            value.fData = val;
            push(s,value);
        }
        else
        {
            if (isalpha(token[0])){
                Node *n=search(root,token);
                if (!n)exit(-1);
                i1.fData=n->value;
            }
            else i1.fData=strtof(token,NULL);
            push(s,i1);
        }
        token = strtok(NULL, " ");
    }
    value = pop(s);val = value.fData;
    if (!isempty(s))
    {
        ERROR("[Stack Evaluation]:INVALID EXPRESSION EVALUATED\n");
        exit(-1);
    }
    free(s);
    return val;

}

char* format(char *expression)
{
    if (VERBOSE)puts("[Format] Formatting The Expression");
    if (VERBOSE)printf("[Format] Before \"%s\"\n",expression);
    //Allocating double its size For the WorstCase Compressed Equation
    char *formattedRHS=malloc(strlen(expression) * 2);
    //Clearing the String
    strcpy(formattedRHS, "");
    for(int i=0;i<strlen(expression);i++)
    {
        char c=expression[i];
        if(( c == '-' && (i==0||isOperator(&expression[i-1])))||(!isOperator(&c)))
        {
            strncat(formattedRHS, &c, 1);
        }
        else
        {
            strcat(formattedRHS, " ");
            strncat(formattedRHS, &c, 1);
            strcat(formattedRHS, " ");
        }
    }
    //reallocating to the proper size of the string
    formattedRHS = (char*)realloc(formattedRHS, strlen(formattedRHS)+1);
    if (VERBOSE)printf("[Format] After \"%s\"\n",formattedRHS);
    return formattedRHS;
}

void infixToPost(char *infix, char *postfix)
{
    int i = 0;
    stack *s = initialize();
    if (VERBOSE) printf("\n[infixToPost] Stack Initialized\n");

    // initiate:
    if (VERBOSE) printf("[infixToPost] \"%s\" \n",infix);
    
    strcpy(postfix,"");
    char *token=strtok(infix," ");

    // loop through the string to extract all other tokens
    while(token)
    {
        if(strlen(token)==1 && isOperator(token))
        {   //Operator
            Item myitem ;
            char op[]=" ";
            if (VERBOSE) printf("[infixToPost %d] Operator [%c] \n",i++,token[0]);
            myitem.cData = token[0];
            if (token[0]==')')
            {
                while(peek(s).cData != '(' && !isempty(s))
                {
                    if (VERBOSE) printf("[infixToPost %d] peek [%c] \n",i++,peek(s).cData);
                    op[0] = pop(s).cData;
                    strcat(postfix,op);
                    strcat(postfix," ");
                    op[0] = ' ';
                }
                pop(s);
            }
            else if (isempty(s)|| precedence(token[0])>precedence(peek(s).cData) || (!isempty(s) && peek(s).cData == '('))
            {
                if (VERBOSE) printf("[infixToPost %d] [%c] precedence %d | isEmpty %d \n",i++,myitem.cData,precedence(myitem.cData),isempty(s));
                push(s,myitem);
                if (VERBOSE) printf("[infixToPost %d] Pushed %c \n",i++,peek(s).cData);

            }
            else if (precedence(token[0])<=precedence(peek(s).cData))
            {
                if (VERBOSE) printf("[infixToPost %d] [%c] precedence %d < %d | isEmpty %d \n",i++,myitem.cData,precedence(myitem.cData),precedence(peek(s).cData),isempty(s));
                while(precedence(token[0])<precedence(peek(s).cData) && !isempty(s))
                {
                    op[0] = pop(s).cData;
                    strcat(postfix,op);
                    strcat(postfix," ");
                    op[0] = ' ';
                }
                push(s,myitem);
            }
        }
        else //Operand
        {   if (VERBOSE) printf("[infixToPost %d] Operand [%s] \n",i++,token);
            strcat(postfix,token);
            strcat(postfix," ");
        }
        token = strtok(NULL, " ");
    }
    // Popping All The Stack
    char op[]=" ";
    while (!isempty(s))
    {
        op[0] = pop(s).cData;
        strcat(postfix,op);
        strcat(postfix," ");
        op[0] = ' ';
    }
    if (VERBOSE) printf("[infixToPost] Stack is Empty\n");
    free(s);
    if (VERBOSE) printf("[infixToPost] Stack Freed\n");
}

