#include "Director.h"

using namespace Builder;

void SoftWareEngineer::Programme(AbstractBuilder * ab)
{
    ab->CreateHeaderFile();
    ab->CreateProgramFile();
    ab->CreateMakeFile();
}
