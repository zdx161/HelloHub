/** ************************************************************
 ** heap
 **
 **
 **
 ** book: Programming Pearls (second Edition)
 ** ***********************************************************/
#include <iostream>

using namespace std;

template <class T>
class priqueue {
public:
    priqueue(int m);
    ~priqueue() {
        delete[] x;
    }
    void insert(T t);
    T extractmin();
    void swap(int i, int j) {
        T t = x[i]; x[i] = x[j]; x[j] = t;
    }

private:
    int n, maxsize;
    T *x;
};

template <class T>
priqueue<T>::priqueue(int m)
{
    maxsize = m;
    x = new T[maxsize];
    n = 0;
}

template <class T>
void priqueue<T>::insert(T t)
{
    int i, p;
    x[++n] = t;
    for (i = n; i > 0 && x[p = i/2] > x[i]; i = p)
        swap(p, i);
}

template <class T>
T priqueue<T>::extractmin()
{
    int i, c;
    T t = x[1];
    x[1] = x[n--];

    for (i = 1; (c = 2 * i) <= n; i = c) {
        if (c + 1 <= n && x[c + 1] < x[c])
            c++;
        if (x[i] <= x[c])
            break;
        swap(c, i);
    }
    return t;
}

template <class T>
void pqsort(T v[], int n)
{
    priqueue<T> pq(n);
    int i;
    for (i = 0; i < n; i++)
        pq.insert(v[i]);
    for (i = 0; i < n; i++)
        v[i] = pq.extractmin();
}
