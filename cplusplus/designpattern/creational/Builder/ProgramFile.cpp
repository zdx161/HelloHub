#include <iostream>
#include "ProgramFile.h"

using namespace Builder;

void ProgramFile::AddFile(std::string file)
{
    using namespace std;
    prgf.push_back(file);
}

void ProgramFile::ShowFile()
{
    using namespace std;
    vector<string>::iterator i;

    for (i = prgf.begin(); i != prgf.end(); i++) {
        cout << *i << endl;
    }
}
