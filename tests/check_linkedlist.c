/*
 * Linked List unit tests
 *
 * Copyright (c) 2017, Spencer Peterson
 */

#include <stdlib.h>
#include <check.h>
#include "../src/linkedlist.h"

START_TEST(test_create_list) {
	LinkedList *list;

	list = ll_new();

	ck_assert_ptr_nonnull(list);
}
END_TEST

Suite *linkedlist_suite(void) {
	Suite *s;
	TCase *tc_core;

	s = suite_create("LinkedList");

	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_create_list);
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
