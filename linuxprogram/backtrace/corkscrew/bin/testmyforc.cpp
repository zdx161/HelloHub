#include <stdio.h>
#include <CallStack.h>
#include <testmyforc.h>

void test_backtrace()
{
    printf("+%s\n", __FUNCTION__);
    android::CallStack stack;
    stack.update(1);
    stack.log("test");
    printf("-%s\n", __FUNCTION__);
}
