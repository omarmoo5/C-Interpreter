
#ifndef C_INTERPRETER_HEAPS_H
#define C_INTERPRETER_HEAPS_H

typedef struct variable
{
    char*   name;
    float value;

} variable;


void siftUP(variable hp[], int i);
void printArray(variable *arr,int n);
void siftDown(variable hp[], int i,int n);
void heapifyDown(variable *hp,int n);
void heapSort(int n,variable arr[]);
void heapifyUp(variable *hp,int n);
#endif //C_INTERPRETER_HEAPS_H
