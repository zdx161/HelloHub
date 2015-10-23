#include <iostream>
#include <vector>
#include <string>

#define USEPOINT
#undef USEPOINT

using namespace std;

class Sentry;

class Observer{
public:
    Observer(string name, Sentry *sentry);
    void update();

private:
    string name;
    Sentry *sentry;
};


Observer::Observer(string name, Sentry *sentry)
    :name(name),
    sentry(sentry){
}

class Sentry{
public:
    string getinfo();
    void notify(string info);
    void addobsever(Observer *observer);
    void removeobserver(
#ifdef USEPOINT
            Observer *observer
#else            
            int index
#endif
            );

private:
    string intelligence;
    vector<Observer*> vobservers; 
};

void Observer::update()
{
    cout << name <<" get info: " << sentry->getinfo() << endl;
    cout << "let's go to battle" << endl;
}

string Sentry::getinfo()
{
    return intelligence;  
}

void Sentry::notify(string info)
    //:intelligence(info) (X) ===> because only class constructor does it like this.
{
    intelligence = info;
    vector<Observer*>::iterator i;
    for (i = vobservers.begin(); i != vobservers.end(); i++) {
        (*i)->update();
    }
}


void Sentry::addobsever(Observer * observer)
{
    vobservers.push_back(observer);
}

void Sentry::removeobserver(
#ifdef USEPOINT 
        Observer *observer
#else        
        int index
#endif
)
{
#ifdef USEPOINT 
    vector<Observer*>::iterator i; 
    for (i = vobservers.begin(); i < vobservers.end(); i++) {
        if ((*i) == observer) {
            vobservers.erase(i);
        }
    }
#else
    vobservers.erase(vobservers.begin() + index);
        
#endif
}

int main()
{
    Sentry *sen = new Sentry();

    Observer *ob1 = new Observer("ob1", sen);
    Observer *ob2 = new Observer("ob2", sen);

    sen->addobsever(ob1);
    sen->addobsever(ob2);

    sen->notify("dengerous");

    sen->removeobserver(0);
    sen->notify("enemy");

    delete sen;
    delete ob1;
    delete ob2;

    return 0;
}
