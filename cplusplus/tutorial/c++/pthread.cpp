#include <iostream>
#include <pthread.h>

using namespace std;

#define NUM_THREADS 5

void * printhello(void *arg) //must have arguments name
{
    cout << "Hello World!" << endl;
    pthread_exit(NULL);
}

int main()
{
    pthread_t pid;
    int i, rc;
 
    for (i = 0; i < NUM_THREADS; i++)
    pthread_create(&pid, NULL, &printhello, NULL);


    pthread_exit(NULL);    
}
