#include <iostream>
#include <exception>
#include "CLConcreteBuilder.h"

using namespace Builder;

CLConcreteBuilder::CLConcreteBuilder()
    :gpf(NULL)
{
    try{
        gpf = new ProgramFile();
    }
    catch(std::exception &e) {
        std::cout << "error: " << e.what() << std::endl;
    }

}

CLConcreteBuilder::~CLConcreteBuilder()
{
    if (gpf) {
        delete gpf;
        gpf = NULL;
    }
}

void CLConcreteBuilder::CreateHeaderFile()
{
    gpf->AddFile("CLHeaderfile.h");
}

void CLConcreteBuilder::CreateProgramFile()
{
    gpf->AddFile("CLProgramFile.cpp");
}

void CLConcreteBuilder::CreateMakeFile()
{
    gpf->AddFile("Makefile");
}

ProgramFile * CLConcreteBuilder::GetProgramFile()
{
    return gpf;
}
