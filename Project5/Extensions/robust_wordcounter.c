/*
 * Author: Simon Lartey
 * Project: Word Counter with Robust Error Handling
 * Description:
 *      This program reads a text file, normalizes words to lowercase,
 *      strips punctuation, counts occurrences using a LinkedList,
 *      and prints the top 20 most frequent words.
 *
 * How to run:
 *      gcc robust_wordcounter.c linkedlist.c -o robust_wordcounter
 *      ./robust_wordcounter wctest.txt
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "linkedlist.h"

/* Structure for a word + count pair */
typedef struct {
    char *word;
    int count;
} WordNode;

/* Convert text to lowercase */
void str_to_lower(char *s) {
    for (int i = 0; s[i]; i++)
        s[i] = tolower(s[i]);
}

/* Strip punctuation from beginning and end of word */
void strip_punct(char *s) {
    int start = 0;
    while (s[start] && ispunct((unsigned char)s[start]))
        start++;

    int end = strlen(s) - 1;
    while (end >= start && ispunct((unsigned char)s[end]))
        end--;

    memmove(s, s + start, end - start + 1);
    s[end - start + 1] = '\0';
}

/* Compare two WordNodes by word */
int compare_words(void *data, void *target) {
    WordNode *a = data;
    WordNode *b = target;
    return strcmp(a->word, b->word) == 0;
}

/* Free a WordNode */
void free_wordnode(void *data) {
    WordNode *wn = data;
    free(wn->word);
    free(wn);
}

/* Comparator for qsort (sort by descending count) */
int cmp(const void *a, const void *b) {
    WordNode *wa = *(WordNode **)a;
    WordNode *wb = *(WordNode **)b;
    return wb->count - wa->count;    // higher count comes first
}

int main(int argc, char *argv[]) {

    /* -------- Robustness Improvement #1: Argument Checking -------- */
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    /* -------- Robustness Improvement #2: File Opening Error Handling -------- */
    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("Error opening file");
        return 1;
    }

    LinkedList *list = ll_create();
    char buffer[256];

    /* Read and process all words */
    while (fscanf(fp, "%255s", buffer) == 1) {

        strip_punct(buffer);
        str_to_lower(buffer);

        /* -------- Robustness Improvement #3: Skip empty strings -------- */
        if (strlen(buffer) == 0)
            continue;

        WordNode temp;
        temp.word = buffer;

        /* Search existing words */
        WordNode *found = ll_find(list, &temp, compare_words);

        if (found) {
            found->count++;
        } else {
            /* Create new node */
            WordNode *newnode = malloc(sizeof(WordNode));
            newnode->word = strdup(buffer);
            newnode->count = 1;
            ll_append(list, newnode);
        }
    }

    fclose(fp);

    /* Convert list to array for sorting */
    int n = ll_size(list);
    WordNode **array = malloc(n * sizeof(WordNode *));
    int i = 0;

    for (Node *cur = list->head; cur; cur = cur->next)
        array[i++] = (WordNode *)cur->data;

    /* Sort descending by count */
    qsort(array, n, sizeof(WordNode *), cmp);

    /* Print top 20 words */
    printf("\n=== Top 20 Most Frequent Words ===\n");
    int limit = (n < 20) ? n : 20;
    for (int k = 0; k < limit; k++) {
        printf("%s %d\n", array[k]->word, array[k]->count);
    }

    /* -------- Robustness Improvement #4: Complete Cleanup -------- */
    free(array);
    ll_clear(list, free_wordnode);
    free(list);

    return 0;
}
