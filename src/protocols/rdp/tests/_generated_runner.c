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

/* Automatically-generated prototypes for the fs suite */
void test_fs__basename_windows();
void test_fs__basename_unix();
void test_fs__basename_mixed();
void test_fs__normalize_absolute_windows();
void test_fs__normalize_absolute_unix();
void test_fs__normalize_absolute_mixed();
void test_fs__normalize_relative_windows();
void test_fs__normalize_relative_unix();
void test_fs__normalize_relative_mixed();
void test_fs__normalize_long();
void test_fs__normalize_deep();

/* Automatically-generated test runner */
int main() {

    /* Init CUnit test registry */
    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();

    /* Create and register all tests for the fs suite */
    CU_pSuite fs = CU_add_suite("fs", NULL, NULL);
    if (fs == NULL
        || CU_add_test(fs, "basename_windows", test_fs__basename_windows) == NULL
        || CU_add_test(fs, "basename_unix", test_fs__basename_unix) == NULL
        || CU_add_test(fs, "basename_mixed", test_fs__basename_mixed) == NULL
        || CU_add_test(fs, "normalize_absolute_windows", test_fs__normalize_absolute_windows) == NULL
        || CU_add_test(fs, "normalize_absolute_unix", test_fs__normalize_absolute_unix) == NULL
        || CU_add_test(fs, "normalize_absolute_mixed", test_fs__normalize_absolute_mixed) == NULL
        || CU_add_test(fs, "normalize_relative_windows", test_fs__normalize_relative_windows) == NULL
        || CU_add_test(fs, "normalize_relative_unix", test_fs__normalize_relative_unix) == NULL
        || CU_add_test(fs, "normalize_relative_mixed", test_fs__normalize_relative_mixed) == NULL
        || CU_add_test(fs, "normalize_long", test_fs__normalize_long) == NULL
        || CU_add_test(fs, "normalize_deep", test_fs__normalize_deep) == NULL
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
