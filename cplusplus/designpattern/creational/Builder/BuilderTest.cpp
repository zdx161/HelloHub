#include "Director.h"
#include "CLConcreteBuilder.h"
#include "CPPConcreteBuilder.h"

using namespace Builder;

int main()
{
    AbstractBuilder * abcl = new CLConcreteBuilder();
    SoftWareEngineer * engineer = new SoftWareEngineer();

    engineer->Programme(abcl);

    ProgramFile * file = abcl->GetProgramFile();
    file->ShowFile();

    delete abcl;
    delete engineer;

    return 0;
}
