#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

//the active point status for runtime
typedef enum {
    NORMAL = 0, RESUME
} STATUS;

//mutex lock for accessing shared data
typedef pthread_mutex_t PMT;

//control block data struct
typedef struct {
    STATUS flag;
    int size;
    PMT mutex;
    int *rptr;
    int *wptr;
    int *end;
    int *ptr;
} RING;

//control thread loop
int exitflag = 1;

//init control block data struct
RING * init(int size)
{
    RING * cblk = NULL;

    //the way to allocate memory is same as new in place for c++
    cblk = (RING *) calloc(1, sizeof(RING) + size * sizeof(int));
    if (!cblk) {
        printf("%s\n", strerror(errno));
        return NULL;
    }

    cblk->size = size;
    cblk->ptr = (int *)(&cblk[1]);
    cblk->end = cblk->ptr + size;
    cblk->rptr = cblk->ptr;
    cblk->wptr = cblk->ptr;
    cblk->flag =  NORMAL;

    pthread_mutex_init(&cblk->mutex, NULL);

    return cblk;
}

//free cblk memory
void destroy(RING * r)
{
    if (r != NULL) {
        pthread_mutex_destroy(&r->mutex);
        free(r);
        r = NULL;
    }
}

//read data from ring buffer
int rbread(RING * r, int asize)
{
    int num = 0, size;
    int i;

    //calculate number of data can be readed in ring buffer.
    pthread_mutex_lock(&r->mutex);
    if (r->flag == NORMAL) {
        if (r->rptr < r->wptr) {
            num = r->wptr - r->rptr;
        }
    } else if (r->flag == RESUME) {
        if (r->rptr < r->end) {
            num += r->end - r->rptr;
        }

        if (r->wptr > r->ptr) {
            num += r->wptr - r->ptr;
            //r->flag = NORMAL;
        }
    }
    pthread_mutex_unlock(&r->mutex);

    //the number need read from ring buffer really.
    size = num > asize ? asize : num;
    num = size;

    //read data operator in ring buffer.
    if ((r->end - r->rptr > 0) && (num > 0)) {
        if (r->end - r->rptr >= num) {
            for (i = 0; i < num; i++) {
                printf("%d ", *r->rptr++);
            }
            printf("\n");

            if (r->rptr == r->end) {
                r->rptr = r->ptr;
                //resume the point of reading data
                pthread_mutex_lock(&r->mutex);
                r->flag = NORMAL;
                pthread_mutex_unlock(&r->mutex);
            }
        } else {
            for (; r->rptr < r->end; num--) {
                printf("%d ", *r->rptr++);
            }

            r->rptr = r->ptr;
            //resume the point of reading data
            pthread_mutex_lock(&r->mutex);
            r->flag = NORMAL;
            pthread_mutex_unlock(&r->mutex);
            num++;

            for (i = 0; i < num; i++) {
                printf("%d ", *r->rptr++);
            }

            printf("\n");
        }
    } else if ((r->end == r->rptr) && (num > 0)) {
        r->rptr = r->ptr;
        //resume the point of reading data
        pthread_mutex_lock(&r->mutex);
        r->flag = NORMAL;
        pthread_mutex_unlock(&r->mutex);

        for (i = 0; i < num; i++) {
            printf("%d ", *r->rptr++);
        }
        printf("\n");
    }

    return size;
}

//write data to ring buffer
int rbwrite(RING * r, int asize)
{
    int num = 0, size;
    int i;
    static int data = 0;

    //calculate number of data can be  wrote to ring buffer.
    pthread_mutex_lock(&r->mutex);

    if (r->flag == NORMAL) {
        if (r->wptr < r->end) {
            num += r->end - r->wptr;
        }

        if (r->rptr > r->ptr) {
            num += r->rptr - r->ptr;
            //r->flag = RESUME;
        }
    } else if (r->flag == RESUME) {
        if (r->rptr > r->wptr) {
            num += r->rptr - r->wptr;
        }
    }

    pthread_mutex_unlock(&r->mutex);

    //the number need write to ring buffer really.
    size = num > asize ? asize : num;
    num = size;

    //write data operator in ring buffer.
    if (num > 0) {
        for (i = 0; i < num && r->wptr < r->end; i++) {
            *r->wptr++ = data++;
        }

        if (r->wptr == r->end) {
            r->wptr = r->ptr;
            //resume the point of writing data
            pthread_mutex_lock(&r->mutex);
            r->flag = RESUME;
            pthread_mutex_unlock(&r->mutex);
        }

        if (i-- < num) {
            for (; i < num && r->wptr < r->end; i++) {
                *r->wptr++ = data++;
            }
        }
    }

    return size;
}

//read data thread loop function
void * readringbuf(void * v) {
    int size;
    RING * r  = NULL;

    size = 64;
    r = (RING *) v;

    while(exitflag) {
        rbread(r, size);
        usleep(1000);
    }
}

//write data thread loop function
void * writeringbuf(void * v) {
    int size;
    RING * r  = NULL;

    size = 64;
    r = (RING *) v;

    while(exitflag) {
        rbwrite(r, size);
        usleep(1000);
    }
}

//the function for test ring buffer.
int main()
{
    pthread_t rpid, wpid;
    int ret;
    RING * r = NULL;

    r = init(1024);
    if (!r)
        return -1;

    ret = pthread_create(&rpid, NULL, readringbuf, r);
    if (ret != 0) {
        destroy(r);
        exit(EXIT_FAILURE);
    }

    ret = pthread_create(&wpid, NULL, writeringbuf, r);
    if (ret != 0) {
        destroy(r);
        exit(EXIT_FAILURE);
    }

    usleep(5000);
    exitflag = 0;

    pthread_join(rpid, NULL);
    pthread_join(wpid, NULL);
    destroy(r);

    return 0;
}
