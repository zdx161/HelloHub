#pragma once

#include <iostream>

namespace AbstractFactory {

class Button{
public:

    virtual void Click() = 0;

    virtual void DoubleClick() = 0;

    virtual ~Button(){}
};

}
