#include <stdio.h>

#pragma pack(1) //set one byte aligned

typedef struct {
    char a;   //1
    int b;    //4
    double c; //8
    short d;  //2
} TEST;

//real size: 1 + 4 + 8 + 2 = 15
//aligned(4): 4 + 4 + 8 + 4 = 20
//aligned(8): 4 + 4 + 8 + 8 = 24
//aligned(16): 4 + 4 + 8 + 16 = 32

#pragma pack() //cancel minimux aligned

typedef struct {
    char a;
    int b;
    double c;
    short d;
} TS;

//gnu c attribute
//aligned for up to default
//packed for down to default
typedef struct {
    char a;
    int b;
    double c;
    short d;
}__attribute__((packed)) GNUA;
//packed(1) ===>(X)
//__packed__ ===>(OK)

typedef struct {
    char a;
    int b;
    double c;
    short d;
}__attribute__((aligned(4))) GNUB;


int main()
{
    TEST a;
    printf("a size:%ld\n", sizeof(a));
//#pragma pack():size of a is same as b, #pragma is preprocess, not runtime
    TEST b;
    printf("b size:%ld\n", sizeof(b));

    TS c; //-m32:32bit->20; default:64bit->24
    printf("c size:%ld\n", sizeof(c));

    GNUA ga;
    printf("gnua size:%ld\n", sizeof(ga));

    GNUB gb;//sizeof ld for 64, d for 32
    printf("gnua size:%ld\n", sizeof(gb));

    return 0;
}
