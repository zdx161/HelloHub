#ifndef SINGLETON_H
#define SINGLETON_H

namespace Test{
class SingleTest{
public:
    static SingleTest * self();
    SingleTest();
    ~SingleTest();
    
    void print(char * s);
};
}
#endif
