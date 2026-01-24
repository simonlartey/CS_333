/*
 * Author: Simon Lartey
 * Date: 11/14/25
 * File: wordcounter_hashmap.c
 * Project: Word Counter Using Hash Map
 *
 * Description:
 *     A word-frequency counter implemented with a hash map instead of a
 *     linked list. Each cleaned, lowercase word is inserted into a hash
 *     table, allowing O(1) average-time lookup and updates. After reading
 *     the input file, all entries are collected and sorted to print the
 *     top 20 most frequent words.
 *
 * Compile:
 *     gcc wordcounter_hashmap.c hashmap.c -o wordcounter_hashmap
 *
 * Run:
 *     ./wordcounter_hashmap wctest.txt
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "hashmap.h"



void str_to_lower(char *s) {
    for (int i = 0; s[i]; i++)
        s[i] = tolower(s[i]);
}

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



int compare_nodes(const void *a, const void *b) {
    const HashNode *nodeA = *(const HashNode **)a;
    const HashNode *nodeB = *(const HashNode **)b;
    return nodeB->count - nodeA->count;  // sort descending
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

    HashMap *hm = hm_create(5000);  // big enough table

    char buffer[256];

    while (fscanf(fp, "%255s", buffer) == 1) {
        strip_punct(buffer);
        str_to_lower(buffer);

        if (strlen(buffer) == 0)
            continue;

        hm_insert(hm, buffer);
    }

    fclose(fp);

    // Extract entries to array
    int total = 0;
    HashNode **list = malloc(5000 * sizeof(HashNode *));

    for (int i = 0; i < hm->size; i++) {
        HashNode *node = hm->table[i];
        while (node) {
            list[total++] = node;
            node = node->next;
        }
    }

    // Sort
    qsort(list, total, sizeof(HashNode *), compare_nodes);

    printf("=== Top 20 Words (Hash Map) ===\n");
    int limit = total < 20 ? total : 20;
    for (int i = 0; i < limit; i++) {
        printf("%s %d\n", list[i]->word, list[i]->count);
    }

    free(list);
    hm_free(hm);

    return 0;
}
