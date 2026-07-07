/*
 * OMI Layer: test
 * Purpose: Shared test harness CHECK macro for omi-port tests.
 * Authority: Non-authoritative test support.
 */

#ifndef OMI_PORT_TEST_HARNESS_H
#define OMI_PORT_TEST_HARNESS_H

#include <stdio.h>

static int test_failures = 0;

#define CHECK(cond, msg)                                            \
    do {                                                            \
        if (cond) {                                                 \
            printf("  PASS: %s\n", msg);                            \
        } else {                                                    \
            printf("  FAIL: %s\n", msg);                            \
            test_failures++;                                        \
        }                                                           \
    } while (0)

#define CHECK_RESULT(r, expected, msg)                              \
    do {                                                            \
        if ((r) == (expected)) {                                    \
            printf("  PASS: %s\n", msg);                            \
        } else {                                                    \
            printf("  FAIL: %s (got %d, expected %d)\n",           \
                   msg, (int)(r), (int)(expected));                 \
            test_failures++;                                        \
        }                                                           \
    } while (0)

#define CHECK_STR_EQ(a, b, msg)                                     \
    do {                                                            \
        if (strcmp((a), (b)) == 0) {                                \
            printf("  PASS: %s\n", msg);                            \
        } else {                                                    \
            printf("  FAIL: %s (\"%s\" != \"%s\")\n",              \
                   msg, (a), (b));                                  \
            test_failures++;                                        \
        }                                                           \
    } while (0)

#endif /* OMI_PORT_TEST_HARNESS_H */
