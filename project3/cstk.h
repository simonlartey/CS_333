/*
 * File:        cstk.h
 * Author:      Simon Lartey
 * Date:        October 15, 2025
 * Description: Header file for a simple stack implementation in C.
 *              Contains the structure definition and function declarations
 *              for creating, managing, and freeing a stack of integers.
 */

#ifndef CSTK_H
#define CSTK_H

/* Stack structure:
 * data     → points to the beginning of the stack’s storage area
 * top      → points to the next open slot for pushing a new element
 * capacity → maximum number of elements the stack can hold
 */
typedef struct Stack {
    int *data;
    int *top;
    int capacity;
} Stack;


/* Creates a new stack with the given maximum capacity.
 * Returns a pointer to the new stack.
 */
Stack *stk_create(int capacity);


/* Returns 1 if the stack is empty, 0 otherwise. */
int stk_empty(Stack *stack);


/* Returns 1 if the stack is full, 0 otherwise. */
int stk_full(Stack *stack);

/* Pushes a value onto the stack if there’s room.
 * If the stack is full, prints a warning and does nothing.
 */
void stk_push(Stack *stack, int value);


/* Returns the top value of the stack without removing it.
 * If the stack is empty, prints a warning and returns 0.
 */
int stk_peek(Stack *stack);



/* Removes and returns the top value of the stack.
 * If the stack is empty, prints a warning and returns 0.
 */
int stk_pop(Stack *stack);


/* Prints the contents of the stack.
 * If 'order' is 1, prints in reverse (LILO);
 * otherwise prints in the normal order (LIFO).
 */
void stk_display(Stack *stack, int order);


/* Frees all memory used by the stack. */
void stk_destroy(Stack *stack);


/* Makes a copy of the given stack and returns it. */
Stack *stk_copy(Stack *stack);

#endif /* CSTK_H */
