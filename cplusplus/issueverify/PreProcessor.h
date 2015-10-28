#ifndef PRE_PROCESSOR_H
#define PRE_PROCESSOR_H

#include <iostream>

//using namespace std;

//namespace TestPreProcessor {//  ===>(X)

namespace PreProcessor{
class TestPreProcessor {
public:
    TestPreProcessor()
        :test(0)
    {
        using namespace std;
        cout << "construct TestPreProcessor" << endl;
    }

    ~TestPreProcessor()
    {
        using namespace std;
        cout << "deconstruct TestPreProcessor" << endl;
    }

    int * getvariableaddr() {
        return &test;
    }
    
    void print() {
        std::cout << "hello" << std::endl;
    }

private:
    int test;
};

}
#endif
