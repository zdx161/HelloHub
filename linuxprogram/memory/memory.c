#include <stdio.h>
#include <unistd.h>

int main()
{
    unsigned long psize1 = getpagesize();
    printf("system page size1: %ld\n", psize1);

    unsigned long psize2 = sysconf(/*_SC_PAGESIZE*/_SC_PAGE_SIZE);  //_SC_PAGE_SIZE == _SC_PAGESIZE
    printf("system page size2: %ld\n", psize2);

    //printf("system page size3: %ld\n", PAGE_SIZE);

    return 0;
}
