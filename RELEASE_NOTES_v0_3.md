# Release Notes — omi-port v0.3

## Milestone

`v0.3-omi-lisp-port-fixtures`

## Summary

This release adds read-only OMI-Lisp-shaped port binding fixture
declarations to omi-port. The fixtures are proven by test but do not
create a code dependency on omi-lisp. The release also includes the
golden route freeze (v0.2) as a prerequisite milestone.

## What Exists (v0.3 delta)

### Fixture Handoff

| File | Description |
|------|-------------|
| `tests/golden/port_forms.omi` | 8 dormant OMI-Lisp port binding fixtures (canonical gauge vectors) |
| `tests/test_port_forms.c` | Verifies each fixture: source, target, gauge, dormant state, accepted=0, validated=0, receipted=0 |

### Versioning

| File | Value |
|------|-------|
| `VERSION.md` | v0.3-omi-lisp-port-fixtures |
| `docs/TRANSFORM_VERSIONING.md` | transform_version=0.1 (unchanged) |

## Cumulative Tests

| Binary | Checks | Purpose |
|--------|--------|---------|
| `test_scope` | 10+ | URI-CIDR scope parser, scope≠gauge |
| `test_transform` | 22+ | Core PortTensor_G, gauges, authority |
| `test_notation` | 49+ | Omicron chirality, LL/MM/NN absence, init |
| `test_authority_negative` | 17+ | Flags = 1 → queries still 0 |
| `test_gauge_vectors` | 138+ | 8 canonical F* vectors, determinism |
| `test_route_expected` | 184+ | Golden expected route output freeze |
| `test_port_forms` | 56+ | OMI-Lisp port fixture verification |

**Total: 7 binaries, 476+ assertions, 0 failures, 0 warnings**

## Release Gate

`docs/RELEASE_GATE.md` must pass before any v0.4 work. The gate
protects all frozen milestones (v0.1 ABI, v0.2 golden route, v0.3
fixtures) from accidental scope expansion or behavior drift.

## Key Doctrines

### Boundary

- No I/O in library code
- No sibling repo imports (omi-lisp, omi-isa, omi-canvas, omi-tetragrammatron, omi-protocol)
- All authority flags default to 0
- `is_authoritative` returns 0 even after flag mutation
- `has_side_effects` returns 0 even after flag mutation

### Fixture Handoff

- omi-lisp shape may declare
- omi-port may derive
- golden outputs may freeze behavior
- fixtures may demonstrate handoff

None of these validate, receipt, accept, or connect.

## Files

```
omi-port/
├── VERSION.md                  v0.3-omi-lisp-port-fixtures
├── RELEASE_NOTES_v0_1.md       v0.1 release notes
├── RELEASE_NOTES_v0_3.md       This file
├── AGENTS.md                   Agent boundary contract
├── MANIFEST.md                 File manifest
├── STATUS.md                   Current status
├── Makefile                    C build + Haskell check
├── .gitignore                  Build artifacts
├── include/
│   └── omi_port.h              C ABI header (self-contained)
├── src/
│   └── omi_port.c              C99 implementation (no I/O)
├── tests/
│   ├── test_harness.h          Shared CHECK macros
│   ├── test_scope.c            URI-CIDR scope parser
│   ├── test_transform.c        PortTensor_G core
│   ├── test_notation.c         Chirality, LL/MM/NN, init
│   ├── test_authority_negative.c  Negative authority proof
│   ├── test_gauge_vectors.c       Gauge vector determinism
│   ├── test_route_expected.c       Golden route freeze
│   ├── test_port_forms.c          OMI-Lisp fixture handoff
│   └── golden/
│       ├── route_expected.txt     Frozen expected route outputs
│       └── port_forms.omi         Dormant OMI-Lisp fixtures
├── canon/OMI/
│   └── Port.hs                Normative Haskell reference
├── lisp/
│   └── port-declaration.omi   Dormant declaration examples
├── text/
│   └── PORT_TEXT.md           Text notation reference
└── docs/
    ├── ARCHITECTURE.md
    ├── BOUNDARY_CHECKLIST.md
    ├── GAUGE_VECTOR_POLICY.md
    ├── GOLDEN_ROUTE_POLICY.md
    ├── TRANSFORM_VERSIONING.md
    ├── OMI_LISP_HANDOFF.md
    ├── PORT_ABI.md
    ├── PORT_AUTHORITY.md
    ├── PORT_CONTRACT.md
    ├── PORT_NOTATION.md
    ├── PORT_SCOPE.md
    ├── PORT_TEST_MATRIX.md
    └── PORT_TRANSFORM.md
```
