#include <stdio.h>
#include "heaps.h"


void siftUP(variable hp[], int i)
{
    if (i>0) {
        int parent = (i-1)/2;
        if (hp[parent].value>hp[i].value ) {
            variable t=hp[i];hp[i]=hp[parent];hp[parent]=t;//swap
            siftUP(hp, parent);
        }
    }
}

void printArray(variable *arr,int n){
    int i=0;
    while(i<=n) {
        printf("%s = %.2f \n",arr[i].name,arr[i].value);
        i++;
    }
    printf("\n");
}

void heapifyUp(variable *hp,int n){ // O(n log(n))
    for (int i=1;i<n;i++)

    {siftUP(hp,i);}

}

#define swap(x,y) {variable temp=x;x=y;y=temp;}


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

void heapSort(int n,variable arr[n]){ // 0 base indexing
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



