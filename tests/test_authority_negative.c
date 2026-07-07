/*
 * OMI Layer: test
 * Purpose: Prove omi-port v0 never becomes authoritative even after
 *          manual mutation of all authority flags to 1.
 * Authority: Non-authoritative test.
 *
 * This mirrors the negative authority test pattern from omi-lisp:
 * even if a caller mutates every authority flag to 1, omi-port v0
 * queries still return 0 because the dormant layer does not confer
 * authority.
 */

#include <stdio.h>
#include <string.h>
#include "omi_port.h"
#include "test_harness.h"

int main(void)
{
    OMI_PortAuthority auth;
    OMI_PortScope src, tgt;
    OMI_PortRoute r;

    printf("=== test_authority_negative ===\n\n");

    /* 1. Fresh route: all flags 0, queries return 0 */
    omi_port_scope_from_string("file:///a#/8", &src);
    omi_port_scope_from_string("file:///b#/16", &tgt);
    omi_port_transform(&src, &tgt, 0xFF, &r);

    CHECK(r.authority.accepted  == 0, "fresh route: accepted = 0");
    CHECK(r.authority.validated == 0, "fresh route: validated = 0");
    CHECK(r.authority.receipted == 0, "fresh route: receipted = 0");
    CHECK(r.authority.connects  == 0, "fresh route: connects = 0");
    CHECK(r.authority.transmits == 0, "fresh route: transmits = 0");
    CHECK(r.authority.mounts    == 0, "fresh route: mounts = 0");

    CHECK(omi_port_is_authoritative(&r.authority) == 0,
          "fresh route: is_authoritative = 0");
    CHECK(omi_port_has_side_effects(&r.authority) == 0,
          "fresh route: has_side_effects = 0");

    /* 2. Manually set ALL authority flags to 1 */
    memset(&auth, 0, sizeof(auth));
    auth.accepted   = 1;
    auth.validated  = 1;
    auth.receipted  = 1;
    auth.connects   = 1;
    auth.transmits  = 1;
    auth.mounts     = 1;

    /* 3. Prove queries still return 0 despite flags = 1 */
    CHECK(omi_port_is_authoritative(&auth) == 0,
          "mutated flags[all=1]: is_authoritative = 0 (v0 stub)");
    CHECK(omi_port_has_side_effects(&auth) == 0,
          "mutated flags[all=1]: has_side_effects = 0 (v0 stub)");

    /* 4. Partial mutations also return 0 */
    memset(&auth, 0, sizeof(auth));
    auth.accepted = 1;
    CHECK(omi_port_is_authoritative(&auth) == 0,
          "mutated flags[accepted=1]: is_authoritative = 0");

    memset(&auth, 0, sizeof(auth));
    auth.connects = 1;
    CHECK(omi_port_has_side_effects(&auth) == 0,
          "mutated flags[connects=1]: has_side_effects = 0");

    /* 5. Transform does not set connects/transmits/mounts */
    {
        OMI_PortRoute r2;
        omi_port_transform(&src, &tgt, 0xF6, &r2);
        CHECK(r2.authority.connects  == 0,
              "F6 transform: connects = 0");
        CHECK(r2.authority.transmits == 0,
              "F6 transform: transmits = 0");
        CHECK(r2.authority.mounts    == 0,
              "F6 transform: mounts = 0");
    }

    /* 6. NULL-safe queries (proven in notation test, repeated for completeness) */
    CHECK(omi_port_is_authoritative(NULL) == 0,
          "is_authoritative(NULL) = 0");
    CHECK(omi_port_has_side_effects(NULL) == 0,
          "has_side_effects(NULL) = 0");

    printf("\n");
    if (test_failures > 0)
        printf("RESULT: %d test(s) FAILED\n", test_failures);
    else
        printf("RESULT: all tests PASSED\n");

    return test_failures > 0 ? 1 : 0;
}
