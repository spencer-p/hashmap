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
	Node *new, *t;

	// Try to reuse an existing node if possible
	for (t = list->head; t != NULL; t = t->next) {
		if (strcmp(t->key, key) == 0) {

			// Set new value
			// TODO this destroys the orphan value!
			t->value = value;

			return 1;
		}
	}

	// Create new node
	if ((new = node_new(key, value)) != NULL) {

		// Point new node to its new next
		new->next = list->head;

		// Set node to head
		list->head = new;

		// Change list length
		list->length++;

		return 1;
	}

	return 0;
}

void *ll_remove(LinkedList *list, char *key) {
	Node *t = NULL;
	void *orphan_value = NULL;

	// Only one element or first element is match
	if (list->length == 1 || strcmp(list->head->key, key) == 0) {

		// Save head
		t = list->head;

		// Reset head
		list->head = t->next;

		// Free/get orphan value
		orphan_value = node_free(t);

		// Change list length
		list->length--;
	}
	else if (list->length > 1) {
		// Scrub to the node before
		for (t = list->head; t != NULL; t = t->next) {
			if (t->next != NULL && strcmp(t->next->key, key) == 0) {
				// Free and get orphan value
				orphan_value = node_free(t->next);

				// Remove from the linked list
				t->next = t->next->next;
				
				// Change list length
				list->length--;
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
	if (list->head != NULL) {
		ll_recursive_delete(list->head);
	}
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
	int key_length;

	// Create new node
	if ((new = (Node *) malloc(sizeof(Node))) != NULL) {
		// Initialize values
		new->value = value;
		new->key = NULL;
		new->next = NULL;

		// Create a copy of the key
		key_length = strlen(key)+1;
		if ((key_copy = (char *) malloc(key_length*sizeof(char))) != NULL) {
			strncpy(key_copy, key, key_length);
			new->key = key_copy;
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
