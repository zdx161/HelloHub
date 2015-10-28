#ifndef PROGRAM_FILE_H
#define PROGRAM_FILE_H

#include <iostream>
#include <vector>
#include <string>

namespace Builder {

class ProgramFile {

public:

    ProgramFile() {
        #ifdef _DEBUG
        std::cout << __FUNCTION__ << std::endl;
        #endif
    }

    ~ProgramFile() {
        #ifdef _DEBUG
        std::cout << __FUNCTION__ << std::endl;
        #endif
    }

    void AddFile(std::string file);
    void ShowFile();

private:
    std::vector<std::string> prgf;

};

}
#endif
