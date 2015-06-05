#include <stdio.h>
#include <string.h>


int main()
{
    char *ptr = NULL;
    char *str = strdup("handleFm=1;xxxx");
    char *tmpstr;
    ptr = strtok_r(str, ";", &tmpstr);
    printf("%s\n", ptr);
    printf("%s\n", tmpstr);

    const char * str2 = "s";
    int data;
    sscanf(&str2[0], "%x", &data);
    printf("data: %x\n", data);

    return 0;
}
