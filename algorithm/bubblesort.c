/**************************************************************
 *
 *
 *
 * compile option: -std=c99
 *************************************************************/
#include <stdio.h>

//bubble: first sort big data, cross interchange data
void bubblesort(int *data, int size)
{
    if (size <= 1) {
        printf("%d numbers need not to sort!\n", size);
        return;
    }

    int i, j, temp;
    for (i = 0; i < size - 1; i++) {
        for (j = size - 1; j > i; j--) {
            if (data[j - 1] > data[j]) {
                temp = data[j - 1];
                data[j - 1] = data[j];
                data[j] = temp;
            }
        }
    }
}

int main()
{
    int data[10] = {9, 2, 1, 6, 4, 7, 5, 3, 0, 8};

    bubblesort(data, 10);

    int i;
    for (i = 0; i < 10; i++) {
        printf("%d ", data[i]);
    }

    printf("\n");

    return 0;
}
