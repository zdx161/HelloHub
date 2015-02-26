#include <iostream>
#include <set>
#include <string>

using namespace std;

int main(void)
{
    set <string> S;
    set <string>::iterator j;
    string t;
    while (cin >> t){
        if (!t.compare("q"))
            break;
        S.insert(t);
    }

    for (j = S.begin(); j != S.end(); j++) {
        cout << *j << endl;
    }

    return 0;
}
