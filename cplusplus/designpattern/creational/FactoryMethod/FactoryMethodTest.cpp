#include <iostream>
#include <memory>
#include <typeinfo>
#include "PhoneFactory.h"
#include "HtcM8Factory.h"
#include "HtcM9Factory.h"

using namespace FactoryMethod;


int main()
{
    std::cout << "test FactoryMethod Design Pattern" << std::endl;
    
    //PhoneFactory *pf = new HtcM8Factory();
    //use auto_ptr
    std::auto_ptr<PhoneFactory> pf(new HtcM8Factory());
    std::cout << typeid(pf).name() << std::endl; //overload -> operator
    HtcM8Phone * hmp = dynamic_cast<HtcM8Phone*>(pf->getProduct());
    if (hmp == NULL) {
        std::cout << "dynamic cast PhoneMethod to HtcM8Phone failed." << std::endl;
    }

    //delete pf;
    delete hmp;
    return 0;
}
