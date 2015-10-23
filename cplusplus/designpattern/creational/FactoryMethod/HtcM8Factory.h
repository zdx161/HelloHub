#ifndef HTC_M8_FACTORY
#define HTC_M8_FACTORY

#include "PhoneFactory.h"
#include "HtcM8Phone.h"

namespace FactoryMethod {

class HtcM8Factory: public PhoneFactory {
public:
    HtcM8Factory();
    virtual ~HtcM8Factory();
    virtual ProductMethod * getProduct();
};

}

#endif
