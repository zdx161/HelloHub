#include <stdio.h>

//char a:16; error: width of ‘a’ exceeds its type
typedef struct {
    int a:8; //8 is num of bits
    int b:8;
    int c:8;
    int d:8;
} TEST;

TEST test()
{
    TEST a = {0};

    a.a = 16;
    a.b = 32;
    a.c = 64;
    a.d = 128;

    return a;
}

//int atest()[] //error: ‘atest’ declared as function returning an array
int  * atest()
{
    int i;
    int a[5] = {0};

    for (i = 0; i < 5; i++) {
        a[i] = i * 10;
    }

    return a; //function returns address of local variable [enabled by default]
}

//array is different from struct
//struct can be assigned, but array is not
int main()
{
    TEST a;
    int *b;
    int c;
    int d[5] = {0};
    float sum = 0.;
    int i;

    printf("size: %ld\n", sizeof(a));

    a = test();
    //c = (int)a; error: aggregate value used where an integer was expected
    b = (int *)&a; //OK

    printf("0x%x \n", *b);

    for (i = 0; i < 20; i++) {
        sum += 0.4;
    }

    printf("%f \n", sum);

    return 0;
}
