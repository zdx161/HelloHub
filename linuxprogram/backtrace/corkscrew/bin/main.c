#include <stdio.h>

extern void test_backtrace();

void show()
{
    test_backtrace();
}

void fun1()
{
    show();
}

void fun2()
{
    fun1();
}

void fun3()
{
    fun2();
}

int main()
{
    fun3();
    return 0;
}
