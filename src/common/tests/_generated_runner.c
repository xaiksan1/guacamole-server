/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <stdlib.h>
#include <CUnit/TestRun.h>

/**
 * The current test number, as required by the TAP format. This value is
 * automatically incremented by tap_log_test_completed() after each test is
 * run.
 */
int tap_test_number = 1;

/**
 * Logs the status of a CUnit test which just completed. This implementation
 * logs test completion in TAP format.
 *
 * @param test
 *     The CUnit test which just completed.
 *
 * @param suite
 *     The CUnit test suite associated with the test.
 *
 * @param failure
 *     The head element of the test failure list, or NULL if the test passed.
 */
static void tap_log_test_completed(const CU_pTest test,
        const CU_pSuite suite, const CU_pFailureRecord failure) {

    /* Log success/failure in TAP format */
    if (failure == NULL)
        printf("ok %i - [%s] %s: OK\n",
            tap_test_number, suite->pName, test->pName);
    else
        printf("not ok %i - [%s] %s: Assertion failed on %s:%i: %s\n",
            tap_test_number, suite->pName, test->pName,
            failure->strFileName, failure->uiLineNumber,
            failure->strCondition);

    tap_test_number++;

}

/* Automatically-generated prototypes for the rect suite */
void test_rect__clip_and_split();
void test_rect__constrain();
void test_rect__expand_to_grid();
void test_rect__extend();
void test_rect__init();
void test_rect__intersects();

/* Automatically-generated prototypes for the string suite */
void test_string__guac_count_occurrences();
void test_string__split();

/* Automatically-generated prototypes for the iconv suite */
void test_iconv__preserve();
void test_iconv__normalize_unix();
void test_iconv__normalize_crlf();

/* Automatically-generated test runner */
int main() {

    /* Init CUnit test registry */
    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();

    /* Create and register all tests for the rect suite */
    CU_pSuite rect = CU_add_suite("rect", NULL, NULL);
    if (rect == NULL
        || CU_add_test(rect, "clip_and_split", test_rect__clip_and_split) == NULL
        || CU_add_test(rect, "constrain", test_rect__constrain) == NULL
        || CU_add_test(rect, "expand_to_grid", test_rect__expand_to_grid) == NULL
        || CU_add_test(rect, "extend", test_rect__extend) == NULL
        || CU_add_test(rect, "init", test_rect__init) == NULL
        || CU_add_test(rect, "intersects", test_rect__intersects) == NULL
    ) goto cleanup;

    /* Create and register all tests for the string suite */
    CU_pSuite string = CU_add_suite("string", NULL, NULL);
    if (string == NULL
        || CU_add_test(string, "guac_count_occurrences", test_string__guac_count_occurrences) == NULL
        || CU_add_test(string, "split", test_string__split) == NULL
    ) goto cleanup;

    /* Create and register all tests for the iconv suite */
    CU_pSuite iconv = CU_add_suite("iconv", NULL, NULL);
    if (iconv == NULL
        || CU_add_test(iconv, "preserve", test_iconv__preserve) == NULL
        || CU_add_test(iconv, "normalize_unix", test_iconv__normalize_unix) == NULL
        || CU_add_test(iconv, "normalize_crlf", test_iconv__normalize_crlf) == NULL
    ) goto cleanup;

    /* Force line-buffered output to ensure log messages are visible even if
     * a test crashes */
    setvbuf(stdout, NULL, _IOLBF, 0);
    setvbuf(stderr, NULL, _IOLBF, 0);

    /* Write TAP header */
    printf("1..11\n");

    /* Run all tests in all suites */
    CU_set_test_complete_handler(tap_log_test_completed);
    CU_run_all_tests();

cleanup:
    /* Tests complete */
    CU_cleanup_registry();
    return CU_get_error();

}
