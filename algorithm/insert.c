/** **************************************************************
 ** Insertion sort: is a simple sorting algorithm that
 ** builds the final sorted array (or list) one item at a
 ** time.
 **
 ** wikipedia link: http://en.wikipedia.org/wiki/Insertion_sort
 ** **************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void insert(int *data, int size)
{
    int i,j,k,tmp;
#if 0
    //myself:
    for(i = 1; i < size; i++){
        for(j = 0; j < i; j++){
            if(data[j] > data[i]){
               tmp = data[i];
               for(k = i; k > j; k--){
                   data[k] = data[k - 1];
               }
               data[k] = tmp;
               break;
            }
        }
    }
#else
    //introduce algorithm
    int key;
    for(i = 1; i < size; i++){
        key = data[i];
        j = i - 1;
        while(j >= 0 && data[j] > key)
        {
            data[j + 1] = data[j];
            j = j-1;
        }
        data[j + 1] = key;
    }
#endif

}

int main(int  argc, char **argv)
{
    int c = 0;
    long size = 0;
    int *data;
    int i;
    char *errstr = NULL;

    while((c = getopt(argc, argv, "n:")) != -1){
        switch(c){
            case 'n':
                size = strtol(argv[optind - 1], NULL, 10);
                printf("size: %ld\n", size);
                break;
            default:
                printf("default option\n");
                break;
        }
    }

    if(size == -1){
        printf("input num is failed.\n");
        exit(EXIT_FAILURE);
    }

    data = (int *)calloc(1, size);
    
    
    srand(10);
    for(i = 0; i < size; i++){
        data[i] = rand()%size;
        printf("%d, ", data[i]);
    }

    printf("\n");
    insert(data, size);
    for(i = 0; i < size; i++){
        printf("%d, ", data[i]);
    }

    printf("\n");


    return 0;
}
