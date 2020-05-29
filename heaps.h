
#ifndef C_INTERPRETER_HEAPS_H
#define C_INTERPRETER_HEAPS_H

typedef struct variable
{
    char*  name;
    float value;

} variable;

void siftUP(variable hp[], int i);
void heapifyUp(variable *hp,unsigned long n);
void heapifyDown(variable *hp,int n);
void heapSort(unsigned long n,variable arr[]);
void printArray(variable *arr,unsigned long n);

#endif //C_INTERPRETER_HEAPS_H