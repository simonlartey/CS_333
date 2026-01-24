/*
 * File: hashmap.c
 * Author: Simon Lartey
 * Date: 11/16/25
 *
 * Description:
 *     Implementation of a simple hash map for counting word frequencies.
 *     Supports hashing, insertion, lookup, memory cleanup, and printing
 *     the top N most frequent words. Used by the word counter and profiler
 *     extensions in this project.
 *
 * How to compile :
 *     gcc wordcounter_hashmap.c hashmap.c -o wordcounter_hashmap
 *
 * How to run :
 *     ./wordcounter_hashmap wctest.txt
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

unsigned long hash(const char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;  

    return hash;
}

HashMap *hm_create(int size) {
    HashMap *hm = malloc(sizeof(HashMap));
    hm->size = size;
    hm->table = calloc(size, sizeof(HashNode *));
    return hm;
}

void hm_insert(HashMap *hm, const char *word) {
    unsigned long idx = hash(word) % hm->size;

    HashNode *node = hm->table[idx];

    while (node) {
        if (strcmp(node->word, word) == 0) {
            node->count++;
            return;
        }
        node = node->next;
    }

    // Not found — insert new node
    HashNode *newnode = malloc(sizeof(HashNode));
    newnode->word = strdup(word);
    newnode->count = 1;
    newnode->next = hm->table[idx];
    hm->table[idx] = newnode;
}

int hm_get(HashMap *hm, const char *word) {
    unsigned long idx = hash(word) % hm->size;

    HashNode *node = hm->table[idx];

    while (node) {
        if (strcmp(node->word, word) == 0)
            return node->count;
        node = node->next;
    }

    return 0;
}

void hm_free(HashMap *hm) {
    for (int i = 0; i < hm->size; i++) {
        HashNode *node = hm->table[i];
        while (node) {
            HashNode *tmp = node;
            node = node->next;
            free(tmp->word);
            free(tmp);
        }
    }
    free(hm->table);
    free(hm);
}



// Comparator for sorting by descending count
static int compare_nodes(const void *a, const void *b) {
    const HashNode *A = *(const HashNode **)a;
    const HashNode *B = *(const HashNode **)b;
    return B->count - A->count;
}

void hm_print_top(HashMap *hm, int n) {
    // Count total nodes
    int total = 0;
    for (int i = 0; i < hm->size; i++) {
        HashNode *node = hm->table[i];
        while (node) {
            total++;
            node = node->next;
        }
    }

    if (total == 0) {
        printf("HashMap is empty.\n");
        return;
    }

    // Gather pointers into an array
    HashNode **array = malloc(total * sizeof(HashNode *));
    int idx = 0;

    for (int i = 0; i < hm->size; i++) {
        HashNode *node = hm->table[i];
        while (node) {
            array[idx++] = node;
            node = node->next;
        }
    }

    // Sort by frequency
    qsort(array, total, sizeof(HashNode *), compare_nodes);

    int limit = (n < total ? n : total);
    printf("\n=== Top %d Words ===\n", limit);

    for (int i = 0; i < limit; i++) {
        printf("%s: %d\n", array[i]->word, array[i]->count);
    }

    free(array);
}
