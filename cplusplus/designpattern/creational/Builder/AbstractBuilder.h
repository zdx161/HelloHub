#ifndef ABSTRACT_BUILDER_H
#define ABSTRACT_BUILDER_H

#include "ProgramFile.h"

namespace Builder {

class AbstractBuilder {

public:
    AbstractBuilder() {
#ifdef _DEBUG
        std::cout << __FUNCTION__ << std::endl;
#endif
    }

    virtual void CreateHeaderFile() = 0;
    virtual void CreateProgramFile() = 0;
    virtual void CreateMakeFile() = 0;
    virtual ProgramFile * GetProgramFile() = 0;

    virtual ~AbstractBuilder(){
        #ifdef _DEBUG
        std::cout << __FUNCTION__ << std::endl;
        #endif
    }
};

}
#endif
