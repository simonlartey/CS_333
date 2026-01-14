/**
 * @file   linkedlist.c
 * @brief  Implementation of a generic singly linked list.
 * @author Simon Lartey
 * @date   11/13/2025
 */

#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

/* Create an empty list */
LinkedList *ll_create(void) {
    LinkedList *list = malloc(sizeof(LinkedList));
    if (!list) {
        fprintf(stderr, "Error: Failed to allocate memory for LinkedList.\n");
        return NULL;
    }
    list->head = NULL;
    return list;
}

/* Add node to front */
void ll_push(LinkedList *list, void *data) {
    if (!list) return;

    Node *node = malloc(sizeof(Node));
    if (!node) {
        fprintf(stderr, "Error: Failed to allocate memory for Node.\n");
        return;
    }

    node->data = data;
    node->next = list->head;
    list->head = node;
}

/* Remove node from front */
void *ll_pop(LinkedList *list) {
    if (!list || !list->head) return NULL;

    Node *temp = list->head;
    void *data = temp->data;
    list->head = temp->next;
    free(temp);
    return data;
}

/* Add node to end */
void ll_append(LinkedList *list, void *data) {
    if (!list) return;

    Node *node = malloc(sizeof(Node));
    if (!node) {
        fprintf(stderr, "Error: Failed to allocate memory for Node.\n");
        return;
    }

    node->data = data;
    node->next = NULL;

    if (!list->head) {
        list->head = node;
        return;
    }

    Node *current = list->head;
    while (current->next)
        current = current->next;

    current->next = node;
}

/* Remove first node matching target */
void *ll_remove(LinkedList *list, void *target,
                int (*compfunc)(void *, void *)) {
    if (!list || !list->head) return NULL;

    Node *current = list->head;
    Node *prev = NULL;

    while (current) {
        if (compfunc(current->data, target) == 1) {  // match
            void *data = current->data;

            if (prev)
                prev->next = current->next;
            else
                list->head = current->next;

            free(current);
            return data;
        }
        prev = current;
        current = current->next;
    }
    return NULL;
}

/* Find first node matching target */
void *ll_find(LinkedList *list, void *target,
              int (*compfunc)(void *, void *)) {
    if (!list) return NULL;

    Node *current = list->head;
    while (current) {
        if (compfunc(current->data, target) == 1)
            return current->data;
        current = current->next;
    }
    return NULL;
}

/* Count nodes */
int ll_size(LinkedList *list) {
    int count = 0;
    for (Node *cur = list ? list->head : NULL; cur; cur = cur->next)
        count++;
    return count;
}

/* Clear all nodes */
void ll_clear(LinkedList *list, void (*freefunc)(void *)) {
    if (!list) return;

    Node *current = list->head;
    while (current) {
        Node *next = current->next;
        if (freefunc)
            freefunc(current->data);
        free(current);
        current = next;
    }
    list->head = NULL;
}

/* Apply function to each node’s data */
void ll_map(LinkedList *list, void (*mapfunc)(void *)) {
    if (!list || !mapfunc) return;

    for (Node *cur = list->head; cur; cur = cur->next)
        mapfunc(cur->data);
}
