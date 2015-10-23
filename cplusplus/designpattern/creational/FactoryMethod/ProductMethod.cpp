#include "ProductMethod.h"
#include <iostream>

using namespace FactoryMethod;

ProductMethod::ProductMethod()
{
    std::cout << __FUNCTION__ << std::endl;
}

ProductMethod::~ProductMethod()
{
    std::cout << __FUNCTION__ << std::endl;
}
