#ifndef PROTOTYPE_KFC_H
#define PROTOTYPE_KFC_H

#include <string>

namespace Prototype {

class PrototypeKFC {

public:

    virtual PrototypeKFC * clone() = 0;
    virtual ~PrototypeKFC();
};

}

#endif
