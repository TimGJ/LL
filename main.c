/*
 * My final attempt at cudgeling my brain in to remembering C... a linked list!
 *
 * Takes a list of integers from the command line and returns them in order with a count
 *
 * Tim Greening-Jackson 25th February 2018
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    long int value;
    int count;
    struct node *next;
} node;

node *create(long int value) {
    /*
     * Creates and initialises a node structure. Effectively a constructor.
     */

    node *nptr = malloc(sizeof(node));
    nptr->value = value;
    nptr->count = 1;
    nptr->next  = NULL;
    return nptr;
}

node *insert(node *head, long int value) {
    /*
     * Inserts value in to linked list
     */

    node *current = head;

    if (head == NULL) {                                    /* Is this a brand new (empty) list?                    */
        head = create(value);
        return head;
    }

    if (head->value > value) {                              /* Insert at the very start of the list otherwise...   */
        node *new = create(value);
        new->next = head;
        return new;
    }

    while (current->next && current->next->value <= value)  /* Traverse the list to find the correct point...     */
        current = current->next;

    if (current->value == value) {                          /* ... and increment the count if there's a match...  */
        current->count++;
    }
    else {
        node *new = create(value);                          /* ... or insert a new entry in to the list           */
        new->next = current->next;
        current->next = new;
    }
    return head;
}

void print(node *nptr){
    /*
     * Print the list
     */
    while (nptr) {
        printf("%ld (%d) %p->%p\n", nptr->value, nptr->count, nptr, nptr->next);
        nptr = nptr->next;
    }
}
int main(int argc, char **argv) {
    node *head = NULL;
    char *endptr;
    while (--argc) {
        long int value = strtol(*++argv, &endptr, 0);
        if (endptr == *argv) {
            printf("Could not convert %s to long int\n", *argv);
            continue;
        }
        printf("Inserting %ld in to list\n", value);
        head = insert(head, value);
        print(head);
    }
    return 0;
}