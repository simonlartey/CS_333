/*
 * Author: Simon Lartey
 * Date: 11/12/25
 * Project: Word Counter using Linked List
 * Description:
 *      This program reads a text file, normalizes words to lowercase,
 *      strips punctuation, counts occurrences using a LinkedList,
 *      and prints the top 20 most frequent words.
 *
 * How to run:
 *      gcc wordcounter.c linkedlist.c -o wordcounter
 *      ./wordcounter wctest.tx
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "linkedlist.h"

/* Structure to store a word + its frequency */
typedef struct {
    char *word;
    int count;
} WordNode;

/* Convert a string to lowercase */
void str_to_lower(char *s) {
    for (int i = 0; s[i]; i++)
        s[i] = tolower(s[i]);
}

/* Remove punctuation from beginning/end */
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

/* Compare WordNode objects by comparing the words */
int compare_words(void *data, void *target) {
    WordNode *a = data;
    WordNode *b = target;
    return strcmp(a->word, b->word) == 0;  // match
}

/* Free function for clearing list */
void free_wordnode(void *data) {
    WordNode *wn = data;
    free(wn->word);
    free(wn);
}

/* Comparator for qsort: sort by frequency descending */
int compare_freq(const void *a, const void *b) {
    const WordNode *wa = *(const WordNode **)a;
    const WordNode *wb = *(const WordNode **)b;
    return wb->count - wa->count;
}


int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("Error opening file");
        return 1;
    }

    LinkedList *list = ll_create();
    char buffer[256];

    /* Read all words from file */
    while (fscanf(fp, "%255s", buffer) == 1) {

        strip_punct(buffer);
        str_to_lower(buffer);

        if (strlen(buffer) == 0)
            continue;

        /* Temp node for searching */
        WordNode temp;
        temp.word = buffer;

        WordNode *found = ll_find(list, &temp, compare_words);

        if (found) {
            found->count++;
        } else {
            WordNode *newnode = malloc(sizeof(WordNode));
            newnode->word = strdup(buffer);
            newnode->count = 1;

            ll_append(list, newnode);
        }
    }

    fclose(fp);

    

    int n = ll_size(list);
    WordNode **array = malloc(n * sizeof(WordNode *));

    int idx = 0;
    for (Node *cur = list->head; cur; cur = cur->next)
        array[idx++] = (WordNode *)cur->data;

    /* Sort by frequency descending */
    qsort(array, n, sizeof(WordNode *), compare_freq);

    /* Print top 20 */
    printf("\n=== Top 20 Most Frequent Words ===\n");
    int limit = n < 20 ? n : 20;
    for (int i = 0; i < limit; i++)
        printf("%s %d\n", array[i]->word, array[i]->count);

    /* Cleanup */
    free(array);
    ll_clear(list, free_wordnode);
    free(list);

    return 0;
}
