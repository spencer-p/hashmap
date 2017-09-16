/*
 * Hashmap implementation
 *
 * Copyright (c) 2017, Spencer Peterson
 */

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hashmap.h"

#define DEFAULT_CAPACITY 20

// Private stuff
long long hash_string(char *string);
long long mystery_hash(char *str, int len, int key, int expstart, int reverse);
int mknum(char c);

Hashmap *hm_new(int capacity) {
	Hashmap *new = NULL;
	capacity = (capacity == 0) ? DEFAULT_CAPACITY : capacity;

	if ((new = (Hashmap *) malloc(sizeof(Hashmap))) != NULL) {
		// Initialize ints
		new->size = capacity;
		new->used = 0;

		// Generate LL array
		new->array = (LinkedList **) calloc(capacity, sizeof(LinkedList *));

		if (new->array == NULL) {
			free(new);
			new = NULL;
		}
	}

	return new;
}

int hm_set(Hashmap *hashmap, char *key, void *value) {
	long long hash = hash_string(key) % hashmap->size;

	// Make the LL if necessary
	if (hashmap->array[hash] == NULL) {
		if ((hashmap->array[hash] = ll_new()) == NULL) {
			// Could not allocate linked list
			return 0;
		}
	}

	return ll_insert(hashmap->array[hash], key, value);
}

void *hm_get(Hashmap *hashmap, char *key) {
	void *value = NULL;
	long long hash = hash_string(key) % hashmap->size;

	if (hashmap->array[hash] != NULL) {
		value = ll_get(hashmap->array[hash], key);
	}

	return value;
}

void *hm_delete(Hashmap *hashmap, char *key) {
	void *to_delete = NULL;
	long long hash = hash_string(key) % hashmap->size;

	if (hashmap->array[hash] != NULL) {
		to_delete = ll_remove(hashmap->array[hash], key);
	}

	return to_delete;
}

float hm_load(Hashmap *hashmap) {
	return (float) hashmap->used / hashmap->size;
}

void hm_free(Hashmap *hashmap) {
	int i;
	for (i = 0; i < hashmap->size; i++) {
		if (hashmap->array[i] != NULL) {
			ll_free(hashmap->array[i]);
		}
	}
	free(hashmap->array);
	free(hashmap);
}

long long hash_string(char *string) {
	return mystery_hash(string, strlen(string), 2, 1, 0);
}

// I don't actually know what this hash function is
long long mystery_hash(char *str, int len, int key, int expstart, int reverse) {
    long long hash = 0;
    for (int i = 0; i < len; i++) {
        hash += ((int)str[(reverse) ? len-i-1 : i])*pow(key, expstart+i);
    }
    return hash;
}
