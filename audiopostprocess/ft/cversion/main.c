#include <stdio.h>
#include "sampling.h"
#include "fourier.h"

int main()
{
    Matrix * pcm = NULL;
    Matrix * ipcm = NULL;
    Matrix * sig = NULL;

    pcm = allocate_matrix(256, 1);
    signalsampling(signalfunc, 256, pcm);
    //log_matrix(pcm, False);
    print_matrix(pcm);

    sig = dft(pcm);
    //fourieramplitude(sig, sig);
    //signalamplitude(sig, sig);
    //log_matrix(sig, False);
    ipcm = idft(sig);
    sleep(1);
    print_matrix(ipcm);
    //log_matrix(ipcm, False);

    free_matrix(pcm);
    free_matrix(ipcm);
    free_matrix(sig);

    return 0;
}
