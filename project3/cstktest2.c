/**
 * @file cstktest2.c
 * @author mbender & srtaylor
 * @date 2024-03-05
 *
 * Exercises the functionality of cstk 
 * Modified by Simon lartey 10/19/2025
 */
#include "cstk2.h"

typedef struct Account {
    char *name;
    int balance;
} Account;

char *intToString(void *x) {
    int *num = (int *)x;
    char *str = (char *)malloc(12 * sizeof(char));
    sprintf(str, "%d", *num);
    return str;
}

char *account_toString(void *v) {
    Account *acct = (Account *)v;
    int needed = strlen(acct->name) + 20; 
    char *str = (char *)malloc(needed * sizeof(char));
    sprintf(str, "%s: %d", acct->name, acct->balance);
    return str;
}


int main(int argc, char **argv) {
    /**
     * Test stack initialization
     */
    {
        Stack *stack1 = stk_create(10);
        Stack *stack2 = stk_create(10);

        if (stack1 == NULL || stack2 == NULL) {
            printf("Error in stk_create: unable to initialize stack");
            return 0;
        }

        if (stack1 == stack2) {
            printf(
                "Error in stk_create: two stacks created but are pointing to "
                "the same memory.");
            return 0;
        }

        stk_destroy(stack1);
        stk_destroy(stack2);
    }

    /**
     * Test stk_push
     */
    {
        Stack *stack1 = stk_create(1);
        Stack *stack2 = stk_create(1);
        int *someInts = (int *)malloc(sizeof(int) * 2);
        *someInts = 0;
        *(someInts + 1) = 1;

        stk_push(stack1, someInts);
        stk_push(stack2, someInts + 1);

        if (*(stack1->top - 1) != someInts ||
            *(stack2->top - 1) != someInts + 1) {
            printf(
                "Error in stk_push: value not inserted correctly or top not "
                "updated correctly");
            return 0;
        }

        stk_destroy(stack1);
        stk_destroy(stack2);
        free(someInts);
    }

    /**
     * Test stk_peek
     */
    {
        Stack *stack1 = stk_create(1);
        Stack *stack2 = stk_create(1);
        Stack *stack3 = stk_create(10);
        int *someInts = (int *)malloc(sizeof(int) * 6);
        for (int i = 0; i < 6; i++) *(someInts + i) = i;

        stk_push(stack1, someInts);
        stk_push(stack2, someInts + 1);
        for (int i = 0; i < 6; i++) {
            stk_push(stack3, someInts + i);
        }

        if (stk_peek(stack1) != someInts || stk_peek(stack2) != someInts + 1 ||
            stk_peek(stack3) != someInts + 5) {
            printf("Error in stk_peek: incorrect value returned");
            return 0;
        }

        stk_destroy(stack1);
        stk_destroy(stack2);
        stk_destroy(stack3);
        free(someInts);
    }

    /**
     * Test stk_pop
     */
    {
        Stack *stack1 = stk_create(1);
        Stack *stack2 = stk_create(3);
        Stack *stack3 = stk_create(10);
        int *someInts = (int *)malloc(sizeof(int) * 6);
        for (int i = 0; i < 6; i++) *(someInts + i) = i;

        stk_push(stack1, someInts);
        stk_push(stack2, someInts);
        stk_push(stack2, someInts + 1);
        for (int i = 0; i < 6; i++) stk_push(stack3, someInts + i);

        int *val1 = stk_pop(stack1);
        int *val2 = stk_pop(stack2);
        int *val3 = stk_pop(stack3);

        if (*val1 != 0 || *val2 != 1 || *val3 != 5) {
            printf("Error in stk_pop: incorrect value returned");
            return 0;
        }

        stk_destroy(stack1);
        stk_destroy(stack2);
        stk_destroy(stack3);
        free(someInts);
    }

    printf("All non-display tests passed!\n");
    Stack *stack = stk_create(10);
    for (int i = 0; i < 10; i++) {
        int *x = (int *)malloc(sizeof(int));
        *x = i;
        stk_push(stack, x);
    }
    printf("You should now see the numbers from 0 to 9: \n");
    printf("%s\n\n", stk_toString(stack, &intToString));

    for (int i = stk_size(stack); i > 0; i--) stk_pop(stack);

    Account account = {"Max Bender", 10};
    stk_push(stack, &account);
    // why is the above perhaps dangerous?

    Account account2 = {"Stephanie Taylor", 100};
    stk_push(stack, &account2);
    printf(
        "You should now see the string: [Max Bender: 10, Stephanie Taylor: "
        "100]\n");
    printf("%s\n\n", stk_toString(stack, &account_toString));





/*     printf("\n----- MARK 1 MEMORY STATE -----\n");

    // Stack variable
    printf("Address of stack variable: %p\n", (void*)&stack);

    // Heap struct
    printf("Address of Stack struct (heap): %p\n", (void*)stack);

    // Fields inside the struct
    printf("Address of stack->data: %p\n", (void*)&(stack->data));
    printf("stack->data points to (heap array): %p\n", (void*)stack->data);

    printf("Address of stack->top: %p\n", (void*)&(stack->top));
    printf("stack->top currently points to: %p\n", (void*)stack->top);

    printf("Address of stack->capacity: %p\n", (void*)&(stack->capacity));
    printf("Value of stack->capacity: %d\n", stack->capacity);

    // Print current stack size
    printf("Current stack size: %d\n", stk_size(stack));

    // Print the address of each element in the heap array
    printf("\nHeap array elements:\n");
    for (int i = 0; i < stack->capacity; i++) {
        printf("stack->data[%d] is at address %p and stores %p\n", 
            i, (void*)(stack->data + i), (void*)stack->data[i]);
    }

    printf("Address of account struct: %p\n", (void*)&account);
    printf("Address of account.name: %p\n", (void*)&(account.name));
    printf("Address of account.balance: %p\n", (void*)&(account.balance));


    printf("-------------------------------\n"); */



    /**
     * What follows is a test to visually confirm whether stk_destroy
     * is correctly implemented. After uncommenting the lines below,
     * open your task manager (Windows) or Activity Monitor (Mac) and observe
     * that your memory usage doesn't increase while the program runs.
     *
     * In this second version, it will also test if you have avoided memory
     * leaks in your toString method(s).
     */
    // while (1) {
    //     int cap = 100;
    //     Stack *stack = stk_create(cap);
    //     int *ints = (int *)malloc(sizeof(int) * cap);
    //     for (int i = 0; i < cap; i++) {
    //         *(ints + i) = 0x7FFF0000 + i;
    //         stk_push(stack, ints + i);
    //     }
    //     char *toString = stk_toString(stack, &intToString);
    //     // comment out the line(s) below and watch your memory usage explode!
    //     free(toString);
    //     stk_destroy(stack);
    //     free(ints);
    // }
}