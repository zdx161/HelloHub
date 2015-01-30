/** *****************************************************************************
 ** kMP(Knuth-Morris-Pratt) algorithm: searches for occurrences
 ** of a "word" W within a main "text string" S by employing the
 ** observation that when a mismatch occurs, the word itself
 ** embodies sufficient information to determine where the next
 ** match could begin, thus bypassing re-examination of
 ** previously matched characters.
 **
 ** wikipedia link: http://en.wikipedia.org/wiki/Knuth-Morris-Pratt_algorithm
 ** ****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * kmptable(const char *str)
{
    char *table = NULL;
    const char *start;
    const char *index;
    const char *sync = NULL;
    table = (char *)calloc(1, strlen(str));

    if (table == NULL)
        return table;

    start = str;
    index = str;
    for (start = index = str; *index != '\0'; index++) {
        if (start == index && *start == *index)
            table[0] = -1;
        else if (sync == NULL && *start == *index) {
            sync = index;
        } else if (sync != NULL) {
            table[index - start] = index - sync;
            if((*(start + (index - sync))) != *index)
                sync = NULL;
        }
    }

    return table;
}

int kmpsearch(const char *src, const char *dst, const char *table)
{
    int index = -1;
    int i;
    const char *sptr = src;
    const char *dptr = dst;
    //const char *tptr = table;

    for ( ; *sptr != '\0'; ){
        i = 0;
        for ( ; *(dptr + i) != '\0'; i++) {
            if(*sptr++ != *(dptr + i))
                break;
        }

        if (*(dptr + i) == '\0') {
            index = sptr - i - src;
            break;
        }

        sptr = (--sptr) - table[i]; //warning: failed easily
    }

    return index;
}

int main()
{
    char *str = "ABCDABD";//"PARTICIPATE IN PARACHUTE"; "ABCDABD";
    char *src = "ABC ABCDAB ABCDABCDABDE";
    char *table = NULL;
    int i, index;

    table = kmptable(str);

    if (table == NULL) {
        printf("create table failed.\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < strlen(str); i++) {
        printf("%3c ", *(str + i));
    }
    printf("\n");

    for (i = 0; i < strlen(str); i++) {
        printf("%3d ", *(table + i));
    }
    printf("\n");

    index = kmpsearch(src, str, table);

    if(index != -1)
        printf("index = %d, string: %s\n", index, &src[index]); //%7s: do nothing
    else
        printf("%s does not contain %s", src, str);

    free(table);

    return 0;
}
