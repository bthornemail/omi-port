# OMI-Port Test Matrix

## Test Binaries

| Binary | File | Checks | Purpose |
|--------|------|--------|---------|
| `test_scope` | `tests/test_scope.c` | 8+ | URI-CIDR scope parser |
| `test_transform` | `tests/test_transform.c` | 15+ | PortTensor_G transform |
| `test_notation` | `tests/test_notation.c` | 10+ | Omicron chirality, init |

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

### Notation (test_notation.c)

- [x] 'o' and 'O' recognized as omicron
- [x] 'x' and '0' not omicron
- [x] Chirality bit for lowercase = 1
- [x] Chirality bit for uppercase = 0
- [x] 0x20 bit relationships
- [x] XOR flip o<->O
- [x] flip_case_bit round-trip
- [x] route_init zeros all fields
- [x] NULL-safe authority queries

## Integration Gates

- [ ] All C builds warning-free with -Wall -Wextra
- [ ] No I/O in library code
- [ ] No omi-lisp or omi-protocol import
- [ ] All authority flags default to 0
