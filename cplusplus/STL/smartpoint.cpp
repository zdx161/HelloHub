#include <iostream>

using namespace std;

template<class T>
class raii_ptr {
public:
    raii_ptr(T * t);
    raii_ptr(const raii_ptr & ref);
    raii_ptr & operator=(const raii_ptr & ref);
    T * get() const;
    void set(T * t);
    T * operator->() const; //overload operator -> for reference class T's operator
    ~raii_ptr();

private:
    T * ptr;
    //raii_ptr & operator=(const raii_ptr &);
    //raii_ptr(const raii_ptr &);
};

template<class T>
void raii_ptr<T>::set(T * t)
{
    cout << __FUNCTION__ << ": t = " << t << endl;
    ptr = t;
}

template<class T>
raii_ptr<T> & raii_ptr<T>::operator=(const raii_ptr & ref)
{
    this->ptr = ref.get();
    (const_cast<raii_ptr &>(ref)).set(NULL);
    //const_cast<raii_ptr &>(ref) = 0; //interator infinite
    return *this;
}

template<class T>
raii_ptr<T>::raii_ptr(const raii_ptr & ref)
{
    this->ptr = ref.get();
    (const_cast<raii_ptr &>(ref)).set(NULL);
    //const_cast<raii_ptr &>(ref) = 0;
}

template<class T>
raii_ptr<T>::raii_ptr(T * t)
    :ptr(t) {
    cout << "constructor initializate resource." << endl;
}

template<class T>
raii_ptr<T>::~raii_ptr()
{
    if (ptr != NULL)
        delete ptr;
}

template<class T>
T * raii_ptr<T>::get() const
{
    return ptr;
}

template<class T>
T * raii_ptr<T>::operator->() const
{
    return ptr; 
}


class testraii {
public:
    testraii();
    void print();
    ~testraii();
     int testnum;
};

testraii::testraii()
    :testnum(0)
{
    testnum += 1;
    cout << __FUNCTION__ << endl;
}

testraii::~testraii()
{
    cout << __FUNCTION__ << endl;
}

void testraii::print()
{
    cout << "just test " << endl;
}

int main()
{
    //raii_ptr<testraii> ptr(new testraii);
    //raii_ptr<testraii> ptr2(ptr); //error: deconstruct two times for default copy constructor function
    raii_ptr<testraii> ptr2(NULL); //OK
    (ptr2.operator->())->print(); //???
    cout << (ptr2.operator->())->testnum << endl; //difference of members and member function
    //ptr2 = ptr;
    //(ptr.get())->print(); //???
    //ptr->print(); //need to overload -> operator, (ptr.operator->())->print()

    int y;
    int &x = y;
    x = 10;
    cout << "x = " << x << "; y = " << y << endl;

    return 0;
}
