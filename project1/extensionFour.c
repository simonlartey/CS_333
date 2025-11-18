/**
 * File Name:   extension_4.c
 * Description: Simple C program to demonstrate common run-time errors:
 *              divide by zero, null pointer dereference, and stack overflow.
 * Author:      Simon Lartey
 * Date:        2/20/25
 */

#include <stdio.h>
#include <stdlib.h>

// ----- Divide by Zero -----
void demo_divide_by_zero() {
    int zero = 0;         // runtime variable
    int x = 5 / zero;     // triggers SIGFPE at runtime
    printf("Result: %d\n", x);
}

// ----- Null Pointer Dereference -----
void demo_null_pointer() {
    int *p = NULL;
    *p = 10;   // causes segmentation fault
}

// ----- Stack Overflow -----
void demo_stack_overflow() {
    demo_stack_overflow();  // infinite recursion
}

// ----- Main Menu -----
int main() {
    int choice;
    printf("Choose a demo:\n");
    printf("1. Divide by Zero\n");
    printf("2. Null Pointer Dereference\n");
    printf("3. Stack Overflow\n");
    printf("Choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: demo_divide_by_zero(); break;
        case 2: demo_null_pointer(); break;
        case 3: demo_stack_overflow(); break;
        default: printf("Invalid choice.\n");
    }
    return 0;
}
