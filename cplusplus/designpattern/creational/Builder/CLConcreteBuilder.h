#ifndef CL_CONCRETE_BUILDER_H
#define CL_CONCRETE_BUILDER_H

#include "AbstractBuilder.h"

namespace Builder {

class CLConcreteBuilder : public AbstractBuilder {

public:
    CLConcreteBuilder();
    virtual void CreateHeaderFile();
    virtual void CreateProgramFile();
    virtual void CreateMakeFile();
    virtual ProgramFile * GetProgramFile();

    virtual ~CLConcreteBuilder();

private:
    ProgramFile * gpf;

};

}
#endif
