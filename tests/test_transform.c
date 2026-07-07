/*
 * OMI Layer: test
 * Purpose: Verify omi_port_transform — PortTensor_G.
 * Authority: Non-authoritative test.
 */

#include <stdio.h>
#include <string.h>
#include "omi_port.h"
#include "test_harness.h"

int main(void)
{
    OMI_PortScope src, tgt;
    OMI_PortRoute r1, r2, r3;
    OMI_PortResult res;

    printf("=== test_transform ===\n\n");

    omi_port_scope_from_string("file:///a#/8",  &src);
    omi_port_scope_from_string("file:///b#/16", &tgt);

    /* 1. FF gauge succeeds */
    res = omi_port_transform(&src, &tgt, 0xFF, &r1);
    CHECK_RESULT(res, OMI_PORT_OK, "FF transform succeeds");

    /* 2. F6 gauge succeeds */
    res = omi_port_transform(&src, &tgt, 0xF6, &r2);
    CHECK_RESULT(res, OMI_PORT_OK, "F6 transform succeeds");

    /* 3. EF gauge fails (not F0..FF) */
    res = omi_port_transform(&src, &tgt, 0xEF, &r3);
    CHECK_RESULT(res, OMI_PORT_ERROR_INVALID_GAUGE, "EF transform fails");

    /* 4. same source/target/gauge gives same route */
    omi_port_transform(&src, &tgt, 0xFF, &r2);
    CHECK(r1.fs == r2.fs, "same source/target/gauge: fs matches");
    CHECK(r1.gs == r2.gs, "same source/target/gauge: gs matches");
    CHECK(r1.rs == r2.rs, "same source/target/gauge: rs matches");
    CHECK(r1.us == r2.us, "same source/target/gauge: us matches");
    CHECK(r1.reg == r2.reg, "same source/target/gauge: reg matches");

    /* 5. different source changes route */
    {
        OMI_PortScope src2;
        omi_port_scope_from_string("file:///c#/8", &src2);
        omi_port_transform(&src2, &tgt, 0xFF, &r3);
        CHECK(r1.fs != r3.fs || r1.gs != r3.gs ||
              r1.rs != r3.rs || r1.us != r3.us,
              "different source changes route");
    }

    /* 6. all authority flags default to 0 */
    {
        OMI_PortRoute r;
        omi_port_transform(&src, &tgt, 0xFF, &r);
        CHECK(r.authority.accepted  == 0, "accepted = 0");
        CHECK(r.authority.validated == 0, "validated = 0");
        CHECK(r.authority.receipted == 0, "receipted = 0");
        CHECK(r.authority.connects  == 0, "connects = 0");
        CHECK(r.authority.transmits == 0, "transmits = 0");
        CHECK(r.authority.mounts    == 0, "mounts = 0");
    }

    /* 7. authoritative query returns 0 */
    {
        OMI_PortRoute r;
        omi_port_transform(&src, &tgt, 0xFF, &r);
        CHECK(omi_port_is_authoritative(&r.authority) == 0,
              "omi_port_is_authoritative returns 0");
        CHECK(omi_port_has_side_effects(&r.authority) == 0,
              "omi_port_has_side_effects returns 0");
    }

    /* 8. null input returns error */
    res = omi_port_transform(NULL, &tgt, 0xFF, &r1);
    CHECK_RESULT(res, OMI_PORT_ERROR_NULL_INPUT, "null source fails");

    res = omi_port_transform(&src, NULL, 0xFF, &r1);
    CHECK_RESULT(res, OMI_PORT_ERROR_NULL_INPUT, "null target fails");

    /* 9. gauge boundary checks */
    res = omi_port_transform(&src, &tgt, 0xF0, &r1);
    CHECK_RESULT(res, OMI_PORT_OK, "F0 gauge succeeds (lower bound)");

    res = omi_port_transform(&src, &tgt, 0x00, &r1);
    CHECK_RESULT(res, OMI_PORT_ERROR_INVALID_GAUGE, "00 gauge fails");

    res = omi_port_transform(&src, &tgt, 0xFE, &r1);
    CHECK_RESULT(res, OMI_PORT_OK, "FE gauge succeeds");

    printf("\n");
    if (test_failures > 0)
        printf("RESULT: %d test(s) FAILED\n", test_failures);
    else
        printf("RESULT: all tests PASSED\n");

    return test_failures > 0 ? 1 : 0;
}
