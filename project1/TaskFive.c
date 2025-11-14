/**
 * @file BankExample.c
 * @author Max Bender
 * @date 2024-01-22
 * 
 * A goofy example to demonstrate need for care when managing strings in C.
 *
 * Modified by Ying Li 08/15/2024
 * Further Modified by simon lartey 09/18/2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Account {
    char name[10];
    int balance;
} Account;

int main(int arg, char *argv[]) {
    Account newAccount = {"", 0};
    printf("Please input your name for a new bank account: ");
    
    scanf("%[^\n]s", newAccount.name);
    printf("Thank you %s, your new account has been initialized with balance %d.",
           newAccount.name, newAccount.balance);

    // inspect memory contents for bad string input
    unsigned char *ptr = (unsigned char *)&newAccount;

    printf("\n\nMemory Contents on Bad String:\n");
    for (int i = 0; i < sizeof(Account); i++) {
        printf("%d: %02X\n", i, ptr[i]);
    }
					 
    return 0;
}
