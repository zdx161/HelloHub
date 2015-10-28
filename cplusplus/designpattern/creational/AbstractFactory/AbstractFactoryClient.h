#pragma once

#include "AbstractFactoryServer.h"
#include "WinFactory.h"
#include "UnixFactory.h"

namespace AbstractFactory {

class AbstractFactoryClient {

public:
    AbstractFactoryClient(AbstractFactoryServer * af);

    void Click();
    void DoubleClick();

    ~AbstractFactoryClient();

private:
    Button * b;
    Text * t;

};

}
