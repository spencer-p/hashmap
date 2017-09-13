/*
 * Linked List lib header
 * Simple LL for use in hashmap chaining
 *
 * Copyright (c) 2017, Spencer Peterson
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// Node object
typedef struct node_t {
	char *key;
	void *value;
	struct node_t *next;
} Node;

// Linked list object
typedef struct {
	int length;
	Node *head;
} LinkedList;

// Public interface

/*
 * returns:
 *  new ll pointer or null
 */
LinkedList *ll_new();

/*
 * args:
 *  list - list to insert in
 *  key, value - kv pair to insert
 * returns:
 *  0 for fail
 *  1 for success
 */
int ll_insert(LinkedList *list, char *key, void *value);

/* args:
 *  list - list to delete from
 *  key - key to delete
 * returns:
 *	the value to be deleted
 */
void *ll_remove(LinkedList *list, char *key);

/* args:
 *  list - list to get from
 *  key - key to get
 * returns:
 *  value for given key
 *
 * Does not account for missing keys.
 */
void *ll_get(LinkedList *list, char *key);

#endif
