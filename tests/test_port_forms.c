/*
 * OMI Layer: test
 * Purpose: Verify OMI-Lisp port binding fixture declarations contain
 *          the expected source, target, gauge, and dormant authority fields.
 * Authority: Non-authoritative test. No OMI-Lisp import.
 */

#include <stdio.h>
#include <string.h>
#include "test_harness.h"

#define MAX_LINE 512

int main(void)
{
    FILE* f;
    char line[MAX_LINE];
    int in_form = 0;
    int form_count = 0;
    int has_source, has_target, has_gauge, has_dormant;
    int accepted_ok, validated_ok, receipted_ok;
    char msg[256];

    printf("=== test_port_forms ===\n\n");

    f = fopen("tests/golden/port_forms.omi", "r");
    if (!f) {
        printf("  FAIL: could not open tests/golden/port_forms.omi\n");
        test_failures++;
        goto done;
    }

    has_source = has_target = has_gauge = has_dormant = 0;
    accepted_ok = validated_ok = receipted_ok = 0;

    while (fgets(line, sizeof(line), f)) {
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\n') line[len-1] = '\0';

        if (strstr(line, "(port-binding")) {
            in_form = 1;
            has_source = has_target = has_gauge = has_dormant = 0;
            accepted_ok = validated_ok = receipted_ok = 0;
        }

        if (in_form) {
            if (strstr(line, "(source")) has_source = 1;
            if (strstr(line, "(target")) has_target = 1;
            if (strstr(line, "(gauge")) has_gauge = 1;
            if (strstr(line, "(state dormant")) has_dormant = 1;
            if (strstr(line, "(accepted") && strstr(line, "0")) accepted_ok = 1;
            if (strstr(line, "(validated") && strstr(line, "0")) validated_ok = 1;
            if (strstr(line, "(receipted") && strstr(line, "0")) receipted_ok = 1;
        }

        if (in_form && strstr(line, "))")) {
            form_count++;

            if (!has_source) {
                snprintf(msg, sizeof(msg), "form %d: missing source", form_count);
                printf("  FAIL: %s\n", msg);
                test_failures++;
            }
            if (!has_target) {
                snprintf(msg, sizeof(msg), "form %d: missing target", form_count);
                printf("  FAIL: %s\n", msg);
                test_failures++;
            }
            if (!has_gauge) {
                snprintf(msg, sizeof(msg), "form %d: missing gauge", form_count);
                printf("  FAIL: %s\n", msg);
                test_failures++;
            }
            if (!has_dormant) {
                snprintf(msg, sizeof(msg), "form %d: missing state dormant", form_count);
                printf("  FAIL: %s\n", msg);
                test_failures++;
            }
            if (!accepted_ok) {
                snprintf(msg, sizeof(msg), "form %d: accepted != 0", form_count);
                printf("  FAIL: %s\n", msg);
                test_failures++;
            }
            if (!validated_ok) {
                snprintf(msg, sizeof(msg), "form %d: validated != 0", form_count);
                printf("  FAIL: %s\n", msg);
                test_failures++;
            }
            if (!receipted_ok) {
                snprintf(msg, sizeof(msg), "form %d: receipted != 0", form_count);
                printf("  FAIL: %s\n", msg);
                test_failures++;
            }

            if (has_source && has_target && has_gauge && has_dormant &&
                accepted_ok && validated_ok && receipted_ok) {
                snprintf(msg, sizeof(msg),
                         "form %d: source, target, gauge, dormant, accepted=0, validated=0, receipted=0",
                         form_count);
                printf("  PASS: %s\n", msg);
            }

            in_form = 0;
        }
    }

    fclose(f);

    printf("\n  forms checked: %d\n", form_count);
    if (form_count == 0) {
        printf("  FAIL: no forms found\n");
        test_failures++;
    } else if (form_count != 8) {
        snprintf(msg, sizeof(msg), "expected 8 forms, got %d", form_count);
        printf("  FAIL: %s\n", msg);
        test_failures++;
    }

done:
    printf("\n");
    if (test_failures > 0)
        printf("RESULT: %d test(s) FAILED\n", test_failures);
    else
        printf("RESULT: all tests PASSED\n");

    return test_failures > 0 ? 1 : 0;
}
