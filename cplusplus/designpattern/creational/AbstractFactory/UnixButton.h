#pragma once

#include "Button.h"

namespace AbstractFactory {

class UnixButton : public Button {

public:
    UnixButton()
    {
        using namespace std;
        cout << "Button for Unix OS" << endl;
    }

    void Click()
    {
        std::cout << "single click on Unix OS " << std::endl;
    }

    void DoubleClick()
    {
        std::cout << "Double Click on Unix OS " << std::endl;
    }

    virtual ~UnixButton(){}

};

}
