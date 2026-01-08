/*
 * File:        cstk.c
 * Author:      Simon Lartey
 * Date:        October 15, 2025
 * Description: Implementation of a simple integer stack in C.
 *              Provides basic operations for creating, using,
 *              copying, and destroying a stack.
 */

#include "cstk.h"
#include <stdlib.h>
#include <stdio.h>

/* Creates a new stack that can hold up to 'capacity' integers.
 * Allocates memory for both the Stack struct and its data array.
 * Returns a pointer to the new stack, or NULL if allocation fails.
 */
Stack *stk_create(int capacity) {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    if (stack == NULL) {
        printf("Error: unable to allocate memory for stack.\n");
        return NULL;
    }

    stack->data = (int *) malloc(capacity * sizeof(int));
    if (stack->data == NULL) {
        printf("Error: unable to allocate memory for stack data.\n");
        free(stack);
        return NULL;
    }

    stack->capacity = capacity;
    stack->top = stack->data;  // top starts at the beginning (empty stack)
    return stack;
}


/* Returns 1 if the stack is empty (no elements), otherwise 0. */
int stk_empty(Stack *stack) {
    return stack->top == stack->data;
}


/* Returns 1 if the stack is full (no more room), otherwise 0. */
int stk_full(Stack *stack) {
    return stack->top == (stack->data + stack->capacity);
}


/* Pushes a new value onto the top of the stack.
 * If the stack is full, prints a warning and leaves it unchanged.
 */
void stk_push(Stack *stack, int value) {
    if (stk_full(stack)) {
        printf("Warning: cannot push to a full stack.\n");
        return;
    }
    *(stack->top) = value;
    stack->top++;
}


/* Removes and returns the value at the top of the stack.
 * If the stack is empty, prints a warning and returns 0.
 */
int stk_pop(Stack *stack) {
    if (stk_empty(stack)) {
        printf("Warning: cannot pop an empty stack.\n");
        return 0;
    }
    stack->top--;
    return *(stack->top);
}


/* Returns (but does not remove) the value on top of the stack.
 * If the stack is empty, prints a warning and returns 0.
 */
int stk_peek(Stack *stack) {
    if (stk_empty(stack)) {
        printf("Warning: cannot peek an empty stack.\n");
        return 0;
    }
    return *(stack->top - 1);
}

/* Displays the contents of the stack.
 * If 'order' is 1 → prints from bottom to top (LILO).
 * If 'order' is 0 → prints from top to bottom (LIFO).
 */
void stk_display(Stack *stack, int order) {
    if (order == 1) {
        for (int *ptr = stack->data; ptr != stack->top; ptr++) {
            printf("%d ", *ptr);
        }
    } else {
        for (int *ptr = stack->top - 1; ptr >= stack->data; ptr--) {
            printf("%d ", *ptr);
        }
    }
    printf("\n");
}


/* Makes a deep copy of the given stack and returns it.
 * The new stack has the same capacity and contains the same elements
 * in the same order, but lives in a separate memory space.
 */
Stack *stk_copy(Stack *stack) {
    Stack *new_stack = stk_create(stack->capacity);
    if (new_stack == NULL) return NULL;

    for (int *ptr = stack->data; ptr != stack->top; ptr++) {
        *(new_stack->top) = *ptr;
        new_stack->top++;
    }
    return new_stack;
}


/* Frees all memory used by the stack.
 * Safe to call even if the stack is empty or partially used.
 */
void stk_destroy(Stack *stack) {
    if (stack != NULL) {
        free(stack->data);
        free(stack);
    }
    
}
