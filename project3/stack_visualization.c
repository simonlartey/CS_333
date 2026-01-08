/**
 * Test code for Stack 
 * Ying Li
 * 08/01/2016
 *
 * Modified by: Simon Lartey
 * Date:        10/15/2025
 * Description:
 * Demonstrates how stack and heap memory are used by the Stack structure.
 * Prints out addresses of variables and heap allocations before and after
 * calling stk_destroy() to visualize memory behavior.
 */

#include "cstk.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
    Stack *s = stk_create(20);
    int i;

    for (i = 0; i < 10; i++) {
        stk_push(s, i + 1);
    }

    // ---------------- MARK 1 ----------------
    printf("----- PROGRAM STATE AT MARK 1 (Before stk_destroy) -----\n");
    printf("Address of i (on stack): %p\n", &i);
    printf("Address of s (on stack): %p\n", &s);
    printf("s points to (Stack struct on heap): %p\n", s);
    printf("Address of s->data (within Stack struct): %p\n", &s->data);
    printf("Address of s->top (within Stack struct): %p\n", &s->top);
    printf("Address of s->capacity (within Stack struct): %p\n", &s->capacity);
    printf("s->data points to (heap array): %p\n", s->data);
    printf("s->top currently points to: %p\n", s->top);
    printf("Address of last element in s->data: %p\n", s->top - 1);
    printf("Value of i: %d\n", i);
    printf("Value of s->capacity: %d\n\n", s->capacity);

    // Print contents of the stack array
    int *ptr = s->data;
    while (ptr != s->top) {
        printf("%p: %d\n", ptr, *ptr);
        ptr++;
    }

    printf("\nThe original list: ");
    stk_display(s, 0);

    printf("The reversed list: ");
    stk_display(s, 1);

    // Free the heap memory used by the Stack
    stk_destroy(s);

    // ---------------- MARK 2 ----------------
    printf("\n----- PROGRAM STATE AT MARK 2 (After stk_destroy) -----\n");
    printf("Address of i (on stack): %p\n", &i);
    printf("Address of s (on stack): %p\n", &s);
    printf("s still holds (dangling pointer to freed heap): %p\n", s);
    printf("The Stack struct and its data have been freed.\n");
    printf("Accessing s->data or s->top now would be undefined behavior.\n");
    printf("Value of i: %d\n", i);
    printf("Note: Addresses remain the same, but memory at those locations is no longer valid.\n");

    return 0;
}
