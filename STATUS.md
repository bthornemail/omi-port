# OMI-Port Status

## v0.3-omi-lisp-port-fixtures

Status: **frozen / documented candidate ABI + golden route + fixture handoff**

### What Exists (cumulative)

- `include/omi_port.h` — self-contained C ABI header
- `src/omi_port.c` — C99 implementation (zero I/O, zero authority)
- `tests/test_scope.c` — 10+ checks for URI-CIDR scope parser
- `tests/test_transform.c` — 22+ checks for PortTensor_G transform
- `tests/test_notation.c` — 49+ checks for chirality + init + LL/MM/NN absence
- `tests/test_authority_negative.c` — 17+ checks proving v0 queries return 0 even with flags = 1
- `tests/test_gauge_vectors.c` — 138+ checks across 8 canonical vectors
- `tests/test_route_expected.c` — golden expected route output freeze (184+ checks)
- `tests/test_port_forms.c` — OMI-Lisp port fixture verification (56+ checks)
- `tests/test_harness.h` — shared CHECK macros
- `tests/golden/` — 7 golden fixture files including `route_expected.txt` and `port_forms.omi`
- `canon/OMI/Port.hs` — normative Haskell EDSL reference
- `lisp/port-declaration.omi` — dormant declaration examples
- `text/PORT_TEXT.md` — text notation reference
- `docs/` — 13 docs covering architecture, boundary checklist, gauge policy, golden route policy, transform versioning, handoff, contract, ABI, scope, transform, notation, authority, test matrix
- `VERSION.md` — v0.3-omi-lisp-port-fixtures
- `RELEASE_NOTES_v0_1.md` / `RELEASE_NOTES_v0_3.md` — release summaries
- `Makefile` — `make`, `make test`, `make clean`, `make hs-check`

### Build Status

All seven test binaries build warning-free and pass.

### Boundary

- No omi-lisp import
- No omi-protocol import
- No I/O in library
- All authority flags default to 0

## Release Gate

v0.3 is frozen. Before v0.4 work begins, `docs/RELEASE_GATE.md` must pass.
