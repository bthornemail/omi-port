# OMI-Port Architecture

## System Context

```
omi-lisp (declaration surface)
    ↓  declares dormant port bindings
omi-port (dormant transform)
    ↓  derives deterministic FS/GS/RS/US route candidates
validation / receipt / acceptance (external, not omi-port)
```

## Layers

### omi-lisp (separate repo)

- Declares port bindings as OMI-Lisp candidate atoms/pairs
- Non-authoritative declaration surface
- No transform logic
- No route derivation

### omi-port (this repo)

- Accepts URI-CIDR source/target scopes and F* gauge
- Produces deterministic `OMI_PortRoute` candidates
- Zero authority (all flags default to 0)
- Zero I/O (no connect, send, receive, mount, filesystem)
- No validation, no receipt, no acceptance

### Downstream (external, not in this repo)

- Validation engine
- Receipt authority
- Acceptance pipeline
- Projection surfaces

These layers are not part of omi-port. They consume route candidates
but do not import omi-port code.

## Architecture Rules

### Coupling

```
omi-lisp  ──(no code coupling)──  omi-port
omi-port  ──(no code coupling)──  omi-lisp
omi-port  ──(no import)─────────  omi-isa, omi-canvas, omi-tetragrammatron, omi-protocol
```

The handoff is documentation and conceptual only. No shared headers,
no linked objects, no runtime calls between repos.

### Data Flow

```
source scope (URI-CIDR)
    ↓
target scope (URI-CIDR)
    ↓
F* gauge (uint8_t, F0..FF)
    ↓
omi_port_transform()
    ↓
OMI_PortRoute (FS/GS/RS/US candidate)
    - gauge
    - fs, gs, rs, us
    - fs_i, gs_i, rs_i, us_i
    - reg, stack, car, cdr
    - authority (all 0)
```

### Authority Boundary

- `omi_port_is_authoritative()` → always 0 (v0 stub)
- `omi_port_has_side_effects()` → always 0 (v0 stub)
- No omi-port function can set authority flags to non-zero
- Authority is conferred externally by the downstream pipeline

### Grammar Boundary

| Grammar | Type | Used By |
|---------|------|---------|
| URI-CIDR | Scope grammar | `OMI_PortScope` |
| F0..FF | Gauge family | `omi_port_is_f_gauge()` |
| FS/GS/RS/US | Output topology | `OMI_PortRoute` |
| OMI-IMO | Route notation | `tests/golden/`, `text/PORT_TEXT.md` |
| LL/MM/NN | Deprecated | Not present in public ABI |
