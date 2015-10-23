/****************************************************************
 * castint operator:
 * dynamic_cast:
 *  The dynamic cast<>() operator is used to convert a base class pointer or reference to, respectively, a derived
 *  class pointer or reference.
 *  A dynamic cast is performed run-time. A prerequisite for the use of the dynamic cast operator is the existence of at
 *  least one virtual member function in the base class.
 *
 * static_cast:
 *  static_cast can perform conversions between pointers to related classes, not only upcasts (from pointer-to-derived to pointer-to-base),
 *  but also downcasts (from pointer-to-base to pointer-to-derived). No checks are performed during runtime to guarantee that the object
 *  being converted is in fact a full object of the destination type. Therefore, it is up to the programmer to ensure that the conversion is safe.
 *  On the other side, it does not incur the overhead of the type-safety checks of dynamic_cast.
 *
 * const_cast:
 *  This type of casting manipulates the constness of the object pointed by a pointer, either to be set or to be removed.
 *
 * reiterpret_cast:
 *  reinterpret_cast converts any pointer type to any other pointer type, even of unrelated classes.
 *  The operation result is a simple binary copy of the value from one pointer to the other.
 *  All pointer conversions are allowed: neither the content pointed nor the pointer type itself is checked.
 *
 * typeid:
 *  typeid allows to check the type of an expression
 ***************************************************************/
#include <iostream>
#include <cstdlib>

using namespace std;

class Base {
public:
    virtual void print(){ //base class must have virtual function for dynamic_cast
        cout << "print Base" << endl;
    }
};

class Driver : public Base{
public:
    int x, y; //int x, int y (x)
};



int main()
{
    Base *b = new Driver; //Up Cast
    Base *c = new Base;

    Driver *pd = NULL;
    Base *pbase = NULL;
 
    pd = dynamic_cast<Driver*> (b); //must have ()

    // dynamic_cast needs RTTI(runtime type identification), different from static_cast(compile time)
    if (pd == NULL)
        cout << "pb is NULL" << endl;
    else {
        //up cast
        //pbase = pd;
        pbase = dynamic_cast<Base*> (pd);
        if (pbase)
            cout << "up cast is ok!" << endl;
    }

    //Down cast
    pd = dynamic_cast<Driver*> (c);
    if (pd == NULL)
        cout << "pb is NULL for BASE to Driver" << endl;

    delete b;
    delete c;

    //return 0;
    exit(0); //process exit and free resource.
}
