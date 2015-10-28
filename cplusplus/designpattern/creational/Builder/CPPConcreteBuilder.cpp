#include <iostream>
#include <exception>
#include "CPPConcreteBuilder.h"

using namespace Builder;

CPPConcreteBuilder::CPPConcreteBuilder()
    :gpf(NULL)
{
    try {
        gpf = new ProgramFile();
    }
    catch (std::exception &e) {
        std::cout << "error: " << e.what() << std::endl;
    }
}

CPPConcreteBuilder::~CPPConcreteBuilder()
{
    if (gpf) {
        delete gpf;
        gpf = NULL;
    }
}

void CPPConcreteBuilder::CreateHeaderFile()
{
    gpf->AddFile("CPPHeader.h");
}

void CPPConcreteBuilder::CreateProgramFile()
{
    gpf->AddFile("CPPprogram.cpp");
}

void CPPConcreteBuilder::CreateMakeFile()
{
    gpf->AddFile("Makefile");
}

ProgramFile * CPPConcreteBuilder::GetProgramFile()
{
    return gpf;
}
