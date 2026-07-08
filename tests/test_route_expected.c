/*
 * OMI Layer: test
 * Purpose: Verify PortTensor_G transform against frozen golden expected
 *          route outputs. Catches accidental transform drift.
 * Authority: Non-authoritative test.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "omi_port.h"
#include "test_harness.h"

#define MAX_LINE 512

typedef struct {
    char    name[16];
    char    source_str[256];
    char    target_str[256];
    uint8_t gauge;
    uint16_t fs, gs, rs, us;
    uint16_t fs_i, gs_i, rs_i, us_i;
    uint32_t reg, stack, car, cdr;
} ExpectedRoute;

static int parse_hex16(const char* s, uint16_t* out)
{
    unsigned long v;
    char* end;
    v = strtoul(s, &end, 16);
    if (*end != '\0' || v > 0xFFFF) return -1;
    *out = (uint16_t)v;
    return 0;
}

static int parse_hex32(const char* s, uint32_t* out)
{
    unsigned long v;
    char* end;
    v = strtoul(s, &end, 16);
    if (*end != '\0') return -1;
    *out = (uint32_t)v;
    return 0;
}

static int parse_expected_line(const char* line, ExpectedRoute* e)
{
    char gauge_str[8];
    char fs_str[16], gs_str[16], rs_str[16], us_str[16];
    char fi_str[16], gi_str[16], ri_str[16], ui_str[16];
    char reg_str[16], stk_str[16], car_str[16], cdr_str[16];
    int n;

    n = sscanf(line, "%15[^|]|%255[^|]|%255[^|]|%7[^|]|"
                    "%15[^|]|%15[^|]|%15[^|]|%15[^|]|"
                    "%15[^|]|%15[^|]|%15[^|]|%15[^|]|"
                    "%15[^|]|%15[^|]|%15[^|]|%15[^|]",
               e->name, e->source_str, e->target_str, gauge_str,
               fs_str, gs_str, rs_str, us_str,
               fi_str, gi_str, ri_str, ui_str,
               reg_str, stk_str, car_str, cdr_str);
    if (n != 16) return -1;

    /* Parse gauge */
    if (gauge_str[0] == 'F' || gauge_str[0] == 'f') {
        unsigned long gv = strtoul(gauge_str, NULL, 16);
        if (gv > 0xFF) return -1;
        e->gauge = (uint8_t)gv;
    } else {
        return -1;
    }

    if (parse_hex16(fs_str, &e->fs)   || parse_hex16(gs_str, &e->gs) ||
        parse_hex16(rs_str, &e->rs)   || parse_hex16(us_str, &e->us) ||
        parse_hex16(fi_str, &e->fs_i) || parse_hex16(gi_str, &e->gs_i) ||
        parse_hex16(ri_str, &e->rs_i) || parse_hex16(ui_str, &e->us_i) ||
        parse_hex32(reg_str, &e->reg) || parse_hex32(stk_str, &e->stack) ||
        parse_hex32(car_str, &e->car) || parse_hex32(cdr_str, &e->cdr))
        return -1;

    return 0;
}

int main(void)
{
    FILE* f;
    char line[MAX_LINE];
    int line_num = 0;
    int expected_count = 0;
    int checked = 0;

    printf("=== test_route_expected ===\n\n");

    f = fopen("tests/golden/route_expected.txt", "r");
    if (!f) {
        printf("  FAIL: could not open tests/golden/route_expected.txt\n");
        test_failures++;
        goto done;
    }

    while (fgets(line, sizeof(line), f)) {
        ExpectedRoute exp;
        OMI_PortScope src, tgt;
        OMI_PortRoute r;
        OMI_PortResult res;
        char msg[256];

        line_num++;
        /* strip trailing newline */
        {
            size_t len = strlen(line);
            if (len > 0 && line[len-1] == '\n') line[len-1] = '\0';
        }

        /* skip blank and comment lines */
        if (line[0] == '\0' || line[0] == '#') continue;

        if (parse_expected_line(line, &exp) != 0) {
            snprintf(msg, sizeof(msg), "line %d: parse error", line_num);
            printf("  FAIL: %s\n", msg);
            test_failures++;
            continue;
        }
        expected_count++;

        /* Parse source */
        omi_port_scope_init(&src);
        res = omi_port_scope_from_string(exp.source_str, &src);
        snprintf(msg, sizeof(msg), "[%s] source scope parses", exp.name);
        CHECK_RESULT(res, OMI_PORT_OK, msg);

        /* Parse target */
        omi_port_scope_init(&tgt);
        res = omi_port_scope_from_string(exp.target_str, &tgt);
        snprintf(msg, sizeof(msg), "[%s] target scope parses", exp.name);
        CHECK_RESULT(res, OMI_PORT_OK, msg);

        /* Check gauge */
        if (!omi_port_is_f_gauge(exp.gauge)) {
            snprintf(msg, sizeof(msg), "[%s] gauge is not F0..FF", exp.name);
            printf("  FAIL: %s\n", msg);
            test_failures++;
            continue;
        }

        /* Transform */
        omi_port_route_init(&r);
        res = omi_port_transform(&src, &tgt, exp.gauge, &r);
        snprintf(msg, sizeof(msg), "[%s] transform succeeds", exp.name);
        CHECK_RESULT(res, OMI_PORT_OK, msg);

        /* Compare all route fields */
        snprintf(msg, sizeof(msg), "[%s] fs == 0x%04X", exp.name, exp.fs);
        CHECK(r.fs == exp.fs, msg);
        snprintf(msg, sizeof(msg), "[%s] gs == 0x%04X", exp.name, exp.gs);
        CHECK(r.gs == exp.gs, msg);
        snprintf(msg, sizeof(msg), "[%s] rs == 0x%04X", exp.name, exp.rs);
        CHECK(r.rs == exp.rs, msg);
        snprintf(msg, sizeof(msg), "[%s] us == 0x%04X", exp.name, exp.us);
        CHECK(r.us == exp.us, msg);
        snprintf(msg, sizeof(msg), "[%s] fs_i == 0x%04X", exp.name, exp.fs_i);
        CHECK(r.fs_i == exp.fs_i, msg);
        snprintf(msg, sizeof(msg), "[%s] gs_i == 0x%04X", exp.name, exp.gs_i);
        CHECK(r.gs_i == exp.gs_i, msg);
        snprintf(msg, sizeof(msg), "[%s] rs_i == 0x%04X", exp.name, exp.rs_i);
        CHECK(r.rs_i == exp.rs_i, msg);
        snprintf(msg, sizeof(msg), "[%s] us_i == 0x%04X", exp.name, exp.us_i);
        CHECK(r.us_i == exp.us_i, msg);
        snprintf(msg, sizeof(msg), "[%s] reg == 0x%08X", exp.name, exp.reg);
        CHECK(r.reg == exp.reg, msg);
        snprintf(msg, sizeof(msg), "[%s] stack == 0x%08X", exp.name, exp.stack);
        CHECK(r.stack == exp.stack, msg);
        snprintf(msg, sizeof(msg), "[%s] car == 0x%08X", exp.name, exp.car);
        CHECK(r.car == exp.car, msg);
        snprintf(msg, sizeof(msg), "[%s] cdr == 0x%08X", exp.name, exp.cdr);
        CHECK(r.cdr == exp.cdr, msg);

        /* Authority = 0 */
        CHECK(r.authority.accepted  == 0, "accepted == 0");
        CHECK(r.authority.validated == 0, "validated == 0");
        CHECK(r.authority.receipted == 0, "receipted == 0");
        CHECK(r.authority.connects  == 0, "connects == 0");
        CHECK(r.authority.transmits == 0, "transmits == 0");
        CHECK(r.authority.mounts    == 0, "mounts == 0");
        CHECK(omi_port_is_authoritative(&r.authority) == 0,
              "is_authoritative == 0");
        CHECK(omi_port_has_side_effects(&r.authority) == 0,
              "has_side_effects == 0");

        checked++;
    }

    fclose(f);

    printf("\n  vectors checked: %d\n", checked);

done:
    printf("\n");
    if (test_failures > 0)
        printf("RESULT: %d test(s) FAILED\n", test_failures);
    else
        printf("RESULT: all tests PASSED\n");

    return test_failures > 0 ? 1 : 0;
}
