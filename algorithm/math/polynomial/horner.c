#include <stdio.h>


double nest(int degree, double * coeff, double x, double * base)
{
    int i;
    double y = 1.;

    y = coeff[0];

    for (i = 1; i <= degree; i++) {
        y = y * (x - (base!=NULL?base[i - 1]:0)) + coeff[i];
    }

    return y;
}

int main()
{
    int degree = 4;
    double coeff[5] = {2, 3, -3, 5, -1};
    double x = 0.5; //1/2 != 0.5
    double base[4] = {0};
    double test;

    printf("%lf \n", nest(degree, coeff, x, base));

    test = 1./2; //1./2 or 1/2. == 0.5
    printf("%lf \n", test);

    test = 1 / (double)2; //(double)1 / 2 == 1 / (double)2 == 0.5
    printf("%lf \n", test);

    return 0;
}
