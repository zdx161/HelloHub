#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159267

void dct(float (*data)[4],  int row, int col)
{
    int i,j;
    for (i = 1; i <= row; i++) {
        for (j = 1; j <= col; j++) {
            data[i-1][j-1] = cos((float)(i - 1) * (2 * j - 1) * PI / 8) * sqrt((float)2/4);
        }
    }

    for (i = 1; i <= row; i++) {
        //data[0][i-1] = data[0][i-1] / sqrt((float)2);
    }

}

#ifdef TEST
int main()
{

#if 0
    float **data;
    data = (float **)malloc(4 * sizeof(float *));
    int x;
    for (x = 0; x < 4; x++)
    data[x] = (float *)malloc(4 * sizeof(float));
#endif

    float data[4][4] = {{1,1,1,1}, {1,0,0,1}, {1,0,0,1}, {1,1,1,1}};

    dct(data, 4, 4);

    int i,j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            printf("%f ", data[i][j]);
        }

        printf("\n");
    }
#if 0
    if(data != NULL) {
        if (*data != NULL) {
            for(i = 0; i < 4; i++)
            free(data[i]);
        }
        free(data);
    }
#endif
    return 0;
}
#endif
