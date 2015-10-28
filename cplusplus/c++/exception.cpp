#include <iostream>
#include <exception>

using namespace std;

class MyException : public exception {
public:
virtual const char * what() const throw()
{
    return "hello exception";
}

};


/*****************************************************************************
    exception                       description
-------------------------------------------------------------------------------
    bad_alloc         |  thrown by new on allocation failure
    bad_cast          |  thrown by dynamic_cast when it fails in a dynamic cast
    bad_exception     |  thrown by certain dynamic exception specifiers
    bad_typeid        |  thrown by typeid
    bad_function_call |  thrown by empty function objects
    bad_weak_ptr      |  thrown by shared_ptr when passed a bad weak_ptr
*****************************************************************************/


int main()
{
#if 0
    try {
        throw 250;
    }
    catch(int e){
        cout << "catch error: " << e << endl;
    }
#else
    MyException myerror;
    try {
        throw myerror;
    }
    catch(MyException &e)
    {
        cout << e.what()  << endl;
    }

#endif

    return 0;
}
