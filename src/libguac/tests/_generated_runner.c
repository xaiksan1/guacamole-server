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

/* Automatically-generated prototypes for the client suite */
void test_client__buffer_pool();
void test_client__layer_pool();

/* Automatically-generated prototypes for the string suite */
void test_string__strdup();
void test_string__strlcat();
void test_string__strlcat_truncate();
void test_string__strlcat_nospace();
void test_string__strlcat_nonull();
void test_string__strlcpy();
void test_string__strlcpy_truncate();
void test_string__strlcpy_nospace();
void test_string__strljoin();
void test_string__strljoin_truncate();
void test_string__strljoin_nospace();
void test_string__strnstr();

/* Automatically-generated prototypes for the parser suite */
void test_parser__append();
void test_parser__read();

/* Automatically-generated prototypes for the protocol suite */
void test_protocol__decode_base64();

/* Automatically-generated prototypes for the guac_protocol suite */
void test_guac_protocol__version_to_string();
void test_guac_protocol__string_to_version();

/* Automatically-generated prototypes for the pool suite */
void test_pool__next_free();

/* Automatically-generated prototypes for the unicode suite */
void test_unicode__utf8_charsize();
void test_unicode__utf8_read();
void test_unicode__utf8_strlen();
void test_unicode__utf8_write();

/* Automatically-generated prototypes for the id suite */
void test_id__unique();
void test_id__format();
void test_id__prefix();

/* Automatically-generated prototypes for the socket suite */
void test_socket__fd_send_instruction();
void test_socket__nested_send_instruction();

/* Automatically-generated prototypes for the gauc_protocol suite */
void test_gauc_protocol__version_comparison();

/* Automatically-generated test runner */
int main() {

    /* Init CUnit test registry */
    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();

    /* Create and register all tests for the client suite */
    CU_pSuite client = CU_add_suite("client", NULL, NULL);
    if (client == NULL
        || CU_add_test(client, "buffer_pool", test_client__buffer_pool) == NULL
        || CU_add_test(client, "layer_pool", test_client__layer_pool) == NULL
    ) goto cleanup;

    /* Create and register all tests for the string suite */
    CU_pSuite string = CU_add_suite("string", NULL, NULL);
    if (string == NULL
        || CU_add_test(string, "strdup", test_string__strdup) == NULL
        || CU_add_test(string, "strlcat", test_string__strlcat) == NULL
        || CU_add_test(string, "strlcat_truncate", test_string__strlcat_truncate) == NULL
        || CU_add_test(string, "strlcat_nospace", test_string__strlcat_nospace) == NULL
        || CU_add_test(string, "strlcat_nonull", test_string__strlcat_nonull) == NULL
        || CU_add_test(string, "strlcpy", test_string__strlcpy) == NULL
        || CU_add_test(string, "strlcpy_truncate", test_string__strlcpy_truncate) == NULL
        || CU_add_test(string, "strlcpy_nospace", test_string__strlcpy_nospace) == NULL
        || CU_add_test(string, "strljoin", test_string__strljoin) == NULL
        || CU_add_test(string, "strljoin_truncate", test_string__strljoin_truncate) == NULL
        || CU_add_test(string, "strljoin_nospace", test_string__strljoin_nospace) == NULL
        || CU_add_test(string, "strnstr", test_string__strnstr) == NULL
    ) goto cleanup;

    /* Create and register all tests for the parser suite */
    CU_pSuite parser = CU_add_suite("parser", NULL, NULL);
    if (parser == NULL
        || CU_add_test(parser, "append", test_parser__append) == NULL
        || CU_add_test(parser, "read", test_parser__read) == NULL
    ) goto cleanup;

    /* Create and register all tests for the protocol suite */
    CU_pSuite protocol = CU_add_suite("protocol", NULL, NULL);
    if (protocol == NULL
        || CU_add_test(protocol, "decode_base64", test_protocol__decode_base64) == NULL
    ) goto cleanup;

    /* Create and register all tests for the guac_protocol suite */
    CU_pSuite guac_protocol = CU_add_suite("guac_protocol", NULL, NULL);
    if (guac_protocol == NULL
        || CU_add_test(guac_protocol, "version_to_string", test_guac_protocol__version_to_string) == NULL
        || CU_add_test(guac_protocol, "string_to_version", test_guac_protocol__string_to_version) == NULL
    ) goto cleanup;

    /* Create and register all tests for the pool suite */
    CU_pSuite pool = CU_add_suite("pool", NULL, NULL);
    if (pool == NULL
        || CU_add_test(pool, "next_free", test_pool__next_free) == NULL
    ) goto cleanup;

    /* Create and register all tests for the unicode suite */
    CU_pSuite unicode = CU_add_suite("unicode", NULL, NULL);
    if (unicode == NULL
        || CU_add_test(unicode, "utf8_charsize", test_unicode__utf8_charsize) == NULL
        || CU_add_test(unicode, "utf8_read", test_unicode__utf8_read) == NULL
        || CU_add_test(unicode, "utf8_strlen", test_unicode__utf8_strlen) == NULL
        || CU_add_test(unicode, "utf8_write", test_unicode__utf8_write) == NULL
    ) goto cleanup;

    /* Create and register all tests for the id suite */
    CU_pSuite id = CU_add_suite("id", NULL, NULL);
    if (id == NULL
        || CU_add_test(id, "unique", test_id__unique) == NULL
        || CU_add_test(id, "format", test_id__format) == NULL
        || CU_add_test(id, "prefix", test_id__prefix) == NULL
    ) goto cleanup;

    /* Create and register all tests for the socket suite */
    CU_pSuite socket = CU_add_suite("socket", NULL, NULL);
    if (socket == NULL
        || CU_add_test(socket, "fd_send_instruction", test_socket__fd_send_instruction) == NULL
        || CU_add_test(socket, "nested_send_instruction", test_socket__nested_send_instruction) == NULL
    ) goto cleanup;

    /* Create and register all tests for the gauc_protocol suite */
    CU_pSuite gauc_protocol = CU_add_suite("gauc_protocol", NULL, NULL);
    if (gauc_protocol == NULL
        || CU_add_test(gauc_protocol, "version_comparison", test_gauc_protocol__version_comparison) == NULL
    ) goto cleanup;

    /* Force line-buffered output to ensure log messages are visible even if
     * a test crashes */
    setvbuf(stdout, NULL, _IOLBF, 0);
    setvbuf(stderr, NULL, _IOLBF, 0);

    /* Write TAP header */
    printf("1..30\n");

    /* Run all tests in all suites */
    CU_set_test_complete_handler(tap_log_test_completed);
    CU_run_all_tests();

cleanup:
    /* Tests complete */
    CU_cleanup_registry();
    return CU_get_error();

}
