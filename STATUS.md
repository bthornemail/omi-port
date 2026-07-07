# OMI-Port Status

## v0 — Dormant Port Notation Transform

Status: **Complete**

### What Exists

- `include/omi_port.h` — self-contained C ABI header
- `src/omi_port.c` — C99 implementation (zero I/O, zero authority)
- `tests/test_scope.c` — 8 checks for URI-CIDR scope parser
- `tests/test_transform.c` — 15+ checks for PortTensor_G transform
- `tests/test_notation.c` — 10+ checks for chirality + init
- `canon/OMI/Port.hs` — normative Haskell EDSL reference
- `lisp/port-declaration.omi` — dormant declaration examples
- `text/PORT_TEXT.md` — text notation reference
- `docs/` — 7 docs covering contract, ABI, scope, transform, notation, authority, test matrix
- `Makefile` — `make`, `make test`, `make clean`, `make hs-check`

### Build Status

All three test binaries build warning-free and pass.

### Boundary

- No omi-lisp import
- No omi-protocol import
- No I/O in library
- All authority flags default to 0
