#include <stdio.h>
#include <stdlib.h>

//one-dimension array equal point is ok for type argument
//*p or p[] is ok
void onedimension(int *p, int size)
{
    int i;

    for (i = 0; i < size; i++) {
        p[i] = i;
    }
}

// runtime: **p ===> can not show layout of array memory
// invalid use of array with unspecified bounds ===> (*p)[]
void twodimension(int (*p)[5], int row, int col)
{
    int i, j;

    printf("sizeof(*p) = %ld\n", sizeof(*p));
    printf("sizeof(p) = %ld\n", sizeof(p));

    //(*p)++; ===> lvalue required as increment operand
    //(*p): the addr of one dimension array
    //**p: the data of two dimension array
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            //Segmentation fault (core dumped)
            //p[i][j] = i * col + j;

            //p[i][j] = i * col + j; //it is ok for (*p)[]
            (*p)[j] = i * col + j;

            // **p = i * col + j;
            //p++;
        }
        p++;
    }
}


#if 0
//compile error: p[][] or p[2][]
//OK:p[2][5] or p[][5]
void twodimension(int p[][5], int row, int col)
{
    int i, j;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            p[i][j] = i * col + j;
        }
    }
}
#endif

int main()
{
    int array[10] = {0};
    int twoarray[2][5] = {0};
    int i, j;

    onedimension(array, 10);

    for (i = 0; i < 10; i++) {
        printf("%d ", array[i]);
    }

    printf("\n");

    ////////////////////////////////////////////////////
    twodimension(twoarray, 2, 5);

/*
    //onedimension(twoarray, 10); OK
    int * p  = twoarray; //OK
    for (i = 0; i < 10; i++)
        printf("%d ", p[i]);

    printf("\n");
*/

    /*failed
    int **p = NULL;
    p = array;
    *p = &array[0];
    */

    typedef int (*ARRPOINT)[5]; //OK
    //typedef ((int*)[5]) ARRPOINT; //failed
    //int (*p)[5]; //OK
    ARRPOINT p;
    p = (ARRPOINT)(&array[0]);//OK
    //p = ((int *)[5])(&array[0]);//failed
    //p = ARRPOINT(&array[0]);//failed

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 5; j++) {
            //printf("%d ", twoarray[i][j]); //OK
            printf("%d ", p[i][j]); //Segmentation fault (core dumped)
        }
        printf("\n");
    }

    /////////////////////////////////////////////////////////////////////////
    int ** arr;

    arr = (int **) malloc(2 * sizeof(int *));
    (*arr) = (int *) malloc(sizeof(int) * 5);
    (*(arr+1)) = (int *)malloc(sizeof(int) * 5);
    printf("%p\n", &arr);
    printf("%p\n", arr);
    printf("%p\n", *arr);
    printf("%p\n", *(arr+1));

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 5; j++) {
            (*(arr+i))[j] = i * 5 + j;
        }
    }

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 5; j++) {
            printf("%d ", (*(arr+i))[j]);
        }
    }

    printf("\n");

    if (*arr)
        free(*arr);

    if (*(arr+1))
        free(*(arr+1));

    if (arr)
        free(arr);

    return 0;
}
