#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159267

void resample(int Herz)
{
    double t;
    int i;
    double period = 1 / ((double)Herz);

    for (i = 0, t = 0.0; t < 1.0; t += period, i++) {
        printf("%lf\t", 2 + 3 * cos((double)2*PI*50*t-(double)PI*30/((double)180)) \
                    + 1.5*cos((double)2*PI*75*t+(double)PI*90/((double) 180)));
        if (i > 0 && (i+1) % 8 == 0)
            printf("\n");
    }
}


#ifdef TEST
int main()
{
    resample(256);

    return 0;
}
#endif
