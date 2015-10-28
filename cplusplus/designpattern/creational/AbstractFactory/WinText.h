#pragma once

#include <iostream>
#include "Text.h"

namespace AbstractFactory {

class WinText : public Text {

public:
    WinText()
    {
        using namespace std;
        cout << "Text for Windows OS" << endl;
    }

    virtual ~WinText(){}

};

}
