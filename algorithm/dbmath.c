#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//db = 20log(s/n)
//s/n = 10 ^ (db/20)
int main()
{
    int db;
    //16bits
    
    double maxvald = (double)((1 << 15) - 1);
    int maxvali = (1 << 15) - 1;
    printf("maxvald = %lf, maxvali = %d\n", maxvald, maxvali);
    for(db = 0; db < 16*6; db++){
        double val = pow((double)10, -((double)db)/((double)20));
        printf("s/n of %ddb is %lf, maxval1: %lf : %d  maxval2: %d\n", db, val, val * maxvald, (int)(val * maxvald + 0.5f) ,(int)(maxvali * val)); 
    }


    //-3db
    double db3 = pow((double)10, ((double)3)/((double)20));
    printf("3db: %lf, %lf\n", db3, 1/db3);
    double t =  pow((double)10, -((double)3)/((double)20));
    printf("%lf\n", t);


    return 0;

}
