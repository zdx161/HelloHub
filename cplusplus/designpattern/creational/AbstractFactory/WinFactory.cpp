#include "WinFactory.h"

using namespace AbstractFactory;

WinFactory::WinFactory()
{
    std::cout << "construct Windows Factory" << std::endl;
}

Button * WinFactory::CreateButton()
{
    return new WinButton();
}


Text * WinFactory::CreateText()
{
    return new WinText();
}

WinFactory::~WinFactory()
{
}
