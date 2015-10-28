#pragma once

#include <iostream>
#include "Text.h"

namespace AbstractFactory {

class UnixText : public Text {

public:
    UnixText()
    {
        using namespace std;
        cout << "Text for Unix OS" << endl;
    }

    virtual ~UnixText(){}

};

}
