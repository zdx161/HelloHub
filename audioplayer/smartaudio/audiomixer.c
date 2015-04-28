
int32_t mulAddRL(int left, uint32_t inRL, uint32_t vRL, int32_t a)
{
    if (left) {
        return a + (int16_t)(inRL&0xFFFF) * (int16_t)(vRL&0xFFFF);
    } else {
        return a + (int16_t)(inRL>>16) * (int16_t)(vRL>>16);
    }
}

static inline int16_t clamp16(int32_t sample)
{
    if ((sample>>15) ^ (sample>>31))
        sample = 0x7FFF ^ (sample>>31);
    return sample; 
}     

 void ditherAndClamp(int32_t* out, int32_t const *sums, size_t c)
{
    size_t i;
    for (i=0 ; i<c ; i++) {
        int32_t l = *sums++;      
        int32_t r = *sums++;      
        int32_t nl = l >> 12;     
        int32_t nr = r >> 12;     
        l = clamp16(nl);
        r = clamp16(nr);
        *out++ = (r<<16) | (l & 0xFFFF); 
    }
}

#define TEST_MIXER
#ifdef TEST_MIXER
int main(int argc, char ** argv)
{
    FILE * in1, * in2;
    in1 = NULL;
    in2 = NULL;
    
    short din1[32] = {0};
    short din2[32] = {0};
    int dnum1 = 0;
    int dnum2 = 0;
    int num;

    in1 = fopen(argv[1], "rb");
    in2 = fopen(argv[2], "rb");
    
    if(in1 == NULL || in2 == NULL)
        goto error;

    while(1) {
        dnum1 = fread(din1, sizeof(short), 32, in1);
        dnum2 = fread(din2, sizeof(short), 32, in2);

        if(dnum1 != 32 || dnum2 != 32)
            break;
        
        for (num = 0; num < 32; num++) {
            
        }
        

    }

error:
    if(in1 != NULL)
        fclose(in1);
    if(in2 != NULL)
        fclose(in2);

    return 0;
}


#endif
