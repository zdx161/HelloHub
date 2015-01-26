#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct chart{
    char c;
    int times;
};

void * statistic(char * str){
    if(str == NULL)
        return str;
    char *ptr;
    void *statptr = calloc(26, sizeof(struct chart));
    char c;
    int i;
    struct chart *tmp = (struct chart *)statptr;
    for(c = 'a',i = 0; c <= 'z'; c++){
        tmp[i++].c = c;
    }

    for(ptr = str; *ptr != '\0'; ptr++){
        for(i = 0; i < 26; i++){
            if(*ptr ==  tmp[i].c){
                tmp[i].times++;
                break;
            }
        }
    }
    
    return statptr;
}

typedef struct node{
    char c;
    char value;
    struct node *p;
    struct node *nL;
    struct node *lR;
    struct node *n;
} Node;


void createnode(Node **node)
{
    if(*node == NULL){
        *node = calloc(1, sizeof(Node));
    }
}

int main(int argc, char ** argv)
{
#if 0
    void *ptr;
    int i;
    ptr = statistic(argv[1]);
    if(ptr == NULL)
    {
        printf("statistis failed.\n");
        exit(EXIT_FAILURE);
    }
    struct chart *tmp = (struct chart *)ptr;
    printf("char statistics: \n");
    for(i = 0; i < 26; i++){
        printf("%c: %d\n",tmp[i].c, tmp[i].times);
    }

    free(ptr);
#endif
    char times[7] = {1,1,2,2,2,3,4};
    Node * p[7] = {NULL};
    int i;
    for(i = 0; i < 7; i++){
        createnode(&p[i]);
        p[i]->value = times[i];
    }
    for(i = 0; i < 7; i++){
        printf("value:%d\n", p[i]->value);
        free(p[i]);
    }
    
    return 0;
}
