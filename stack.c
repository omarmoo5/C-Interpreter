#include "stack.h"
#include "helpers.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "tree.h"


////-----------------------------------------------------------------------------------------
//------------------------------------------------------------------------ Initializing Stack

stack *initialize()
{
    stack *s=malloc(sizeof(stack));
    s->top=0;
    return s;
}


////-----------------------------------------------------------------------------------------
//------------------------------------------------------------------- Push Item To Last Index

void push(stack *s,Item value)
{
    s->items[s->top++]=value;
    //adding item in the last index
}


//-----------------------------------------------------------------------------------------
//----------------------------------------------------------- Pop/Remove Last Item In Stack

Item pop(stack *s)
{
    Item value;
    s->top--;
    value = s->items[s->top];
    return value;
    //removing the last element in the

}

//-----------------------------------------------------------------------------------------
//---------------------------------------------------------- Peek/Return Last Item In Stack

Item peek(stack *s)
{
    return s->items[s->top-1];
    //returning the last element in the stack
}

//-----------------------------------------------------------------------------------------
//---------------------------------------------------------------- Checks If Stack Is Empty

int isEmpty(stack *s)
{
    if(s->top==0)
        return 1;
    else
        return 0;
    //check if the  is empty
}

////-----------------------------------------------------------------------------------------
//------------------------------------- Calculates According To The Function Of Each Operator

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

//-----------------------------------------------------------------------------------------
//---------------------------------------------------------- Checks If An Operator Is Found

int isOperator(const char* character)
{
    switch (character[0])
    {
        case '-':case '+':case '/':case '*':case '^':case '%':case '(':case ')': return 1;
        default: return 0;
    }
}

//-----------------------------------------------------------------------------------------
//---------------------------------------------------- Assigns Precedence for each operator

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

//-----------------------------------------------------------------------------------------
//-------------------------------------------------------- Evaluates The PostFix Expression

float evaluate_postfix(char *expression,Node *root)
{
    stack *s=initialize();
    Item i1,i2,value;
    float op1,op2,val;
    char *token=strtok(expression," ");

    // loop through the string to extract all the other tokens
    while( token )
    {
        //If An Operator is Found:
        if(strlen(token)==1 && isOperator(token))
        {
            //POP The Operand From stack, Calculate the operation & push the value
            i2=pop(s);op2=i2.fData;
            i1=pop(s);op1=i1.fData;
            val=calculate(token[0],op1,op2);
            value.fData = val;
            push(s,value);
        }
        else
        {
            //If 1st element of Token Is a Letter (variable found):
            if (isalpha(token[0]))
            {
                //Search For This Variable
                Node *n=search(root,token);

                //If Variable Not Found:
                if (!n)
                {
                    //Prints an Error Alert for The User That Variable is Not Found
                    ERROR("[Stack Evaluation]:Variable \"%s\" NOT FOUND !",token);
                    exit(-1);
                }

                //Assign The Value of The Variable To fData of operand
                i1.fData=n->value;
            }
            else i1.fData=strtof(token,NULL);

            //Push The Value to the Stack
            push(s,i1);
        }
        token = strtok(NULL, " ");
    }

    //Pop Value From Stack until stack is Empty
    value = pop(s);val = value.fData;

    //If Stack Is Still Not Empty:
    if (!isEmpty(s))
        //Prints an Error Alert for The User That Expression Is Invalid
        ERROR("[Stack Evaluation]:INVALID EXPRESSION EVALUATED");

    free(s);

    //Returns the Evaluated PostFix Value Of Expression
    return val;

}

//-----------------------------------------------------------------------------------------
//------------------------------------------------- Puts The Expression In The Right Format

char* format(char *expression)
{
    VERBOSE("[Format] Formatting The Expression");
    VERBOSE("[Format] Before \"%s\"",expression);

    //Allocating Double its Size For The WorstCase Compressed Equation
    char *formattedRHS=malloc(strlen(expression) * 2);

    //Clearing the Formatted RHS String
    strcpy(formattedRHS, "");

    for(int i=0;i<strlen(expression);i++)
    {
        char c=expression[i];

        //If '-' is Considered As a Negative Sign Not an Operator:
        if(( c == '-' && (i==0||isOperator(&expression[i-1])))||(!isOperator(&c)))
        {
            //Concatenates The '-' To The Formatted RHS String
            strncat(formattedRHS, &c, 1);
        }
        else
        {
            //Concatenates Operands & Operators To The Formatted RHS String & Adding Spaces
            strcat(formattedRHS, " ");
            strncat(formattedRHS, &c, 1);
            strcat(formattedRHS, " ");
        }
    }

    //ReAllocating To The Proper Size Of The String
    formattedRHS = (char*)realloc(formattedRHS, strlen(formattedRHS)+1);

    VERBOSE("[Format] After \"%s\"",formattedRHS);

    //Return The Formatted Expression with Spaces
    return formattedRHS;
}

//-----------------------------------------------------------------------------------------
//------------------------------------ Reform & Change The Expression From InFix to PostFix

char * infixToPost(char *infix)
{
    char *postfix=malloc(strlen(infix)+1);
    int i = 0;
    stack *s = initialize();
    VERBOSE("[infixToPost] Stack Initialized");

    //Initiate:
    VERBOSE("[infixToPost] infix \"%s\" ",infix);
    
    strcpy(postfix,"");
    char *token=strtok(infix," ");

    //Loop Through The String To Extract All The Other Tokens
    while(token)
    {
        //If An Operator Is Found:
        if(strlen(token)==1 && isOperator(token))
        {
            Item myItem ;
            char op[]=" ";

            VERBOSE("[infixToPost %d] Operator [%c]",i++,token[0]);

            myItem.cData = token[0];
            if (token[0]==')')
            {
                while(peek(s).cData != '(' && !isEmpty(s))
                {
                    VERBOSE("[infixToPost %d] peek [%c]",i++,peek(s).cData);
                    op[0] = pop(s).cData;
                    strcat(postfix,op);
                    strcat(postfix," ");
                    op[0] = ' ';
                }
                pop(s);
            }
            else if (isEmpty(s) || precedence(token[0]) > precedence(peek(s).cData) || (!isEmpty(s) && peek(s).cData == '('))
            {
                VERBOSE("[infixToPost %d] [%c] precedence %d | isEmpty %d "
                        , i++, myItem.cData, precedence(myItem.cData),isEmpty(s));
                push(s, myItem);
                VERBOSE("[infixToPost %d] Pushed %c ",i++,peek(s).cData);

            }
            else if (precedence(token[0])<=precedence(peek(s).cData))
            {
                VERBOSE("[infixToPost %d] [%c] precedence %d < %d | isEmpty %d ",
                         i++,myItem.cData, precedence(myItem.cData), precedence(peek(s).cData),isEmpty(s));
                while(precedence(token[0])<=precedence(peek(s).cData) && !isEmpty(s))
                {
                    op[0] = pop(s).cData;
                    strcat(postfix,op);
                    strcat(postfix," ");
                    op[0] = ' ';
                }
                push(s, myItem);
            }
        }
        //Operand Is Found:
        else
        {
            VERBOSE("[infixToPost %d] Operand [%s] ",i++,token);
            strcat(postfix,token);
            strcat(postfix," ");
        }
        token = strtok(NULL, " ");
    }
    // Popping All The Stack
    char op[]=" ";
    while (!isEmpty(s))
    {
        op[0] = pop(s).cData;
        strcat(postfix,op);
        strcat(postfix," ");
        op[0] = ' ';
    }
    VERBOSE("[infixToPost] Stack is Empty");
    free(s);
    VERBOSE("[infixToPost] Stack Freed");
    return postfix;
}

