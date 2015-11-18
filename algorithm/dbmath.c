/** *********************************************************
 ** Decibel(dB): is a logarithmic unit used to express the
 ** ratio between two values of a physical quantity, often
 ** power or intensity.
 **
 ** wikipedia link: http://en.wikipedia.org/wiki/Decibel
 ** ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//db = 20log10(s/n)
//s/n = 10 ^ (db/20)
//1bit = 6db

int main()
{
    int db;
    //16bits
    
    double maxvald = (double)((1 << 15) - 1); //(Most significant bit)MSB is sign
    int maxvali = (1 << 15) - 1;
    printf("maxvald = %lf, maxvali = %d\n", maxvald, maxvali);
    for (db = 0; db < 16*6; db++) {
        double val = pow((double)10, -((double)db)/((double)20));
        printf("s/n of %2ddb is %8.6lf, maxval1: %12.6lf : %5d  maxval2: %5d\n", db, val,
                val * maxvald, (int)(val * maxvald + 0.5f), (int)(maxvali * val)); //+0.5f: do round
    }


    //-3db
    double db3 = pow((double)10, ((double)3)/((double)20));
    printf("3db: %lf, %lf\n", db3, 1/db3);
    double t =  pow((double)10, -((double)3)/((double)20));
    printf("%lf\n", t);


    return 0;
}
