/*
 * OMI Layer: test
 * Purpose: Verify omicron chirality helpers and notation primitives.
 * Authority: Non-authoritative test.
 */

#include <stdio.h>
#include <string.h>
#include "omi_port.h"
#include "test_harness.h"

int main(void)
{
    printf("=== test_notation ===\n\n");

    /* 1. 'o' and 'O' recognized as omicron */
    CHECK(omi_port_is_omicron_ascii('o') == 1, "'o' recognized as omicron");
    CHECK(omi_port_is_omicron_ascii('O') == 1, "'O' recognized as omicron");
    CHECK(omi_port_is_omicron_ascii('x') == 0, "'x' not omicron");
    CHECK(omi_port_is_omicron_ascii('0') == 0, "'0' not omicron");

    /* 2. chirality bit: lowercase = 1, uppercase = 0 */
    CHECK(omi_port_chirality_bit('o') == 1, "'o' chirality bit = 1 (lowercase)");
    CHECK(omi_port_chirality_bit('O') == 0, "'O' chirality bit = 0 (uppercase)");

    /* 3. bit 0x20 relationship */
    CHECK(('o' & 0x20) == 0x20, "'o' & 0x20 == 0x20");
    CHECK(('O' & 0x20) == 0x00, "'O' & 0x20 == 0x00");

    /* 4. XOR flip */
    CHECK(('o' ^ 0x20) == 'O', "'o' ^ 0x20 == 'O'");
    CHECK(('O' ^ 0x20) == 'o', "'O' ^ 0x20 == 'o'");

    /* 5. flip_case_bit */
    CHECK(omi_port_flip_case_bit('o') == 'O', "flip_case_bit('o') -> 'O'");
    CHECK(omi_port_flip_case_bit('O') == 'o', "flip_case_bit('O') -> 'o'");
    CHECK(omi_port_flip_case_bit('x') == 'x', "flip_case_bit('x') -> 'x' (unchanged)");

    /* 6. route_init zeros everything */
    {
        OMI_PortRoute r;
        omi_port_route_init(&r);
        CHECK(r.fs == 0 && r.gs == 0 && r.rs == 0 && r.us == 0,
              "route_init zeros FS/GS/RS/US");
        CHECK(r.fs_i == 0 && r.gs_i == 0 && r.rs_i == 0 && r.us_i == 0,
              "route_init zeros FS_i/GS_i/RS_i/US_i");
        CHECK(r.reg == 0 && r.stack == 0 && r.car == 0 && r.cdr == 0,
              "route_init zeros reg/stack/car/cdr");
        CHECK(r.authority.accepted == 0 &&
              r.authority.validated == 0 &&
              r.authority.receipted == 0 &&
              r.authority.connects == 0 &&
              r.authority.transmits == 0 &&
              r.authority.mounts == 0,
              "route_init zeros all authority flags");
    }

    /* 7. NULL-safe authority queries */
    CHECK(omi_port_is_authoritative(NULL) == 0,
          "is_authoritative(NULL) returns 0");
    CHECK(omi_port_has_side_effects(NULL) == 0,
          "has_side_effects(NULL) returns 0");

    printf("\n");
    if (test_failures > 0)
        printf("RESULT: %d test(s) FAILED\n", test_failures);
    else
        printf("RESULT: all tests PASSED\n");

    return test_failures > 0 ? 1 : 0;
}
