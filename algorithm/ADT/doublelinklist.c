#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node * fwd;
    struct node * bwd;
    int data;
} DList;

enum {
    TRUE,
    FALSE
};

int insertnode(DList *head, int data)
{
    DList * rootp;
    DList * nextp;
    DList * newp;

    for (rootp = head; (nextp = rootp->fwd) != NULL; rootp = nextp) {
        if (data < nextp->data) {
            break;
        }
    }

    newp = (DList *) calloc(1, sizeof(DList));

    if (newp == NULL) {
        printf("allocate new node failed.\n");
        return FALSE;
    }

    newp->data = data;

    if (nextp == NULL) {
        rootp->fwd = newp;
        newp->bwd = rootp;
    } else {
        newp->fwd = nextp;
        newp->bwd = rootp;
        rootp->fwd = newp;
        nextp->bwd = newp;
    }

    return TRUE;
}

int createlist(DList **head)
{
    if (*head == NULL) {
        *head = (DList *)calloc(1, sizeof(DList));
    }

    return *head == NULL ? FALSE : TRUE;
}

void printheadlist(DList * head)
{
    head = head->fwd;

    while (head != NULL) {
        printf("%d ", head->data);
        head = head->fwd;
    }

    printf("\n");
}

void printendlist(DList * head)
{
    DList * end;
    end = head;
    while ((end = end->fwd)->fwd != NULL) ;

    while (end != head) {
        printf("%d ", end->data);
        end = end->bwd;
    }

    printf("\n");
}

void releaselist(DList *head)
{
    DList * ptr;

    while (head != NULL) {
        ptr = head;
        head = head->fwd;
        free(ptr);
    }
}

int main()
{
    DList *head = NULL;
    int data[10] = {1, 4, 2, 7, 9, 3, 5, 0, 8, 6};
    int i;

    createlist(&head);

    for (i = 0; i < 10; i++) {
        insertnode(head, data[i]);
    }

    printheadlist(head); //show data after sorting.

    printendlist(head);

    releaselist(head); //free node memory.

    return 0;
}
