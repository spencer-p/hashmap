/*
 * Hashmap lib header
 * A simple reference hashmap implementation with chaining
 *
 * Copyright (c) 2017, Spencer Peterson
 */

#ifndef HASHMAP_H
#define HASHMAP_H

#include "linkedlist.h"

typedef struct {
	LinkedList **array;
	int size;
	int used;
} Hashmap;

// Public interface

Hashmap *hm_new(int capacity);

int hm_set(Hashmap *hashmap, char *key, void *value);

void *hm_get(Hashmap *hashmap, char *key);

void *hm_delete(Hashmap *hashmap, char *key);

float hm_load(Hashmap *hashmap);

void hm_free(Hashmap *hashmap);

#endif
