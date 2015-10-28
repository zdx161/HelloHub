#include <stdio.h>
#include "PreProcessor.h"

//using namespace std;
//using namespace TestPreProcessor;// (X)

using namespace PreProcessor;

int main()
{
    TestPreProcessor tpp1;
    TestPreProcessor tpp2;

    std::cout << tpp1.getvariableaddr() << std::endl;
    std::cout << tpp2.getvariableaddr() << std::endl;
    printf("addr1: %p\n", &tpp1.getvariableaddr);
    printf("addr2: %p\n", &tpp2.getvariableaddr);

    TestPreProcessor * ptr = NULL;
    ptr->print(); //OK
    std::cout << ptr->getvariableaddr() << std::endl; //OK
    
    
    std::cout << "object size: " << sizeof(tpp1) << std::endl;
    std::cout << "Class size: " << sizeof(TestPreProcessor) << std::endl;

    return 0;
}
