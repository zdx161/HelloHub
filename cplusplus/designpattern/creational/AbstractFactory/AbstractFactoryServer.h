#pragma once

#include "Button.h"
#include "Text.h"

namespace AbstractFactory {

class AbstractFactoryServer{
public:
    AbstractFactoryServer(){}
    virtual Button * CreateButton() = 0;
    virtual Text * CreateText() = 0;

    virtual ~AbstractFactoryServer(){}
};

}
