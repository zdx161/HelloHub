#include <stdio.h>
#include <stdlib.h>

typedef struct List_ {
    struct List_ *link;
    int data;
} List;

enum { //it's easy to define many status value.
  TRUE,
  FALSE
};

int insertnode(List ** head, int data)
{
    List *current;
    //current = *head;

    while ((current = *head) != NULL && data > current->data) {
        head = &current->link; //best way, the relation between * and **;
        //current = *head;
    }

    List *node = (List *)calloc(1, sizeof(List));
    if (node == NULL) {
        printf("error: allocate memory failed.\n");
        return FALSE;
    }

    node->data = data;
    node->link = current;
    *head = node;
    return TRUE;
}

int deletenode(List *head, int data)
{

}

int querynode(List *head, int data)
{

}

void printlist(List * head)
{
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->link;
    }

    printf("\n");
}

void releaselist(List *head)
{
    List * ptr;

    while (head != NULL) {
        ptr = head;
        head = head->link;
        free(ptr);
    }
}

int main()
{
    List *head = NULL;
    int data[10] = {1, 4, 2, 7, 9, 3, 5, 0, 8, 6};
    int i;

    for (i = 0; i < 10; i++) {
        insertnode(&head, data[i]);
    }

    printlist(head); //show data after sorting.

    releaselist(head); //free node memory.

    return 0;
}
