# OMI-Port Status

## v0.1-gauge-vector-candidate-abi

Status: **frozen / documented candidate ABI**

### What Exists

- `include/omi_port.h` — self-contained C ABI header
- `src/omi_port.c` — C99 implementation (zero I/O, zero authority)
- `tests/test_scope.c` — 12+ checks for URI-CIDR scope parser
- `tests/test_transform.c` — 15+ checks for PortTensor_G transform
- `tests/test_notation.c` — 30+ checks for chirality + init + LL/MM/NN absence
- `tests/test_authority_negative.c` — 17+ checks proving v0 queries return 0 even with flags = 1
- `tests/test_gauge_vectors.c` — 50+ checks across 8 canonical vectors
- `tests/test_harness.h` — shared CHECK macros
- `tests/golden/` — 5 golden fixture files
- `canon/OMI/Port.hs` — normative Haskell EDSL reference
- `lisp/port-declaration.omi` — dormant declaration examples
- `text/PORT_TEXT.md` — text notation reference
- `docs/` — 11 docs covering architecture, boundary checklist, gauge policy, handoff, contract, ABI, scope, transform, notation, authority, test matrix
- `VERSION.md` — v0.1-gauge-vector-candidate-abi
- `RELEASE_NOTES_v0_1.md` — release summary
- `Makefile` — `make`, `make test`, `make clean`, `make hs-check`

### Build Status

All five test binaries build warning-free and pass.

### Boundary

- No omi-lisp import
- No omi-protocol import
- No I/O in library
- All authority flags default to 0

## Release Gate

v0.1 is frozen. Before v0.2 work begins, `docs/RELEASE_GATE.md` must pass.
