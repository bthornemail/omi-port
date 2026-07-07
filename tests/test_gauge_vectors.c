/*
 * OMI Layer: test
 * Purpose: Verify PortTensor_G transform determinism and authority
 *          across the eight canonical gauge vectors (F0..FF family).
 * Authority: Non-authoritative test.
 */

#include <stdio.h>
#include <string.h>
#include "omi_port.h"
#include "test_harness.h"

typedef struct {
    const char* label;
    const char* source_str;
    const char* target_str;
    uint8_t     gauge;
} GaugeVector;

static const GaugeVector vectors[] = {
    {
        "FF default closure",
        "file:///repo/alpha#/32",
        "file:///repo/beta#/32",
        0xFF
    },
    {
        "F6 XOR-like difference",
        "lora://915/a#/8",
        "lora://915/b#/8",
        0xF6
    },
    {
        "F8 AND-like intersection",
        "https://api.example.com/v1#/64",
        "https://api.example.com/v2#/64",
        0xF8
    },
    {
        "FE OR-like union",
        "file:///tmp/src#/16",
        "file:///tmp/dst#/24",
        0xFE
    },
    {
        "FB source->target implication",
        "lora://915/x#/64",
        "lora://915/y#/64",
        0xFB
    },
    {
        "FD target->source converse",
        "https://a.com/x#/48",
        "https://b.com/y#/48",
        0xFD
    },
    {
        "F0 contradiction lower bound",
        "file:///null#/0",
        "file:///null#/0",
        0xF0
    },
    {
        "F9 equivalence / XNOR",
        "lora://915/p#/32",
        "lora://915/q#/32",
        0xF9
    }
};

#define NUM_VECTORS (sizeof(vectors) / sizeof(vectors[0]))

int main(void)
{
    OMI_PortScope src, tgt;
    OMI_PortRoute r1, r2;
    OMI_PortResult res;
    unsigned int i;
    int all_gauges_valid = 1;

    printf("=== test_gauge_vectors ===\n\n");

    /* 1. Every gauge is in F0..FF */
    for (i = 0; i < NUM_VECTORS; i++) {
        if (!omi_port_is_f_gauge(vectors[i].gauge)) {
            printf("  FAIL: gauge %s (0x%02X) is not F0..FF\n",
                   vectors[i].label, vectors[i].gauge);
            test_failures++;
            all_gauges_valid = 0;
        }
    }
    if (all_gauges_valid)
        printf("  PASS: all %u gauges in F0..FF\n", (unsigned)NUM_VECTORS);

    /* 2. Every vector: parse scopes, transform, verify */
    for (i = 0; i < NUM_VECTORS; i++) {
        char prefix[128];

        snprintf(prefix, sizeof(prefix), "[%s] ", vectors[i].label);

        /* Parse source scope */
        omi_port_scope_init(&src);
        res = omi_port_scope_from_string(vectors[i].source_str, &src);
        {
            char msg[160];
            snprintf(msg, sizeof(msg), "%ssource scope parses", prefix);
            CHECK_RESULT(res, OMI_PORT_OK, msg);
        }

        /* Parse target scope */
        omi_port_scope_init(&tgt);
        res = omi_port_scope_from_string(vectors[i].target_str, &tgt);
        {
            char msg[160];
            snprintf(msg, sizeof(msg), "%starget scope parses", prefix);
            CHECK_RESULT(res, OMI_PORT_OK, msg);
        }

        /* Transform */
        omi_port_route_init(&r1);
        res = omi_port_transform(&src, &tgt, vectors[i].gauge, &r1);
        {
            char msg[160];
            snprintf(msg, sizeof(msg), "%stransform succeeds", prefix);
            CHECK_RESULT(res, OMI_PORT_OK, msg);
        }

        /* Gauge matches */
        {
            char msg[160];
            snprintf(msg, sizeof(msg), "%sroute.gauge == 0x%02X",
                     prefix, vectors[i].gauge);
            CHECK(r1.gauge == vectors[i].gauge, msg);
        }

        /* Authority flags = 0 */
        {
            char msg[160];
            snprintf(msg, sizeof(msg), "%saccepted == 0", prefix);
            CHECK(r1.authority.accepted == 0, msg);
        }
        {
            char msg[160];
            snprintf(msg, sizeof(msg), "%svalidated == 0", prefix);
            CHECK(r1.authority.validated == 0, msg);
        }
        {
            char msg[160];
            snprintf(msg, sizeof(msg), "%sreceipted == 0", prefix);
            CHECK(r1.authority.receipted == 0, msg);
        }

        /* Side-effect flags = 0 */
        {
            char msg[160];
            snprintf(msg, sizeof(msg), "%sconnects == 0", prefix);
            CHECK(r1.authority.connects == 0, msg);
        }
        {
            char msg[160];
            snprintf(msg, sizeof(msg), "%stransmits == 0", prefix);
            CHECK(r1.authority.transmits == 0, msg);
        }
        {
            char msg[160];
            snprintf(msg, sizeof(msg), "%smounts == 0", prefix);
            CHECK(r1.authority.mounts == 0, msg);
        }

        /* Determinism: second transform with identical inputs */
        omi_port_transform(&src, &tgt, vectors[i].gauge, &r2);
        {
            char msg[160];
            snprintf(msg, sizeof(msg), "%sdeterministic: fs matches", prefix);
            CHECK(r1.fs == r2.fs, msg);
        }
        {
            char msg[160];
            snprintf(msg, sizeof(msg), "%sdeterministic: gs matches", prefix);
            CHECK(r1.gs == r2.gs, msg);
        }
        {
            char msg[160];
            snprintf(msg, sizeof(msg), "%sdeterministic: rs matches", prefix);
            CHECK(r1.rs == r2.rs, msg);
        }
        {
            char msg[160];
            snprintf(msg, sizeof(msg), "%sdeterministic: us matches", prefix);
            CHECK(r1.us == r2.us, msg);
        }
        {
            char msg[160];
            snprintf(msg, sizeof(msg), "%sdeterministic: reg matches", prefix);
            CHECK(r1.reg == r2.reg, msg);
        }
    }

    /* 3. Authority queries return 0 for all vectors */
    {
        OMI_PortRoute rt;
        for (i = 0; i < NUM_VECTORS; i++) {
            omi_port_scope_from_string(vectors[i].source_str, &src);
            omi_port_scope_from_string(vectors[i].target_str, &tgt);
            omi_port_transform(&src, &tgt, vectors[i].gauge, &rt);

            if (!omi_port_is_authoritative(&rt.authority)) {
                char msg[160];
                snprintf(msg, sizeof(msg), "[%s] is_authoritative == 0",
                         vectors[i].label);
                printf("  PASS: %s\n", msg);
            } else {
                char msg[160];
                snprintf(msg, sizeof(msg), "[%s] is_authoritative == 0",
                         vectors[i].label);
                printf("  FAIL: %s\n", msg);
                test_failures++;
            }

            if (!omi_port_has_side_effects(&rt.authority)) {
                char msg[160];
                snprintf(msg, sizeof(msg), "[%s] has_side_effects == 0",
                         vectors[i].label);
                printf("  PASS: %s\n", msg);
            } else {
                char msg[160];
                snprintf(msg, sizeof(msg), "[%s] has_side_effects == 0",
                         vectors[i].label);
                printf("  FAIL: %s\n", msg);
                test_failures++;
            }
        }
    }

    printf("\n");
    if (test_failures > 0)
        printf("RESULT: %d test(s) FAILED\n", test_failures);
    else
        printf("RESULT: all tests PASSED\n");

    return test_failures > 0 ? 1 : 0;
}
