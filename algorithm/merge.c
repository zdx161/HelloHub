#include <stdio.h>
#include <stdlib.h>


void merge(int *data, int p, int q, int r)
{
    int i,j,k;
    int n1 = q - p + 1;
    int n2 = r - q;
    int *d1 = (int *)calloc(1, n1*sizeof(int));
    int *d2 = (int *)calloc(1, n2*sizeof(int));
    memcpy(d1, data, n1*sizeof(int));
    memcpy(d2, data+(n1*sizeof(int)), n2*sizeof(int));
    
    j = k =0;
    for(i = 0; i < n1 + n2; i++){
        if(j >= n1 && k < n2){
            data[i] = d2[k];
        }
        else if(k >= n2 && j < n1){
            data[i] = d1[j];
        }
        else if(d1[j] <= d2[k]){
            data[i] = d1[j];
            j++;
        }else{
            data[i] = d2[j];
            k++;
        }
    }

    free(d1);
    free(d2);
}

void merge_sort(int *data, int p, int q)
{
    int mid = (p + q) / 2;
    if(q - p > 2){
        merge_sort(data, p, mid -1);
        merge_sort(data+mid, mid, q);
    }else{
        merge(data, p, mid, q);
    }
}

int main(){
    int d1[5] = {2,5,1,3,0,4,6,9,7,8};
    merge_sort(d1, 0, 9);

    int i;
    for(i = 0; i < 10; i++){
        printf("%d, ", d1[i]);
    }
    printf("\n");

    return 0;

}
