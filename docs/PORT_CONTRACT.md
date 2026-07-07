# OMI-Port Contract

## Purpose

OMI-Port defines a dormant, side-effect-free source-target port-notation
transform. The core operation is:

    PortTensor_G(source, target) -> OMI_PortRoute

It produces canonical FS/GS/RS/US OMI-IMO place-value route candidates
without connecting, validating, receipting, or accepting state.

## Boundary

OMI-Port is a **carrier layer** artifact. It:

- Declares route candidates
- Transforms source-target pairs into route topologies
- Applies dynamic F0..FF gauge selection

It does **not**:

- Connect, send, receive, or mount
- Open files or sockets as part of the library
- Validate, receipt, or accept state
- Use hashes as identity
- Treat URI as authority
- Treat display order as authority
- Restore archive code
- Import sibling repos (omi-lisp, omi-isa, omi-canvas, omi-tetragrammatron, omi-protocol)

## Authority

All authority flags default to 0. No route produced by omi-port is
authoritative. The word "port" refers to notation and transform only,
not network transport.

## Dependencies

- C99 standard library (string.h, stdint.h, ctype.h)
- No external libraries
- No sibling OMI repos
