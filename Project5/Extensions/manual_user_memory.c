/*
 * Author: Simon Lartey
 * Date: 11/14/25
 * File: manual_user_memory.c
 *
 * Description:
 *     A simple C program that recreates a JavaScript-style user object
 *     to demonstrate manual memory allocation, dynamic resizing, and
 *     explicit cleanup using free(). This contrasts with JavaScript’s
 *     automatic garbage collection.
 *
 * Compile:
 *     gcc manual_user_memory.c -o manual_user_memory
 *
 * Run:
 *     ./manual_user_memory
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char *username;
    char **posts;
    int post_count;
} User;


User *createUser(const char *name) {
    User *u = malloc(sizeof(User));
    if (!u) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    u->username = strdup(name);
    u->post_count = 0;
    u->posts = NULL;   // no posts yet

    return u;
}


void addPost(User *user, const char *post) {
    user->post_count++;

    // grow the posts array manually
    user->posts = realloc(user->posts, user->post_count * sizeof(char *));
    if (!user->posts) {
        fprintf(stderr, "Reallocation failed\n");
        exit(1);
    }

    // duplicate and store the string
    user->posts[user->post_count - 1] = strdup(post);
}

/* Manual cleanup  */
void freeUser(User *user) {
    for (int i = 0; i < user->post_count; i++)
        free(user->posts[i]);

    free(user->posts);
    free(user->username);
    free(user);
}

int main() {
    User *u1 = createUser("Simon");
    addPost(u1, "Hello world!");

    printf("Username: %s\n", u1->username);
    printf("Posts:\n");
    for (int i = 0; i < u1->post_count; i++)
        printf(" - %s\n", u1->posts[i]);

    // Manual garbage collection
    freeUser(u1);

    return 0;
}
