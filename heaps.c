#include <stdio.h>
#include "heaps.h"

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------- Swap
#define swap(x,y) {variable temp=x;x=y;y=temp;}

//-------------------------------------------------------------------------------------------
//------------------------------------------------------------- Swapping Node With Its Parent
void siftUP(variable hp[], int i)
{
    if (i>0) {
        int parent = (i-1)/2;
        if (hp[parent].value>hp[i].value ) {
            swap(hp[i],hp[parent])
            siftUP(hp, parent);
        }
    }
}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------- Prints The Array
void printArray(variable *arr,unsigned long n){
    int i=0;
    while(i<n) {
        printf("%s = %.2f \n",arr[i].name,arr[i].value);
        i++;
    }
}

//-------------------------------------------------------------------------------------------
//------------------------------------------------------------------ Sifting Up Every Element
void heapifyUp(variable *hp,unsigned long n){
    for (int i=1;i<n;i++)

    {siftUP(hp,i);}
}

//-------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Heapify Down
void heapifyDown(variable *arr,int n){
    int i;
    for ( i = 1; i < n; i++)
        // if child is bigger than parent
        if (arr[i].value > arr[(i-1)/2].value)
        { int j = i;
            // swap child and parent until parent is smaller
            while (arr[j].value > arr[(j-1)/2].value)
            {
                swap(arr[j], arr[(j-1)/2])
                j = (j-1)/2;
            }
        }
}

//-------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- Sorts The Heap
void heapSort(unsigned long n,variable arr[n]){
    heapifyDown(arr, n);
    for (int i = n - 1; i > 0; i--)
    {
        // swap value of first indexed with last indexed
        swap(arr[0], arr[i])
        // maintaining heap property after each swapping
        int j = 0, index;
        do
        {
            index = (2 * j + 1);
            // if left child is smaller than right child point to right
            if (arr[index].value<arr[index + 1].value && index < (i - 1))index++;
            // if parent is smaller than child then swap parent with child
            if (arr[j].value<arr[index].value && index < i) swap(arr[j], arr[index])
            j = index;
        } while (index < i);
    }
}


