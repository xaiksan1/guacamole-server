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

#include "common/rect.h"

#include <CUnit/CUnit.h>

/**
 * Test which verifies intersection testing via guac_common_rect_intersects().
 */
void test_rect__intersects() {

    int res;

    guac_common_rect min;
    guac_common_rect rect;

    guac_common_rect_init(&min, 10, 10, 10, 10);

    /* Rectangle intersection - empty
     * rectangle is outside */
    guac_common_rect_init(&rect, 25, 25, 5, 5);
    res = guac_common_rect_intersects(&rect, &min);
    CU_ASSERT_EQUAL(0, res);

    /* Rectangle intersection - complete
     * rectangle is completely inside */
    guac_common_rect_init(&rect, 11, 11, 5, 5);
    res = guac_common_rect_intersects(&rect, &min);
    CU_ASSERT_EQUAL(2, res);

    /* Rectangle intersection - partial
     * rectangle intersects UL */
    guac_common_rect_init(&rect, 8, 8, 5, 5);
    res = guac_common_rect_intersects(&rect, &min);
    CU_ASSERT_EQUAL(1, res);

    /* Rectangle intersection - partial
     * rectangle intersects LR */
    guac_common_rect_init(&rect, 18, 18, 5, 5);
    res = guac_common_rect_intersects(&rect, &min);
    CU_ASSERT_EQUAL(1, res);

    /* Rectangle intersection - complete
     * rect intersects along UL but inside */
    guac_common_rect_init(&rect, 10, 10, 5, 5);
    res = guac_common_rect_intersects(&rect, &min);
    CU_ASSERT_EQUAL(2, res);

    /* Rectangle intersection - partial
     * rectangle intersects along L but outside */
    guac_common_rect_init(&rect, 5, 10, 5, 5);
    res = guac_common_rect_intersects(&rect, &min);
    CU_ASSERT_EQUAL(1, res);

    /* Rectangle intersection - complete
     * rectangle intersects along LR but rest is inside */
    guac_common_rect_init(&rect, 15, 15, 5, 5);
    res = guac_common_rect_intersects(&rect, &min);
    CU_ASSERT_EQUAL(2, res);

    /* Rectangle intersection - partial
     * rectangle intersects along R but rest is outside */
    guac_common_rect_init(&rect, 20, 10, 5, 5);
    res = guac_common_rect_intersects(&rect, &min);
    CU_ASSERT_EQUAL(1, res);

    /* Rectangle intersection - partial
     * rectangle encloses min; which is a partial intersection */
    guac_common_rect_init(&rect, 5, 5, 20, 20);
    res = guac_common_rect_intersects(&rect, &min);
    CU_ASSERT_EQUAL(1, res);

}

