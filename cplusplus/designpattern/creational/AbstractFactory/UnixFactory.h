#pragma once

#include "UnixText.h"
#include "UnixButton.h"
#include "AbstractFactoryServer.h"

namespace AbstractFactory {

class UnixFactory : public AbstractFactoryServer {
public:
    UnixFactory();
    virtual ~UnixFactory();

    Button * CreateButton();
    Text * CreateText();
};

}
