/**
 * File Name:   extensionThree.c
 * Description: Improved version of the BankExample program that avoids 
 *              buffer overflow by limiting user input. The program 
 *              defines an Account struct with a name and balance, 
 *              prompts the user for their name, and initializes their 
 *              account safely.
 * Author:      Simon Lartey
 * Date:        09/18/2025
 */

#include <stdio.h>
#include <stdlib.h>

// Struct definition for an Account with a fixed-size name and a balance
typedef struct Account {
    char name[10];  // up to 9 characters + null terminator
    int balance;
} Account;

int main() {
    // Initialize account with empty name and zero balance
    Account newAccount = {"", 0};

    // Prompt user for their name, safely reading max 9 chars
    printf("Please input your name (max 9 chars): ");
    scanf("%9s", newAccount.name);  // limits input to prevent overflow

    // Print confirmation of account creation
    printf("Thank you %s, your balance is %d.\n", newAccount.name, newAccount.balance);

    return 0;
}
