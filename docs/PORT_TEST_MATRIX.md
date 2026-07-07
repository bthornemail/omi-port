# OMI-Port Test Matrix

## Test Binaries

| Binary | File | Checks | Purpose |
|--------|------|--------|---------|
| `test_scope` | `tests/test_scope.c` | 10+ | URI-CIDR scope parser, scope!=gauge |
| `test_transform` | `tests/test_transform.c` | 15+ | PortTensor_G transform |
| `test_notation` | `tests/test_notation.c` | 20+ | Omicron chirality, init, LL/MM/NN absence |
| `test_authority_negative` | `tests/test_authority_negative.c` | 17+ | Negative authority proof |
| `test_gauge_vectors` | `tests/test_gauge_vectors.c` | 50+ | Gauge vector determinism + authority |

## Coverage by Area

### Scope Parser (test_scope.c)

- [x] `file:///repo/input.omi#/64` parses
- [x] `lora://915/node/alpha#/16` parses
- [x] `https://example.com/api#/40` parses
- [x] Missing `#/` returns error
- [x] Non-numeric prefix returns error
- [x] URI > 255 bytes returns error
- [x] Null input returns error
- [x] Prefix > 255 returns error
- [x] URI-CIDR is scope grammar: prefix_len is not a gauge
- [x] F* gauge values (240) parse as scope prefix (separate namespace)

### Transform (test_transform.c)

- [x] FF gauge succeeds
- [x] F6 gauge succeeds
- [x] EF gauge fails
- [x] Same source/target/gauge gives same route
- [x] Different source changes route
- [x] All authority flags = 0
- [x] is_authoritative returns 0
- [x] has_side_effects returns 0
- [x] Null source returns error
- [x] Null target returns error
- [x] F0 lower bound succeeds
- [x] 00 gauge fails
- [x] FE gauge succeeds

### Negative Authority (test_authority_negative.c)

- [x] Fresh route: all flags = 0
- [x] Fresh route: queries return 0
- [x] Mutated flags[all=1]: is_authoritative = 0 (v0 stub)
- [x] Mutated flags[all=1]: has_side_effects = 0 (v0 stub)
- [x] Partial mutations also return 0
- [x] Transform does not set connects/transmits/mounts
- [x] NULL-safe queries

### Notation (test_notation.c)

- [x] 'o' and 'O' recognized as omicron
- [x] 'x' and '0' not omicron
- [x] Chirality bit for lowercase = 1
- [x] Chirality bit for uppercase = 0
- [x] 0x20 bit relationships
- [x] XOR flip o<->O
- [x] flip_case_bit round-trip
- [x] route_init zeros all fields
- [x] All 10 public API symbols: no LL/MM/NN substrings
- [x] NULL-safe authority queries

## Integration Gates

- [x] All C builds warning-free with -Wall -Wextra
- [x] No I/O in library code
- [x] No omi-lisp or omi-protocol import
- [x] All authority flags default to 0
- [x] is_authoritative returns 0 even with flags = 1 (v0 stub)
- [x] has_side_effects returns 0 even with flags = 1 (v0 stub)
- [x] Transform never sets connects/transmits/mounts
- [x] URI-CIDR is scope grammar, not gauge grammar
- [x] LL/MM/NN absent from public ABI symbols
- [x] All 8 canonical gauges in F0..FF
- [x] Every vector: source parses, target parses, transform succeeds
- [x] Every vector: route.gauge matches vector gauge
- [x] Every vector: authority flags = 0
- [x] Every vector: side-effect flags = 0
- [x] Every vector: deterministic across two identical transforms
- [x] Every vector: is_authoritative == 0
- [x] Every vector: has_side_effects == 0
