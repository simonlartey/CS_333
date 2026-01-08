/*
 * Author: Simon Lartey
 * Date: 10/18/25
 * file: cstk2.c
 * 
 * Description:
 * This file implements a generic stack that can store pointers to any type of data.
 * Each stack operation works with void pointers so it can be used for integers,
 * strings, structs, or any other data type.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cstk2.h"

/* Creates a new stack with the given maximum capacity. */
Stack *stk_create(int capacity) {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack->data = malloc(capacity * sizeof(void *));
    stack->top = stack->data;
    stack->capacity = capacity;
    return stack;
}

/* Frees memory used by the stack structure and its data array.
   Does not free the items stored in the stack. */
void stk_destroy(Stack *stack) {
    free(stack->data);
    free(stack);
}

/* Returns the number of elements currently in the stack. */
int stk_size(Stack *stack) {
    return (int)(stack->top - stack->data);
}

/* Pushes a new item onto the stack if there is space left. */
void stk_push(Stack *stack, void *item) {
    if (stk_size(stack) < stack->capacity) {
        *stack->top = item;
        stack->top++;
    } else {
        printf("Warning: attempting to push to a full stack!\n");
    }
}

/* Returns the top item of the stack without removing it. */
void *stk_peek(Stack *stack) {
    if (stk_size(stack) > 0) {
        return *(stack->top - 1);
    }
    printf("Warning: attempting to peek an empty stack!\n");
    return NULL;
}

/* Removes and returns the item at the top of the stack. */
void *stk_pop(Stack *stack) {
    if (stk_size(stack) > 0) {
        stack->top--;
        return *(stack->top);
    }
    printf("Warning: attempting to pop an empty stack!\n");
    return NULL;
}

/* Helper function to calculate the length of a string. */
static int len(char *string) {
    int length = 0;
    while (string[length] != '\0') {
        length++;
    }
    return length;
}

/* Builds a string representation of the stack using a custom toString function. */
char *stk_toString(Stack *stack, char *(*toString)(void *)) {
    int numItems = stk_size(stack);

    /* If the stack is empty, just return "[]" */
    if (numItems == 0) {
        char *empty = (char *)malloc(3 * sizeof(char));
        strcpy(empty, "[]");
        return empty;
    }

    int allocation_size = 2; // for [ and ]
    allocation_size += 2 * (numItems - 1); // for ", "
    allocation_size += 1; // for null terminator

    /* Calculate total space needed for all item strings */
    void **data_ptr = stack->data;
    while (data_ptr != stack->top) {
        char *str = toString(*data_ptr);
        allocation_size += len(str);
        free(str);
        data_ptr++;
    }

    char *result = (char *) malloc(allocation_size * sizeof(char));
    char *result_ptr = result;

    *result_ptr++ = '[';

    data_ptr = stack->data;
    while (data_ptr != stack->top) {
        char *str = toString(*data_ptr);
        for (int i = 0; str[i] != '\0'; i++) {
            *result_ptr++ = str[i];
        }
        free(str);

        if ((data_ptr + 1) != stack->top) {
            *result_ptr++ = ',';
            *result_ptr++ = ' ';
        }
        data_ptr++;
    }

    *result_ptr++ = ']';
    *result_ptr = '\0';

    return result;
}
