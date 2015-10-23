#pragma once
#include "ProductMethod.h"

namespace FactoryMethod {

class PhoneFactory {
public:
    PhoneFactory();
    virtual ~PhoneFactory();
    virtual ProductMethod * getProduct() = 0;
};

}
