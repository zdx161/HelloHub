#include <iostream>
#include <typeinfo>

#define GETNAME(x) #x

using namespace std;

int & setval(int & ref)
{
    return ref;
}

const int & csetval(int & ref)
{
    return ref;
}

#if 0
//int globalval = 0;
mutable int globalval = 0; //error: non-member function ‘int testfun(int)’ cannot have cv-qualifier

int testfun(int x) const{
   //globalval = x; (X) ===> error: non-member function ‘int testfun(int)’ cannot have cv-qualifier
}
#endif

class ConstVal{
public:
    void setval(int y) const{
        x = y; //1. error: assignment of member ‘ConstVal::x’ in read-only object
    }
    
    int getval() const{
        return x;
    }
private:
    //int x; 1.
    mutable int x;
};

//const + type + variable
//const + type + * variable
//type + const + * variable 
//type + * + const variable
//const + type + * + const variable(fun() const) 
//type + const + * + const variable(fun() const)

int main()
{
    int x;
    int *y;
    int & ref = x; //int & xr; ===> (X) must be initialized when declaring

    cout << typeid(x).name() << endl;
    cout << typeid(ref).name() << endl;
    cout << typeid(y).name() << endl;
    
    //test of return reference
    cout << "the value of x is " << x << ", before calling setvalue." << endl;
    setval(x) = 5;
    cout << GETNAME(setval) << " = " << x << endl;
    cout << "the value of x is " << x << ", after setvalue called." << endl;
    
    //csetval(x) = 10; (X) ===> error: assignment of read-only location ‘csetval((* & x))’
    const_cast<int &>(csetval(x)) = 10;
    cout << "the value of x is " << x << ", after const setvalue called." << endl;
    const_cast<int &>(const_cast<int&>(csetval(x))) = 20; //(OK)
    
    //static_cast<const int &>(setval(x)) = 30; (X) ===> error: assignment of read-only location ‘*(const int*)setval((* & x))’

    ConstVal cv;
    cv.setval(100);
    cout << cv.getval() << endl;
    
    return 0;
}
