#pragma once

#include "PhoneFactory.h"
#include "HtcM9Phone.h"

namespace FactoryMethod {

class HtcM9Factory : public PhoneFactory {
public:
    HtcM9Factory();
    virtual ~HtcM9Factory();
    virtual ProductMethod * getProduct();
};

}
