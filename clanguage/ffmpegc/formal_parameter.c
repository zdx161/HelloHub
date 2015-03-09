#include <stdio.h>
#include <inttypes.h>

static inline char * av_ts_make_string(char *buf, int64_t ts)
{
    snprintf(buf, 32, "%"PRId64"", ts);
    return buf;
}

#define av_ts2str(ts) av_ts_make_string((char[32]){0}, ts)


int main()
{
    int64_t ts = 0x7FFFFFFFFFFFFFFF;
    printf("%s\n", av_ts2str(ts));
    return 0;
}



