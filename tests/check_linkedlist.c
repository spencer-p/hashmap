/*
 * Linked List unit tests
 *
 * Copyright (c) 2017, Spencer Peterson
 */

#include <stdlib.h>
#include <check.h>
#include "../src/linkedlist.h"

LinkedList *list;

void setup(void) {
	int i;
	list = ll_new();
	ll_insert(list, "1", "one");
	ll_insert(list, "2", "two");
	ll_insert(list, "3", "three");
	ll_insert(list, "4", "four");
	ll_insert(list, "5", "five");
}

void teardown(void) {
	ll_free(list);
}

START_TEST(test_create_list) {
	ck_assert_ptr_nonnull(list);
	ck_assert_int_eq(list->length, 5);
}
END_TEST

START_TEST(test_insert) {
	int result, prev_length;

	prev_length = list->length;

	result = ll_insert(list, "6", "six");

	ck_assert_int_eq(result, 1);

	ck_assert_int_eq(list->length, prev_length+1);
}
END_TEST

START_TEST(test_remove) {
	char *orphan_value, *survivor;

	orphan_value = (char *) ll_remove(list, "4");

	ck_assert_str_eq(orphan_value, "four");

	survivor = (char *) ll_get(list, "5");

	ck_assert_str_eq(survivor, "five");
}
END_TEST

START_TEST(test_get) {
	char *value;

	// Index first element (O(1) case)
	value = ll_get(list, "1");

	ck_assert_str_eq(value, "one");

	// Index a middle element
	value = ll_get(list, "3");

	ck_assert_str_eq(value, "three");
}
END_TEST

Suite *linkedlist_suite(void) {
	Suite *s;
	TCase *tc_core;

	s = suite_create("LinkedList");

	// Core tests
	tc_core = tcase_create("Core");

	tcase_add_checked_fixture(tc_core, setup, teardown);
	tcase_add_test(tc_core, test_create_list);
	tcase_add_test(tc_core, test_insert);
	tcase_add_test(tc_core, test_remove);
	tcase_add_test(tc_core, test_get);

	suite_add_tcase(s, tc_core);

	return s;
}

int main() {
	int number_failed;
	Suite *s;
	SRunner *sr;

	s = linkedlist_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
