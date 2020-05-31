#ifndef C_INTERPRETER_HEAPS_H
#define C_INTERPRETER_HEAPS_H

//-----------------------------------------------------
//------------------------ A Struct Containing Variable
typedef struct variable
{
    char*  name;
    float value;

} variable;

//-----------------------------------------------------
//----------------------- Swapping Node With Its Parent
void siftUP(variable hp[], int i);

//-----------------------------------------------------
//---------------------------- Sifting Up Every Element
void heapifyUp(variable *hp,unsigned long n);

//-----------------------------------------------------
//---------------------------------------- Heapify Down
void heapifyDown(variable *hp,int n);

//-----------------------------------------------------
//-------------------------------------- Sorts The Heap
void heapSort(unsigned long n,variable arr[]);

//-----------------------------------------------------
//------------------------------------ Prints The Array
void printArray(variable *arr,unsigned long n);

#endif //C_INTERPRETER_HEAPS_H