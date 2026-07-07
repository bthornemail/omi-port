/*
 * OMI Layer: test
 * Purpose: Verify URI-CIDR scope parser (omi_port_scope_from_string).
 * Authority: Non-authoritative test.
 */

#include <stdio.h>
#include <string.h>
#include "omi_port.h"
#include "test_harness.h"

int main(void)
{
    OMI_PortScope scope;
    OMI_PortResult r;

    printf("=== test_scope ===\n\n");

    /* 1. file:///repo/input.omi#/64 */
    omi_port_scope_init(&scope);
    r = omi_port_scope_from_string("file:///repo/input.omi#/64", &scope);
    CHECK_RESULT(r, OMI_PORT_OK, "file:///repo/input.omi#/64 parses");
    CHECK(scope.prefix_len == 64, "prefix_len = 64");
    CHECK(strcmp(scope.uri, "file:///repo/input.omi") == 0, "uri = file:///repo/input.omi");

    /* 2. lora://915/node/alpha#/16 */
    omi_port_scope_init(&scope);
    r = omi_port_scope_from_string("lora://915/node/alpha#/16", &scope);
    CHECK_RESULT(r, OMI_PORT_OK, "lora://915/node/alpha#/16 parses");
    CHECK(scope.prefix_len == 16, "prefix_len = 16");
    CHECK(strcmp(scope.uri, "lora://915/node/alpha") == 0, "uri = lora://915/node/alpha");

    /* 3. https://example.com/api#/40 */
    omi_port_scope_init(&scope);
    r = omi_port_scope_from_string("https://example.com/api#/40", &scope);
    CHECK_RESULT(r, OMI_PORT_OK, "https://example.com/api#/40 parses");
    CHECK(scope.prefix_len == 40, "prefix_len = 40");
    CHECK(strcmp(scope.uri, "https://example.com/api") == 0, "uri = https://example.com/api");

    /* 4. missing #/ fails */
    omi_port_scope_init(&scope);
    r = omi_port_scope_from_string("https://example.com/api", &scope);
    CHECK_RESULT(r, OMI_PORT_ERROR_SCOPE_NO_PREFIX, "missing #/ fails");

    /* 5. non-numeric prefix fails */
    omi_port_scope_init(&scope);
    r = omi_port_scope_from_string("https://example.com#/abc", &scope);
    CHECK_RESULT(r, OMI_PORT_ERROR_SCOPE_BAD_PREFIX, "non-numeric prefix fails");

    /* 6. too-long URI fails */
    {
        char long_uri[512];
        int i;
        for (i = 0; i < 300; i++) long_uri[i] = 'a';
        memcpy(long_uri + 300, "#/32", 5);
        omi_port_scope_init(&scope);
        r = omi_port_scope_from_string(long_uri, &scope);
        CHECK_RESULT(r, OMI_PORT_ERROR_SCOPE_TOO_LONG, "too-long URI fails");
    }

    /* 7. null input fails */
    r = omi_port_scope_from_string(NULL, &scope);
    CHECK_RESULT(r, OMI_PORT_ERROR_NULL_INPUT, "null input fails");

    /* 8. prefix out of range (>255) */
    omi_port_scope_init(&scope);
    r = omi_port_scope_from_string("file:///x#/999", &scope);
    CHECK_RESULT(r, OMI_PORT_ERROR_SCOPE_BAD_PREFIX, "prefix >255 fails");

    printf("\n");
    if (test_failures > 0)
        printf("RESULT: %d test(s) FAILED\n", test_failures);
    else
        printf("RESULT: all tests PASSED\n");

    return test_failures > 0 ? 1 : 0;
}
