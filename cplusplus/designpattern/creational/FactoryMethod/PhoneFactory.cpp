#include "PhoneFactory.h"
#include <iostream>

namespace FactoryMethod{
PhoneFactory::PhoneFactory()
{
    std::cout << __FUNCTION__ << std::endl;
}

PhoneFactory::~PhoneFactory()
{
    std::cout << __FUNCTION__ << std::endl;
}

}
