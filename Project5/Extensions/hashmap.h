/*
 * File: hashmap.h
 * Author: Simon Lartey
 * Date: 11/15/25
 *
 * Description:
 *     Header file for a hash map implementation used by the
 *     word-frequency counter. Defines the HashNode and HashMap
 *     structures along with functions for creating the map,
 *     inserting words, freeing memory, and printing the top-N
 *     most frequent words.
 *
 * How to run: NA
 */


#ifndef HASHMAP_H
#define HASHMAP_H

typedef struct HashNode {
    char *word;
    int count;
    struct HashNode *next;
} HashNode;

typedef struct {
    HashNode **table;
    int size;
} HashMap;

HashMap *hm_create(int size);
void hm_insert(HashMap *hm, const char *word);
void hm_free(HashMap *hm);


void hm_print_top(HashMap *hm, int n);

#endif
