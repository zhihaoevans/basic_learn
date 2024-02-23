#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

struct entry
{
    int data;
    SLIST_ENTRY(entry) entries; /* Singly linked list */
};

SLIST_HEAD(slisthead, entry);

int main(void)
{
    struct entry *n1, *n2, *n3, *np;
    struct slisthead head; /* Singly linked list
                              head */

    SLIST_INIT(&head); /* Initialize the queue */

    n1 = malloc(sizeof(struct entry)); /* Insert at the head */
    SLIST_INSERT_HEAD(&head, n1, entries);

    n2 = malloc(sizeof(struct entry)); /* Insert after */
    SLIST_INSERT_AFTER(n1, n2, entries);

    SLIST_REMOVE(&head, n2, entry, entries); /* Deletion */
    free(n2);

    n3 = SLIST_FIRST(&head);
    SLIST_REMOVE_HEAD(&head, entries); /* Deletion from the head */
    free(n3);

    unsigned int i;
    for (i = 0; i < 5; i++)
    {
        n1 = malloc(sizeof(struct entry));
        SLIST_INSERT_HEAD(&head, n1, entries);
        n1->data = i;
    }

    /* Forward traversal */
    SLIST_FOREACH(np, &head, entries)
        printf("%i ", np->data);
    
    printf("\n");

    while (!SLIST_EMPTY(&head))
    { /* List deletion */
        n1 = SLIST_FIRST(&head);
        SLIST_REMOVE_HEAD(&head, entries);
        free(n1);
        SLIST_FOREACH(np, &head, entries){
            printf("%i ", np->data);
        }
        printf("\n");
    }
    SLIST_INIT(&head);

    exit(EXIT_SUCCESS);
}