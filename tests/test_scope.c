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

    /* 9. URI-CIDR is scope grammar, not gauge grammar */
    {
        OMI_PortScope s;
        /* A valid URI-CIDR scope parses into OMI_PortScope (uri + prefix_len),
         * not into a gauge. Gauges use omi_port_is_f_gauge(uint8_t) separately. */
        omi_port_scope_from_string("file:///x#/64", &s);
        CHECK(s.prefix_len == 64, "scope-from-string produces prefix_len, not gauge");
        CHECK(omi_port_is_f_gauge(s.prefix_len) == 0,
              "scope prefix_len (64) is not a valid F* gauge (must be F0..FF)");
        /* Scope values 0..255 are NOT gauges; only F0..FF are gauges */
        CHECK(omi_port_is_f_gauge(0x40) == 0,
              "scope prefix (0x40/64) correctly rejected as gauge");
    }

    /* 10. F* gauge values are rejected as scope prefixes */
    {
        OMI_PortScope s;
        r = omi_port_scope_from_string("file:///x#/240", &s);
        CHECK_RESULT(r, OMI_PORT_OK, "F0 gauge value (240) parses as scope prefix");
        CHECK(s.prefix_len == 240, "prefix_len = 240");
        /* 240 = 0xF0 is a valid gauge, but as a scope prefix it's a decimal 240 */
    }

    printf("\n");
    if (test_failures > 0)
        printf("RESULT: %d test(s) FAILED\n", test_failures);
    else
        printf("RESULT: all tests PASSED\n");

    return test_failures > 0 ? 1 : 0;
}
