#include "AbstractFactoryClient.h"

using namespace AbstractFactory;


AbstractFactoryClient::AbstractFactoryClient(AbstractFactoryServer * af)
{
    b = af->CreateButton();
    t = af->CreateText();
}

void AbstractFactoryClient::Click()
{
    if (b)
        b->Click();
}

void AbstractFactoryClient::DoubleClick()
{
    if (b)
        b->DoubleClick();
}

AbstractFactoryClient::~AbstractFactoryClient()
{
    if (b)
        delete b;

    if (t)
        delete t;
}
