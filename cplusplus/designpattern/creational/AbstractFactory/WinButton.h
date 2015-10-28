#pragma once

#include "Button.h"
#include <iostream>

namespace AbstractFactory {

class WinButton : public Button {

public:
    WinButton()
    {
        std::cout << "Button for Windows OS" << std::endl;
    }

    void Click()
    {
        std::cout << "single click on Windows OS " << std::endl;
    }

    void DoubleClick()
    {
        std::cout << "double click on Windows OS " << std::endl;
    }

    virtual ~WinButton(){}
};

}
