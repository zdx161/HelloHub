#include "singleton.h"
#include <iostream>
#include <unistd.h>

using namespace Test;

int main()
{
    pid_t pt;
    // fork is possible to share data, but two seperate process can not do this
    pt = fork();
    if (pt == 0){
        SingleTest * proc_thd(SingleTest::self());
        proc_thd->print("child thread:");
        std::cout << proc_thd << std::endl;
    } else if(pt < 0){
        std::cout << "failed." << std::endl;
    } else{
        SingleTest * proc_par(SingleTest::self());
        proc_par->print("parent thread:");
        std::cout << proc_par << std::endl;
    }
    return 0;
}
