#include "AbstractFactoryServer.h"
#include "AbstractFactoryClient.h"
#include "WinFactory.h"
#include "UnixFactory.h"

using namespace AbstractFactory;


int main()
{
    AbstractFactoryServer *af = new WinFactory();

    AbstractFactoryClient * afc = new AbstractFactoryClient(af);

    afc->Click();
    afc->DoubleClick();

    delete afc;
    delete af;

    return 0;
}
