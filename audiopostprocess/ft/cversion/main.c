#include <stdio.h>
#include "sampling.h"
#include "fourier.h"

int main()
{
    Matrix * pcm = NULL;
    Matrix * sig = NULL;

    pcm = allocate_matrix(16000, 1);
    pcmsampling("testfft.pcm", pcm);
    //log_matrix(pcm, False);
    sig = dft(pcm);
    fourieramplitude(sig, sig);
    //signalamplitude(sig, sig);
    log_matrix(sig, False);

    free_matrix(pcm);
    free_matrix(sig);

    return 0;
}
