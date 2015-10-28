#ifndef DIRECTOR_H
#define DIRECTOR_H

#include "AbstractBuilder.h"

namespace Builder {

class SoftWareEngineer {

public:
    SoftWareEngineer()
    {
#ifdef _DEBUG
        std::cout << __FUNCTION__ << std::endl;
#endif
    }

    void Programme(AbstractBuilder * ab);

    ~SoftWareEngineer()
    {
#ifdef _DEBUG
        std::cout << __FUNCTION__ << std::endl;
#endif
    }
};

}
#endif
