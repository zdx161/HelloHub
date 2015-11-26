#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

#define PI (3.14159265359)

typedef struct {
    int dimsize;
    double * xcoeff;
    double * ycoeff;
} MARRAY; //matrix array

MARRAY * newtondd(double * x, double * y, int n)
{
    int r, c;
    double * xptr, * yptr;
    MARRAY * ma = NULL;

    if (n <= 0) {
        printf("error: there are not number dot to calculate.\n");
        return ma;
    }

    ma = (MARRAY *) calloc(1, sizeof(MARRAY) + n * (n + 1) * sizeof(double));

    if (!ma) {
        printf("error:%s\n", strerror(errno));
        return ma;
    }

    ma->dimsize = n;
    ma->xcoeff = (double *)(&ma[1]);
    ma->ycoeff = ma->xcoeff + (n * sizeof(double));
    xptr = ma->xcoeff;
    yptr = ma->ycoeff;

    for (r = 0; r < n; r++) {
        xptr[r] = x[r];
        yptr[r * n] = y[r];
    }

    //one-dimension can not be accessed by tow-dimension
    for (c = 1; c < n; c++) {
        for (r = 0; r < n - c; r++) {
            yptr[r * n + c] = (yptr[(r + 1) * n + (c - 1)] - yptr[r * n + (c - 1)]) / (x[r + c] - x[r]);
        }
    }

    for (c = 0; c < n; c++) {
        printf("%lf ", yptr[c]);
    }

    printf("\n");

    return ma;
}

double interpolate(MARRAY * ma, double x)
{
    int i, j, n;
    double y = 0., x1;
    double * yptr, * xptr;
    double tmp, sign = 1.;

    if (ma == NULL || ma->dimsize== 0) {
        printf("error: interpolation coeff can not be supply\n");
        return 0;
    }

    //x1 = x % (2 * PI); error:double can not use mod operator
    //imply mod for double as follow.
    x1 = (int)(x * pow(10, 6)) / (int)(2 * (PI * pow(10, 6)));
    x1 = x - (x1 * 2 * PI);
    printf("x1:%lf, x:%lf \n", x1, x);

    if (x1 > PI) {
        x1 = 2 * PI - x1;
        sign = -1.;
    }

    if (x1 > PI / 2) {
        x1 = PI - x1;
    }

    n = ma->dimsize;
    xptr = ma->xcoeff;
    yptr = ma->ycoeff;
    y += yptr[0];

    for (i = 1; i < n; i++) {
        tmp = yptr[i];
        //printf("%lf ", yptr[i]);

        for (j = 0; j < i; j++) {
            tmp *= (x1 - xptr[j]);
            //printf("%lf ", xptr[j]);
        }

        y += tmp;
        //printf("\n");
    }

    return y;
}

int main()
{
    int n = 4, i;
    //double x[n]; error:compile needs static array size.
    double x[4] = {0, PI/6, PI/3, PI/2};
    double y[4] = {0., 0.5, 0.8660, 1.};

    MARRAY * ma = NULL;
    ma = newtondd(x, y, n);

    for (i = 1; i < 5; i++) {
        printf("%lf\n", interpolate(ma, (double)i));
    }

    printf("%lf\n", interpolate(ma, (double)14));
    printf("%lf\n", interpolate(ma, (double)1000));

    if (ma) {
        free(ma);
        ma = NULL;
    }

    return 0;
}
