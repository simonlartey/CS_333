/*
 * Author: Simon Lartey
 * Date: 10/28/2025
 * Project: CS333 Project 04 - Extension
 * Description: 
 *   A memory-safe version of clltest.c that eliminates memory leaks by 
 *   freeing all dynamically allocated memory and linked list structures. 
 *   Demonstrates correct memory management in C using free() and ll_clear().
 *
 * Compile: gcc clltest_memory_safe.c ../C/linkedlist.c -I../C -O2 -o clltest_memory_safe
 * Run:     ./clltest_memory_safe
 */

#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

// function that prints an integer
void printInt(void *i) {
    int *a = (int *)i;
    printf("value: %d\n", *a);
}

// function that squares an integer
void squareInt(void *i) {
    int *a = (int *)i;
    *a = *a * *a;
}

// function that compares two integers and returns 1 if they are equal
int compInt(void *i, void *j) {
    int *a = (int *)i;
    int *b = (int *)j;
    return (*a == *b);
}

void printString(void *s) {
    printf("%s\n", (char *)s);
}

// test function for the various linked list functions
int main(int argc, char *argv[]) {
    LinkedList *l;
    int *a;
    int *target;
    int i;

    // create a list
    l = ll_create();

    // push data on the list
    for (i = 0; i < 20; i += 2) {
        a = malloc(sizeof(int));
        if (!a) {
            fprintf(stderr, "Memory allocation failed.\n");
            ll_clear(l, free);
            free(l);
            return 1;
        }
        *a = i;
        ll_push(l, a);
    }

    printf("After initialization\n");
    ll_map(l, printInt);

    ll_map(l, squareInt);

    printf("\nAfter squaring\n");
    ll_map(l, printInt);

    target = malloc(sizeof(int));
    if (!target) {
        fprintf(stderr, "Memory allocation failed.\n");
        ll_clear(l, free);
        free(l);
        return 1;
    }

    *target = 16;
    a = ll_remove(l, target, compInt);
    if (a != NULL) {
        printf("\nremoved: %d\n", *a);
        free(a);
    } else {
        printf("\nNo instance of %d\n", *target);
    }

    *target = 11;
    a = ll_find(l, target, compInt);
    if (a != NULL)
        printf("\nFound: %d\n", *a);
    else
        printf("\nNo instance of %d\n", *target);

    a = ll_remove(l, target, compInt);
    if (a != NULL) {
        printf("\nremoved: %d\n", *a);
        free(a);
    } else {
        printf("\nNo instance of %d\n", *target);
    }

    printf("\nAfter removals\n");
    ll_map(l, printInt);

    ll_append(l, target);
    printf("\nAfter append\n");
    ll_map(l, printInt);

    ll_clear(l, free);
    printf("\nAfter clear\n");
    ll_map(l, printInt);

    for (i = 0; i < 5; i++) {
        a = malloc(sizeof(int));
        *a = i;
        ll_append(l, a);
    }

    printf("\nAfter appending\n");
    ll_map(l, printInt);

    a = ll_pop(l);
    printf("\npopped: %d\n", *a);
    free(a);

    a = ll_pop(l);
    printf("popped: %d\n", *a);
    free(a);

    printf("\nAfter popping\n");
    ll_map(l, printInt);

    printf("\nList size: %d\n", ll_size(l));  

    ll_clear(l, free);
    free(l);

    /* ==============================
       SECOND DATA TYPE TEST: STRINGS
    ============================== */

    printf("\n--- Testing with strings ---\n");

    LinkedList *strList = ll_create();

    ll_append(strList, "Nairobi");
    ll_append(strList, "Tokyo");
    ll_append(strList, "Oslo");
    ll_append(strList, "Lisbon");
    ll_append(strList, "Cairo");

    printf("\nInitial string list:\n");
    ll_map(strList, printString);

    ll_push(strList, "New York");
    printf("\nAfter push:\n");
    ll_map(strList, printString);

    char *removed = ll_pop(strList);
    printf("\nPopped string: %s\n", removed);

    printf("\nAfter pop:\n");
    ll_map(strList, printString);

    ll_append(strList, "Sydney");
    printf("\nAfter append:\n");
    ll_map(strList, printString);

    ll_clear(strList, NULL);
    free(strList);

    printf("\nAll memory freed successfully.\n");
    return 0;
}
