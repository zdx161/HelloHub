#include <stdio.h>

#define PRINT(fmt, ...) printf("[%s,%d]"fmt"\n", __func__, __LINE__, ## __VA_ARGS__)

int main()
{
    printf("%s\n", __func__);
    printf("clanguage practice\n" + 12); //actice
    PRINT("test for variable arguments");
    return 0;
}
