# OMI-Lisp / OMI-Port Handoff

## Purpose

This document describes the shape-only handoff between omi-lisp and omi-port.
Neither layer validates, receipts, accepts, connects, sends, receives, or mounts.
The handoff is declaration surface to dormant transform — no authority is conferred.

## Conceptual Flow

```
omi-lisp (declaration surface)
    ↓  may declare a dormant port binding
omi-port (dormant transform)
    ↓  may lower that declaration into a PortRoute candidate
downstream (not part of omi-lisp or omi-port)
    ↓  validation → receipt → acceptance
```

## What Each Layer Provides

| Layer | Output | Authority |
|-------|--------|-----------|
| `omi-lisp` | `OMI_Candidate` tree | Non-authoritative declaration |
| `omi-port` | `OMI_PortRoute` candidate | Non-authoritative transform (all flags 0) |

## What Neither Layer Does

- Neither validates port bindings
- Neither receipts port bindings
- Neither accepts port bindings
- Neither connects, sends, receives, or mounts
- Neither imports the other's code

## Handoff Rule

The handoff is **shape-only**:

- omi-lisp declares a port binding as a candidate atom or pair form
- omi-port transforms source-target pairs into canonical FS/GS/RS/US route topologies
- The two repos are standalone; no shared headers, no linked objects, no runtime coupling

## Non-Negotiable

No code in omi-lisp may call omi-port.

No code in omi-port may call omi-lisp.

No code in either may call omi-protocol.

No code in either may call omi-canvas.

No code in either may call omi-tetragrammatron.

The handoff is a documentation and conceptual interface only.
