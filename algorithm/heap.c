/** *************************************************
 **         root = 1
 **         value(i) = x[i]
 **         leftchild(i) = 2 * i
 **         rightchild(i) = 2 * i + 1
 **         parent(i) = i / 2;
 **         null(i) = (i < 1) or (i > n)
 ** ***********************************************/
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1025 //n = log1024 = 10, index 0 not used

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void siftup(int *heap, int index, int node)
{
    int i;
    if (index == 1) {
        heap[1] = node;
        return;
    }

    if (index >= MAXSIZE) {
        printf("error: heap is full.\n");
        return;
    }

    heap[index] = node;
    for (i = index; i > 0; i = i/2) {
        if(heap[i/2] > heap[i])
            swap(&heap[i/2], &heap[i]);
        else
            break;
    }

}

void siftdown(int *heap, int index, int node)
{
    int i, condition;
    if (index == 1) {
        heap[index] = node;
        return;
    }

    for (i = index; i > 1; i--) {
        heap[i] = heap[i - 1]; //empty the first data site for new node.
    }

    heap[i] = node; //assign data to the first site.
    for (i = 1; condition = i; ) { //sift down sort
        if (index >= i * 2 && heap[i] > heap[i*2]) {
            swap(&heap[i], &heap[i * 2]);
            i = i * 2;
        }

        if (index >= i * 2 + 1 && heap[i] > heap[i * 2 + 1]) {
            swap(&heap[i], &heap[i * 2 + 1]);
            i = i * 2 + 1;
        }

        if(i == condition)
            break;
    }
}

int main()
{
    int i;
    int heap[MAXSIZE] = {0};
    int heap1[MAXSIZE] = {0};
    int data[12] = {15,20,29,12,22,17,23,35,40,51,26,19};

    printf("sift up:\n");
    for (i = 0; i < 12; i++) {
        siftup(heap, i+1, data[i]);
    }
    
    for (i = 0; i < 12; i++) {
        printf("%d, ", heap[i+1]);
    }

    printf("\n");

    printf("sift down:\n");
    for (i = 0; i < 12; i++) {
        siftdown(heap1, i + 1, data[i]);
    }

    for (i = 0; i < 12; i++) {
        printf("%d, ", heap1[i+1]);
    }

    printf("\n");

    return 0;
}
