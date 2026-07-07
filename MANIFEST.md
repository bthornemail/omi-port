# OMI-Port Manifest

## Purpose

Standalone dormant port-notation and source-target transform repo.
Defines PortTensor_G(source, target) -> OMI_PortRoute using canonical
FS/GS/RS/US topology and F0..FF gauge selection.

## Directory Structure

```
omi-port/
├── include/
│   └── omi_port.h              C ABI header (self-contained)
├── src/
│   └── omi_port.c              C99 implementation (no I/O)
├── tests/
│   ├── test_harness.h          Shared CHECK macro
│   ├── test_scope.c            URI-CIDR scope parser tests
│   ├── test_transform.c        PortTensor_G transform tests
│   ├── test_notation.c         Omicron chirality + init tests
│   ├── test_authority_negative.c  Negative authority proof (flags=1 still 0)
│   ├── test_gauge_vectors.c       Gauge vector determinism + authority proof
│   └── golden/
│       ├── basic_scope.txt        Scope examples
│       ├── basic_transform.txt    Transform records
│       ├── omi_route.txt          OMI-IMO notation examples
│       ├── port_binding.omi       Dormant port binding example
│       └── route_vectors.txt      Eight canonical gauge vectors
├── canon/
│   └── OMI/
│       └── Port.hs             Normative Haskell EDSL reference
├── lisp/
│   └── port-declaration.omi    OMI-Lisp declaration surface
├── text/
│   └── PORT_TEXT.md            Text notation reference
├── docs/
│   ├── GAUGE_VECTOR_POLICY.md  F* gauge vector semantics policy
│   ├── OMI_LISP_HANDOFF.md     Shape-only handoff contract
│   ├── PORT_CONTRACT.md        Interface contract
│   ├── PORT_ABI.md             C ABI specification
│   ├── PORT_SCOPE.md           URI-CIDR scope grammar
│   ├── PORT_TRANSFORM.md       Transform algorithm
│   ├── PORT_NOTATION.md        Route notation
│   ├── PORT_AUTHORITY.md       Authority flags
│   └── PORT_TEST_MATRIX.md     Test coverage matrix
├── dev-docs/                   Development notes
├── AGENTS.md                   Agent boundary contract
├── MANIFEST.md                 This file
├── STATUS.md                   Current status
├── Makefile                    Build system
└── .gitignore                  Build artifacts
```

## Layer Labels

| File | Layer |
|------|-------|
| `include/omi_port.h` | carrier |
| `src/omi_port.c` | carrier |
| `tests/*.c` | test |
| `canon/OMI/Port.hs` | carrier (normative) |
| `lisp/*.omi` | carrier |
| `text/*.md` | carrier |
| `docs/*.md` | carrier |
| `AGENTS.md` | carrier |
| `MANIFEST.md` | carrier |
| `STATUS.md` | carrier |
