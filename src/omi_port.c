/*
 * OMI Layer: carrier
 * Purpose: OMI-Port C99 implementation — dormant source-target transform.
 * Authority: Non-authoritative declaration surface. Side-effect-free.
 *
 * Implements a dynamic F*-gauged source-target transform that derives
 * canonical FS/GS/RS/US OMI-IMO place-value route candidates.
 *
 * No connect, transmit, mount, validate, receipt, or accept state.
 * No I/O, no networking, no filesystem access.
 */

#include "omi_port.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* ------------------------------------------------------------------ */
/* Internal helpers                                                    */
/* ------------------------------------------------------------------ */

static uint32_t mix_scope_into_acc(const OMI_PortScope* scope, uint32_t acc)
{
    size_t i;
    for (i = 0; i < OMI_PORT_URI_MAX && scope->uri[i] != '\0'; i++) {
        acc = acc * 31 + (unsigned char)scope->uri[i];
    }
    acc = acc * 31 + scope->prefix_len;
    return acc;
}

/* ------------------------------------------------------------------ */
/* Scope lifetime helpers                                              */
/* ------------------------------------------------------------------ */

void omi_port_scope_init(OMI_PortScope* scope)
{
    if (scope) {
        memset(scope->uri, 0, OMI_PORT_URI_MAX);
        scope->prefix_len = 0;
    }
}

void omi_port_route_init(OMI_PortRoute* route)
{
    if (route) {
        route->gauge = 0;
        route->fs = 0; route->gs = 0; route->rs = 0; route->us = 0;
        route->fs_i = 0; route->gs_i = 0; route->rs_i = 0; route->us_i = 0;
        route->reg = 0; route->stack = 0; route->car = 0; route->cdr = 0;
        route->authority.connects   = 0;
        route->authority.transmits  = 0;
        route->authority.mounts     = 0;
        route->authority.accepted   = 0;
        route->authority.validated  = 0;
        route->authority.receipted  = 0;
    }
}

/* ------------------------------------------------------------------ */
/* Gauge validation                                                    */
/* ------------------------------------------------------------------ */

int omi_port_is_f_gauge(uint8_t gauge)
{
    return gauge >= 0xF0;
}

/* ------------------------------------------------------------------ */
/* Scope parser — URI-CIDR: <uri>#/<prefix>                           */
/* ------------------------------------------------------------------ */

OMI_PortResult omi_port_scope_from_string(
    const char* text,
    OMI_PortScope* out)
{
    const char* hash_slash;
    const char* prefix_str;
    char* endptr;
    long val;
    size_t uri_len;

    if (!text || !out) return OMI_PORT_ERROR_NULL_INPUT;

    omi_port_scope_init(out);

    /* Find "#/" separator */
    hash_slash = strstr(text, "#/");
    if (!hash_slash) return OMI_PORT_ERROR_SCOPE_NO_PREFIX;

    uri_len = (size_t)(hash_slash - text);
    if (uri_len == 0 || uri_len >= OMI_PORT_URI_MAX)
        return OMI_PORT_ERROR_SCOPE_TOO_LONG;

    memcpy(out->uri, text, uri_len);
    out->uri[uri_len] = '\0';

    /* Parse prefix length */
    prefix_str = hash_slash + 2;
    if (*prefix_str == '\0') return OMI_PORT_ERROR_SCOPE_BAD_PREFIX;

    val = strtol(prefix_str, &endptr, 10);
    if (*endptr != '\0' || val < 0 || val > 255)
        return OMI_PORT_ERROR_SCOPE_BAD_PREFIX;

    out->prefix_len = (uint8_t)val;
    return OMI_PORT_OK;
}

/* ------------------------------------------------------------------ */
/* Core transform — PortTensor_G                                       */
/* ------------------------------------------------------------------ */

OMI_PortResult omi_port_transform(
    const OMI_PortScope* source,
    const OMI_PortScope* target,
    uint8_t gauge,
    OMI_PortRoute* out)
{
    uint32_t acc;

    if (!source || !target || !out) return OMI_PORT_ERROR_NULL_INPUT;

    if (!omi_port_is_f_gauge(gauge)) return OMI_PORT_ERROR_INVALID_GAUGE;

    omi_port_route_init(out);

    /* Mix source, gauge, target into deterministic route values */
    acc = mix_scope_into_acc(source, 0);
    acc = acc * 31 + gauge;
    acc = mix_scope_into_acc(target, acc);

    out->gauge = gauge;
    out->fs  = (uint16_t)(acc >>  0);
    out->gs  = (uint16_t)(acc >>  8);
    out->rs  = (uint16_t)(acc >> 16);
    out->us  = (uint16_t)(acc >> 24);

    out->fs_i = (uint16_t)(acc >>  4);
    out->gs_i = (uint16_t)(acc >> 12);
    out->rs_i = (uint16_t)(acc >> 20);
    out->us_i = (uint16_t)(acc >> 28);

    out->reg   = acc;
    out->stack = acc ^ 0xDEADBEEF;
    out->car   = acc ^ 0xCAFEBABE;
    out->cdr   = acc ^ 0xBAADF00D;

    /* All authority flags remain 0 (dormant / non-authoritative) */
    return OMI_PORT_OK;
}

/* ------------------------------------------------------------------ */
/* Authority queries                                                   */
/* ------------------------------------------------------------------ */

int omi_port_is_authoritative(const OMI_PortAuthority* authority)
{
    if (!authority) return 0;
    return authority->accepted && authority->validated && authority->receipted;
}

int omi_port_has_side_effects(const OMI_PortAuthority* authority)
{
    if (!authority) return 0;
    return authority->connects || authority->transmits || authority->mounts;
}

/* ------------------------------------------------------------------ */
/* Omicron chirality helpers                                           */
/* ------------------------------------------------------------------ */

int omi_port_is_omicron_ascii(unsigned char byte)
{
    return byte == 'o' || byte == 'O';
}

int omi_port_chirality_bit(unsigned char byte)
{
    /* 0x20 bit is 0 for uppercase, 1 for lowercase in ASCII alpha */
    return (byte & 0x20) ? 1 : 0;
}

unsigned char omi_port_flip_case_bit(unsigned char byte)
{
    if (!omi_port_is_omicron_ascii(byte)) return byte;
    return (unsigned char)(byte ^ 0x20);
}
