#include <stdio.h>
#include <stdio.h>

typedef struct node_{
    struct node_ *fwd;
    struct node_ *bwd;
    int data;
} DList;

enum {
    TRUE,
    FALSE
};

int insertnode(DList *head, int data)
{
    DList *rootp;
    DList *nextp;
    DList *newp;

    for (rootp = head; (nextp = rootp->fwd) != NULL; rootp = nextp) {
        if (data < rootp->data) {
            break;
        }
    }

    newp = (DList *)calloc(1, sizeof(DList));

    if (newp == NULL) {
        printf("allocate new node failed.\n");
        return FALSE;
    }

    newp->data = data;

    if (nextp == NULL) {
        if (rootp == head) {
            rootp->fwd = newp;
            //rootp->bwd = NULL;//newp;
            newp->bwd = rootp;
            //newp->fwd = NULL;//rootp;
        } else {
            //newp->fwd = NULL;//head;
            //head->bwd = newp;
            newp->bwd = rootp;
            rootp->fwd = newp;
        }
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

void printlist(DList * head)
{
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->fwd;
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

    printlist(head); //show data after sorting.

    releaselist(head); //free node memory.
    return 0;
}
