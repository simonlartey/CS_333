/**
 * @file   linkedlist.h
 * @brief  Header for a generic singly linked list in C.
 * @author Simon Lartey
 * @date   11/13/2025
 */

#ifndef GENERIC_LINKEDLIST_H
#define GENERIC_LINKEDLIST_H

#include <stddef.h>  // for size_t

/** Node structure */
typedef struct Node {
    void *data;
    struct Node *next;
} Node;

/** Linked list structure */
typedef struct LinkedList {
    Node *head;
} LinkedList;



/** Create a new empty linked list. */
LinkedList *ll_create(void);

/** Add a new node at the front of the list. */
void ll_push(LinkedList *list, void *data);

/** Add a new node at the end of the list. */
void ll_append(LinkedList *list, void *data);

/** Remove and return data from the first node. */
void *ll_pop(LinkedList *list);

/** Remove first node matching target using a compare function. */
void *ll_remove(LinkedList *list, void *target,
                int (*compfunc)(void *, void *));

/** Find data matching target using a compare function. */
void *ll_find(LinkedList *list, void *target,
              int (*compfunc)(void *, void *));

/** Return number of nodes in the list. */
int ll_size(LinkedList *list);

/** Clear all nodes and free their data using given free function. */
void ll_clear(LinkedList *list, void (*freefunc)(void *));

/** Apply a function to each node’s data. */
void ll_map(LinkedList *list, void (*mapfunc)(void *));

#endif /* GENERIC_LINKEDLIST_H */
