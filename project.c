#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#define SIZE 100
#define VERBOSE 0
#define TYPE float

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
int validation(char *expression)
{




}
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
    //adding item to the  in the last index
}
void reading(char *name)
{
    FILE *f=fopen(name,"r");
    char expression[100];
    if(!f)
        {
            printf("File doesn't exist");
            exit(-1);
        }
    stack *s=initialize();
    while (!feof(f))
    {
        fscanf(f,"%[^\n]\n",expression);
        char *varName=malloc(strlen(expression)+1);
        strcpy(varName,strtok(expression,"="));
        if(!strcmp(varName,expression))
        {
            printf("%s \n this expression isn't valid ",expression);
            exit(-1);
        }
        char *postfix=malloc(strlen(expression)+1);
     //   postfix=infixToPost(expression,)


    }


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

int isfull(stack *s)
{
    if(s->top==SIZE)
        return 1;
    else
        return 0;
    //check if the  is full  SIZE=100
}


float calculate (char x,float op1,float op2)
{
    switch (x)
    {
        case '+':return op1+op2;
        case '-':return op1-op2;
        case '/':return op1/op2;
        case '*':return op1*op2;
        case '%':return (int)op1 %( int)op2;
        case '^':return pow(op1,op2);
        default: return 0;
    }
}

int isOperator(char* character)
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

float evaluate_postfix(char *expression)
{
    stack *s=initialize();
    Item i1,i2,value;
    float op1,op2,val;
    char *token=strtok(expression," ");
    // loop through the string to extract all other tokens
    while( token )
    {
        //printf( "%s\n", token );
        // printing each token
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
            i1.fData=strtof(token,NULL);
            push(s,i1);
        }
        token = strtok(NULL, " ");
    }
    value = pop(s);val = value.fData;
    if (!isempty(s))
    {
        printf("INVALID EXPRESSION !");
        exit(-1);
    }
    free(s);
    return val;

}

char* format(char *expression)
{
    char *varname=malloc(100);
    strcpy(varname,"");
    int i;
    for(i=0;i<strlen(expression);i++)
    {
        char x=expression[i];
        if(i==0 && x=='-')
        {
            printf("%s\n",expression);
            strncat(varname,&x,1);
             continue;
        }
        if(!isOperator(&x))
           {
            strncat(varname,&x,1);
           }
        else if(isOperator(&expression[i-1])==1&&x=='-')
              {
                  strncat(varname,&x,1);
              }
       // else if(isOperator[i-1]==0&&(isOperator(expression[i])==1||isOperator(expression[i])==2))
        else
            {
                strcat(varname," ");
                strncat(varname,&x,1);
                strcat(varname," ");
            }
    }
    return varname;
}

void infixToPost(char *infix, char *postfix)
{
    int i = 0;
    stack *s = initialize();
    if (VERBOSE) printf("\n[infixToPost] Stack Initialized\n");

    //initiate:
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



///////////////////////////////////////////////////////////////////////
/*typedef struct
{
    char *varName;
    float value;
    struct  Node* left;
    struct Node*right;
} Node;
Node* newNode(char *w,float value)
{
    Node* n=malloc(sizeof(Node));
    n->varName=malloc(strlen(w)+1);
    strcpy(n->varName,w);
    n->value=value;
    n->left=NULL;
    n->right=NULL;
    return n;
}
Node* insert(Node* Root,char* key,float value)
{
    if(Root==NULL)
        return newNode(key,value);
    else if(strcasecmp(key,Root->varName) > 0)
        Root->right=insert(Root->right, key);
    else
        Root->left=insert(Root->left, key);
    return Root;
}
Node* search(Node* root,char *w)
{
    if(root==NULL||w==NULL)
        return NULL;
    else if (strcasecmp(root->varName,w)==0)
        return root;
    else if(strcasecmp(root->varName,w)>0)
    {
        if(root->left==NULL)
            return root;
        else
            return search(root->left,w);
    }

    else
    {
        if(root->right==NULL)
            return root;
        else
            return search(root->right,w);
    }
}
*/


int main()
{
    char*t="2+(-2.5+3.14)*(-5.4+8.1)^(-0.5)";
    char i[100];
    infixToPost(format(t),i);
    printf("Result = %f\n",evaluate_postfix(i));
    return 0;
}
