#include "singleton.h"
#include "static.h"
#include <iostream>

namespace Test{
SingleTest * SingleTest::self()
{
    if (gsingleton != NULL)
    {
        return gsingleton;
    }

    gsingleton = new SingleTest;
    return gsingleton;
}


SingleTest::SingleTest()
{
    std::cout << "===construct===" << std::endl;
}

SingleTest::~SingleTest()
{
    std::cout << "===deconstruct===" << std::endl;
}

void SingleTest::print(const char * s)
{
    std::cout << s << std::endl;
}


}
