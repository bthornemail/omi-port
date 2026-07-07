/*
 * OMI Layer: carrier
 * Purpose: OMI-Port C ABI — dormant source-target port-notation transform.
 * Authority: Non-authoritative declaration surface. Side-effect-free.
 *
 * Defines the PortTensor_G(source, target) -> OMI_PortRoute transform
 * using canonical FS/GS/RS/US topology and F0..FF gauge selection.
 *
 * No connect, transmit, mount, validate, receipt, or accept state.
 * All authority flags default to 0.
 * No omi-lisp, omi-isa, omi-canvas, omi-tetragrammatron, or omi-protocol import.
 */

#ifndef OMI_PORT_H
#define OMI_PORT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/* Constants                                                          */
/* ------------------------------------------------------------------ */

#define OMI_PORT_URI_MAX 256

/* ------------------------------------------------------------------ */
/* Result codes                                                       */
/* ------------------------------------------------------------------ */

typedef enum {
    OMI_PORT_OK                 = 0,
    OMI_PORT_ERROR_NULL_INPUT   = 1,
    OMI_PORT_ERROR_SCOPE_MALFORMED = 2,
    OMI_PORT_ERROR_SCOPE_NO_PREFIX  = 3,
    OMI_PORT_ERROR_SCOPE_BAD_PREFIX = 4,
    OMI_PORT_ERROR_SCOPE_TOO_LONG   = 5,
    OMI_PORT_ERROR_INVALID_GAUGE    = 6,
    OMI_PORT_ERROR_UNSPECIFIED      = 7
} OMI_PortResult;

/* ------------------------------------------------------------------ */
/* Scope — URI-CIDR default grammar                                   */
/* ------------------------------------------------------------------ */

typedef struct {
    char     uri[OMI_PORT_URI_MAX];
    uint8_t  prefix_len;
} OMI_PortScope;

/* ------------------------------------------------------------------ */
/* Authority flags — all default to 0                                  */
/* ------------------------------------------------------------------ */

typedef struct {
    int connects;
    int transmits;
    int mounts;
    int accepted;
    int validated;
    int receipted;
} OMI_PortAuthority;

/* ------------------------------------------------------------------ */
/* Route — canonical FS/GS/RS/US topology output                       */
/* ------------------------------------------------------------------ */

typedef struct {
    uint8_t  gauge;   /* F0..FF */

    uint16_t fs;
    uint16_t gs;
    uint16_t rs;
    uint16_t us;

    uint16_t fs_i;
    uint16_t gs_i;
    uint16_t rs_i;
    uint16_t us_i;

    uint32_t reg;
    uint32_t stack;
    uint32_t car;
    uint32_t cdr;

    OMI_PortAuthority authority;
} OMI_PortRoute;

/* ------------------------------------------------------------------ */
/* Scope lifetime helpers                                              */
/* ------------------------------------------------------------------ */

void omi_port_scope_init(OMI_PortScope* scope);
void omi_port_route_init(OMI_PortRoute* route);

/* ------------------------------------------------------------------ */
/* Gauge validation                                                    */
/* ------------------------------------------------------------------ */

int omi_port_is_f_gauge(uint8_t gauge);

/* ------------------------------------------------------------------ */
/* Scope parser (URI-CIDR)                                             */
/* ------------------------------------------------------------------ */

OMI_PortResult omi_port_scope_from_string(
    const char* text,
    OMI_PortScope* out
);

/* ------------------------------------------------------------------ */
/* Core transform — PortTensor_G(source, target) -> route              */
/* ------------------------------------------------------------------ */

OMI_PortResult omi_port_transform(
    const OMI_PortScope* source,
    const OMI_PortScope* target,
    uint8_t gauge,
    OMI_PortRoute* out
);

/* ------------------------------------------------------------------ */
/* Authority queries                                                   */
/* ------------------------------------------------------------------ */

int omi_port_is_authoritative(const OMI_PortAuthority* authority);
int omi_port_has_side_effects(const OMI_PortAuthority* authority);

/* ------------------------------------------------------------------ */
/* Omicron chirality helpers                                           */
/* ------------------------------------------------------------------ */

int  omi_port_is_omicron_ascii(unsigned char byte);
int  omi_port_chirality_bit(unsigned char byte);
unsigned char omi_port_flip_case_bit(unsigned char byte);

#ifdef __cplusplus
}
#endif

#endif /* OMI_PORT_H */
