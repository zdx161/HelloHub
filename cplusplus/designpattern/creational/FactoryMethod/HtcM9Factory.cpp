#include "HtcM9Factory.h"
#include <iostream>

using namespace FactoryMethod;

HtcM9Factory::HtcM9Factory()
{
    std::cout << __FUNCTION__ << std::endl;
}

HtcM9Factory::~HtcM9Factory()
{
    std::cout << __FUNCTION__ << std::endl;
}

ProductMethod * HtcM9Factory::getProduct()
{
    return new HtcM9Phone();
}
