#include "UnixFactory.h"

using namespace AbstractFactory;


UnixFactory::UnixFactory()
{
    using namespace std;
    cout << "Unix Factory" << endl;
}

UnixFactory::~UnixFactory()
{
}

Button * UnixFactory::CreateButton()
{
    return new UnixButton();
}


Text * UnixFactory::CreateText()
{
    return new UnixText();
}
