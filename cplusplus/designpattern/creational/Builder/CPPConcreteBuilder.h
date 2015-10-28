#ifndef CPP_CONCRETE_BUILDER_H
#define CPP_CONCRETE_BUILDER_H

#include "AbstractBuilder.h"

namespace Builder {

class CPPConcreteBuilder : public AbstractBuilder {

public:
    CPPConcreteBuilder();
    virtual void CreateHeaderFile();
    virtual void CreateProgramFile();
    virtual void CreateMakeFile();
    virtual ProgramFile * GetProgramFile();

    virtual ~CPPConcreteBuilder();

private:
    ProgramFile * gpf;


};

}
#endif
