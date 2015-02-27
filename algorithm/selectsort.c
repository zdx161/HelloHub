/***********************************************************************
 *
 *
 *
 *
 ***********************************************************************/

#include <stdio.h>

void selectsort(int *data, int size)
{
    if (size <= 1) {
        printf("size: %d, need not to sort\n", size);
        return;
    }

    int i, j, index, tmp;
    for (i = 0; i < size - 1; i++) {
        index = i;
        for (j = i + 1; j < size; j++) {
            if (data[j] < data[index]) {
                index = j; //use index to minimize frequency of interchange data.
            }
        }
        if (index != i) {
            tmp = data[i];
            data[i] = data[index];
            data[index] = tmp;
        }
    }
}


int main()
{
    int data[10] = {9, 2, 1, 6, 4, 7, 5, 3, 0, 8};

    selectsort(data, 10);

    int i;
    for (i = 0; i < 10; i++) {
        printf("%d ", data[i]);
    }

    printf("\n");

    return 0;
}
