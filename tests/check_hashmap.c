/*
 * Hashmap unit tests
 *
 * Copyright (c) 2017, Spencer Peterson
 */

#include <stdlib.h>
#include <check.h>
#include "../src/hashmap.h"

#define SIMPLE_SIZE 10

Hashmap *hm;

void simple_setup(void) {
	hm = hm_new(SIMPLE_SIZE);
}

void teardown(void) {
	hm_free(hm);
}

START_TEST(test_create) {
	ck_assert_ptr_nonnull(hm);
	ck_assert_float_eq(hm_load(hm), 0);
}
END_TEST

START_TEST(test_set) {
	// Insert two items
	hm_set(hm, "1", "one");
	hm_set(hm, "2", "two");

	// Two of max should be set
	ck_assert_float_eq(hm_load(hm), (float)2/SIMPLE_SIZE);
}
END_TEST

START_TEST(test_remove) {
	// Insert and remove
	hm_set(hm, "1", "one");
	hm_delete(hm, "1");

	// None should be left
	ck_assert_float_eq(hm_load(hm), 0);
}
END_TEST

START_TEST(test_reset) {
	// Set same key twice
	hm_set(hm, "1", "one");
	hm_set(hm, "1", "ONE");

	// Should get new value
	ck_assert_str_eq(hm_get(hm, "1"), "ONE");

	// Load should be 1
	ck_assert_float_eq(hm_load(hm), 1/SIMPLE_SIZE);
}
END_TEST

START_TEST(test_get) {
	hm_set(hm, "1", "one");
	ck_assert_str_eq(hm_get(hm, "1"), "one");
}
END_TEST

Suite *hashmap_suite(void) {
	Suite *s;
	TCase *tc_simple;

	s = suite_create("Hashmap");

	// Core tests
	tc_simple = tcase_create("Simple");

	tcase_add_checked_fixture(tc_simple, simple_setup, teardown);
	tcase_add_test(tc_simple, test_create);
	tcase_add_test(tc_simple, test_set);
	tcase_add_test(tc_simple, test_remove);
	tcase_add_test(tc_simple, test_reset);
	tcase_add_test(tc_simple, test_get);

	suite_add_tcase(s, tc_simple);

	return s;
}

int main() {
	int number_failed;
	Suite *s;
	SRunner *sr;

	s = hashmap_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
