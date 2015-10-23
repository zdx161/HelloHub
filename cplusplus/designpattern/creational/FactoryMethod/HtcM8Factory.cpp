#include "HtcM8Factory.h"
#include <iostream>

using namespace FactoryMethod;

HtcM8Factory::HtcM8Factory()
{
    std::cout << __FUNCTION__ << std::endl;    
}


HtcM8Factory::~HtcM8Factory()
{
    std::cout << __FUNCTION__ << std::endl;
}

ProductMethod * HtcM8Factory::getProduct()
{
    return new HtcM8Phone();
}
