#include <iostream>
#include <vector>

using namespace std;

int main()
{
    //create a vector to store int
    vector<int> vec;
    int i;

    //show vector size
    cout << "vector container size is: " << vec.size() << endl;

    //push data into vector
    for (i = 0; i < 5; i++) {
        vec.push_back(i);
    }

    cout << "vector size after pushing: " << vec.size() << endl;

    //access the five values from the vector
    for (i = 0; i < 5; i++) {
        cout << "the " << i << "th value is: " << vec[i] << endl;
    }

    //use iterator to access the values
    vector<int>::iterator v = vec.begin();
    while (v != vec.end()) {
        cout << "the value of iterator: " << *v++ << endl;
    }


    //pop the data from vector
    while (!vec.empty()) {
       cout << "current vector size is: " << vec.size() << endl;
       vec.pop_back(); 
    }

    return 0;
}
