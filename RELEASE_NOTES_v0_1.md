# Release Notes — omi-port v0.1

## Milestone

`v0.1-gauge-vector-candidate-abi`

## Summary

First documented release of `omi-port`, a standalone C99/Haskell repository
for dormant OMI-IMO port notation and source-target route candidate transforms.

## What Exists

### C ABI (`include/omi_port.h`, `src/omi_port.c`)

| Component | Description |
|-----------|-------------|
| `OMI_PortScope` | URI-CIDR scope grammar: `<uri>#/<prefix>` |
| `OMI_PortRoute` | Canonical FS/GS/RS/US route candidate |
| `OMI_PortAuthority` | Dormant authority flags (all default 0) |
| `omi_port_scope_from_string` | Parse URI-CIDR text into scope |
| `omi_port_transform` | PortTensor_G(source, target, gauge) → route |
| `omi_port_is_f_gauge` | Validate gauge in F0..FF |
| `omi_port_is_authoritative` | v0 stub: always returns 0 |
| `omi_port_has_side_effects` | v0 stub: always returns 0 |
| Omicron chirality helpers | `is_omicron_ascii`, `chirality_bit`, `flip_case_bit` |

### Normative Haskell Reference (`canon/OMI/Port.hs`)

Pure Haskell EDSL matching C transform semantics. Compiles with `make hs-check`.

### Tests

| Binary | Checks | Coverage |
|--------|--------|----------|
| `test_scope` | 17+ | URI-CIDR parser, scope≠gauge |
| `test_transform` | 22+ | Core PortTensor_G, gauges, authority |
| `test_notation` | 49+ | Omicron chirality, LL/MM/NN absence, init |
| `test_authority_negative` | 17+ | Flags = 1 → queries still 0 |
| `test_gauge_vectors` | 138+ | 8 canonical F* vectors, determinism |

**Total: 5 binaries, 243+ assertions, 0 failures, 0 warnings**

## Key Doctrines

### Boundary

- No I/O in library code
- No sibling repo imports (omi-lisp, omi-isa, omi-canvas, omi-tetragrammatron, omi-protocol)
- All authority flags default to 0
- `is_authoritative` returns 0 even after flag mutation
- `has_side_effects` returns 0 even after flag mutation

### Grammar

| Concept | Role |
|---------|------|
| URI-CIDR | Scope grammar: `<uri>#/<prefix>` |
| F* gauge | Transform operator dialect: F0..FF |
| FS/GS/RS/US | Canonical four-scope output topology |
| `omi---imo` | Compact route candidate |
| `o---o/---/?---?@---@` | Expanded printable route surface |
| LL/MM/NN | Deprecated historical 3-slot mnemonic only |

### Handoff

```
omi-lisp declares candidates
omi-port derives route candidates
validation/receipt/acceptance lives elsewhere
no code coupling between repos
```

## Files

```
omi-port/
├── VERSION.md              v0.1-gauge-vector-candidate-abi
├── RELEASE_NOTES_v0_1.md   This file
├── AGENTS.md               Agent boundary contract
├── MANIFEST.md             File manifest
├── STATUS.md               Current status
├── Makefile                C build + Haskell check
├── .gitignore              Build artifacts
├── include/
│   └── omi_port.h          C ABI header (self-contained)
├── src/
│   └── omi_port.c          C99 implementation (no I/O)
├── tests/
│   ├── test_harness.h      Shared CHECK macros
│   ├── test_scope.c        URI-CIDR scope parser
│   ├── test_transform.c    PortTensor_G core
│   ├── test_notation.c     Chirality, LL/MM/NN, init
│   ├── test_authority_negative.c  Negative authority proof
│   ├── test_gauge_vectors.c       Gauge vector determinism
│   └── golden/             5 fixture files
├── canon/OMI/
│   └── Port.hs             Normative Haskell reference
├── lisp/
│   └── port-declaration.omi  Dormant declaration examples
├── text/
│   └── PORT_TEXT.md        Text notation reference
└── docs/
    ├── ARCHITECTURE.md     System architecture
    ├── BOUNDARY_CHECKLIST.md  Boundary verification
    ├── GAUGE_VECTOR_POLICY.md  Gauge semantics
    ├── OMI_LISP_HANDOFF.md    Shape-only handoff
    ├── PORT_ABI.md         C ABI specification
    ├── PORT_AUTHORITY.md   Authority flags
    ├── PORT_CONTRACT.md    Interface contract
    ├── PORT_NOTATION.md    Route notation
    ├── PORT_SCOPE.md       URI-CIDR scope grammar
    ├── PORT_TEST_MATRIX.md Test coverage matrix
    └── PORT_TRANSFORM.md   Transform algorithm
```
