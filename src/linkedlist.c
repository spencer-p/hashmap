/*
 * Linked List implementation
 *
 * Copyright (c) 2017, Spencer Peterson
 */

#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

// Private functions
void ll_recursive_delete(Node *head);

// Node management
Node *node_new(char *key, void *value);
Node *node_free(Node *node);

LinkedList *ll_new() {
	LinkedList *new = NULL;

	// Create new list and initialize
	new = (LinkedList *) malloc(sizeof(LinkedList));
	if (new != NULL) {
		new->length = 0;
		new->head = NULL;
	}

	return new;
}

int ll_insert(LinkedList *list, char *key, void *value) {
	Node *new;

	// Create new node
	if ((new = node_new(key, value)) != NULL) {

		// Point new node to its new next
		new->next = list->head;

		// Set node to head
		list->head = new->next;

		return 1;
	}

	return 0;
}

void *ll_remove(LinkedList *list, char *key) {
	Node *t = NULL;
	void *orphan_value = NULL;

	if (list->length == 1) {
		// Free/get orphan value
		orphan_value = node_free(list->head);

		// Reset head
		list->head = NULL;
	}
	else if (list->length > 1) {
		// Scrub to the node before
		for (t = list->head; t != NULL; t = t->next) {
			if (t->next != NULL && strcmp(t->next->key, key) == 0) {
				// Free and get orphan value
				orphan_value = node_free(t->next);

				// Remove from the linked list
				t->next = t->next->next;
			}
		}
	}

	return orphan_value;
}

/*
 * This function does not account for missing keys.
 * Only use this if you are sure the key exists.
 */
void *ll_get(LinkedList *list, char *key) {
	Node *t = NULL;

	// Find relevant node
	if (list->length == 1) {
		// Only one element means we're already there
		t = list->head;
	}
	else if (list->length > 1) {
		// Scrub to the node
		for (t = list->head; t != NULL; t = t->next) {
			if (strcmp(t->key, key) == 0) {
				break;
			}
		}
	}

	// Return the node's value
	return t->value;
}

void ll_free(LinkedList *list) {
	ll_recursive_delete(list->head);
	free(list);
}

void ll_recursive_delete(Node *head) {
	if (head->next != NULL) {
		ll_recursive_delete(head->next);
	}
	node_free(head);
}

/*
 * args:
 *	key, value - the key value pair to insert
 * returns:
 *	pointer to new node or null
 */
Node *node_new(char *key, void *value) {
	Node *new;
	char *key_copy;

	// Create new node
	if ((new = (Node *) malloc(sizeof(Node))) != NULL) {

		// Create a copy of the key
		if ((key_copy = (char *) malloc(strlen(key)*sizeof(char))) != NULL) {

			// Initialize values
			new->key = key_copy;
			new->value = value;
			new->next = NULL;
		}
		else {

			// Failed key_copy, destroy the new node
			free(new);
			new = NULL;
		}
	}

	return new;
}

/*
 * args:
 *	node - the node to free
 * returns:
 *  the value of the node (unfreed)
 */
Node *node_free(Node *node) {
	void *orphan_value = node->value;

	// Free memory
	free(node->key);
	node->key = NULL;
	free(node);

	return orphan_value;
}
