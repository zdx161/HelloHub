/** ****************************************************************
 ** Merge sort(also commonly spelled mergesort): is an O(nlogn) 
 ** comparison-based sorting algorithm.
 **
 ** wikipedia link: http://en.wikipedia.org/wiki/Merge_sort
 ** ***************************************************************/
#include <stdio.h>
#include <stdlib.h>


void merge(int * const data, int p, int q, int r)
{
    int i,j,k;
    int n1 = q - p;
    int n2 = r - q + 1;
    int *d1 = (int *)calloc(1, n1*sizeof(int));
    int *d2 = (int *)calloc(1, n2*sizeof(int));
    for(i = 0; i < n1; i++){
        d1[i] = data[i];
    }
    for(i = 0; i < n2; i++){
        d2[i] = data[n1+i];
    }
    
    j = k =0;

    for(i = 0; i < n1 + n2; i++){
        if(j >= n1 && k < n2){
            data[i] = d2[k];
            k++;
        }
        else if(k >= n2 && j < n1){
            data[i] = d1[j];
            j++;
        }
        else if(d1[j] <= d2[k]){
            data[i] = d1[j];
            j++;
        }else{
            data[i] = d2[k];
            k++;
        }
    }

    free(d1);
    free(d2);
}

void merge_sort(int * const data, int p, int q)
{
    int mid = (p + q + 1) / 2;
    if(q > p){
        merge_sort(data, p, mid -1);
        merge_sort((data + (mid - p)), mid, q);
        merge(data, p, mid, q);
    }else{
       //do nothing
       return ;
       // merge(data, p, mid, q);
    }
}

int main(){
    int d1[10] = {2,5,1,3,0,4,6,9,7,8};
    //int d1[5] = {2,5,1,3,0};
    int size = 10;
    merge_sort(d1, 0, size - 1);

    int i;
    for(i = 0; i < size; i++){
        printf("%d, ", d1[i]);
    }
    printf("\n");

    return 0;

}
