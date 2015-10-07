#include <CallStack.h>
#include <stdio.h>
#include <stdlib.h>

void do_backtrace()
{
    printf("enter into %s\n", __FUNCTION__);
    android::CallStack stack;
    stack.update(1);
    stack.log("test");
    printf("leave from %s\n", __FUNCTION__);
}

void show()
{
    printf("enter into %s\n", __FUNCTION__);
    do_backtrace();
    printf("leave frome %s\n", __FUNCTION__);
}

int main()
{
    show();
    return 0;
}
