#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *start;
    int *end;
    int size;
} Stack;

enum {
    TRUE,
    FALSE
};

int createstack(Stack ** head, int size)
{
    if (*head == NULL) {
        *head = (Stack *)calloc(1, sizeof(Stack) + size);
        (*head)->start = (*head)->end = (int *)(&((*head)[1]));
        (*head)->size = size;
    }

    return *head == NULL ? FALSE : TRUE; 
}

void releasestack(Stack * head)
{
    if (head) {
        free(head);
        head = NULL;
    }
}

int pushstack(Stack * head, int data)
{
    if (head->end - head->start >= head->size) {
        printf("error: stack is full, this data will discard\n");
        return FALSE;
    }
    
    *head->end++ = data;
    return TRUE;
}

int popstack(Stack * head, int * data)
{
    if (head->end <= head->start) {
        printf("error: stack is empty, pop data failed.\n");
        return FALSE;
    }

    
    *data = *--head->end; 
    return TRUE;
}

int main()
{
    int data[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Stack * head = NULL;
    if (createstack(&head, 64) == FALSE) {
        printf("create stack failed.\n");
        exit(EXIT_FAILURE);
    }
    
    int i = 0;
    while (pushstack(head, data[i++]) == TRUE && i < 10);
    
    while (popstack(head, &i) == TRUE)
        printf("%d ", i);
    
    printf("\n");
    
    releasestack(head);

    return 0;
}
