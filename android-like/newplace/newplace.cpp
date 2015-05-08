#include <iostream>
#include <stdlib.h>

using namespace std;

class cblk_t {
public:
    cblk_t();
    ~cblk_t(){ cout << "call destructed function" << endl;}
    char * startptr;
    char * endptr;
    char * readptr;
    char * writeptr;
    int size;
};

cblk_t::cblk_t()
    :startptr(0),
    endptr(0),
    readptr(0),
    writeptr(0),
    size(0)
{
    cout << "call constructed function" << endl;
}

int main()
{
    cblk_t * mCblk;
    void * memptr = NULL;
    memptr = calloc(1, 1024);
    
    mCblk = static_cast<cblk_t *>(memptr);

    new(mCblk) cblk_t();

    
    cout << "new object === oK" << endl;

    //delete mCblk; //it's possible to leak memory;

    mCblk->~cblk_t();
    
    if (memptr != NULL){
        free(memptr);
        memptr = NULL;
    }



    return 0;
}
