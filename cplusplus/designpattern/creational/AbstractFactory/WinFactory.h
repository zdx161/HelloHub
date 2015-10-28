#pragma once

#include "WinButton.h"
#include "WinText.h"
#include "AbstractFactoryServer.h"

namespace AbstractFactory {

class WinFactory : public AbstractFactoryServer {
public:
    WinFactory();

    virtual Button *CreateButton();
    virtual Text * CreateText();

    virtual ~WinFactory();
};

}
