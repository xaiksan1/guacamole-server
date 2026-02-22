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

/* Automatically-generated prototypes for the url suite */
void test_url__append_no_query();
void test_url__append_existing_query();
void test_url__append_bounds();
void test_url__escape_special();
void test_url__escape_nospecial();
void test_url__escape_bounds();

/* Automatically-generated test runner */
int main() {

    /* Init CUnit test registry */
    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();

    /* Create and register all tests for the url suite */
    CU_pSuite url = CU_add_suite("url", NULL, NULL);
    if (url == NULL
        || CU_add_test(url, "append_no_query", test_url__append_no_query) == NULL
        || CU_add_test(url, "append_existing_query", test_url__append_existing_query) == NULL
        || CU_add_test(url, "append_bounds", test_url__append_bounds) == NULL
        || CU_add_test(url, "escape_special", test_url__escape_special) == NULL
        || CU_add_test(url, "escape_nospecial", test_url__escape_nospecial) == NULL
        || CU_add_test(url, "escape_bounds", test_url__escape_bounds) == NULL
    ) goto cleanup;

    /* Force line-buffered output to ensure log messages are visible even if
     * a test crashes */
    setvbuf(stdout, NULL, _IOLBF, 0);
    setvbuf(stderr, NULL, _IOLBF, 0);

    /* Write TAP header */
    printf("1..6\n");

    /* Run all tests in all suites */
    CU_set_test_complete_handler(tap_log_test_completed);
    CU_run_all_tests();

cleanup:
    /* Tests complete */
    CU_cleanup_registry();
    return CU_get_error();

}
