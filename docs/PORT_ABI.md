# OMI-Port ABI

## C99 EABI Surface

The public API is defined in `include/omi_port.h` and implemented in
`src/omi_port.c`.

### Objects

| Type | Description |
|------|-------------|
| `OMI_PortScope` | URI-CIDR scope: `<uri>#/<prefix>` |
| `OMI_PortRoute` | Canonical FS/GS/RS/US route candidate |
| `OMI_PortAuthority` | Dormant authority flags (all default 0) |
| `OMI_PortResult` | Error/success result code |

### Required Functions

| Function | Purpose |
|----------|---------|
| `omi_port_scope_init` | Zero a scope |
| `omi_port_route_init` | Zero a route (all fields + authority = 0) |
| `omi_port_is_f_gauge` | Check gauge in F0..FF |
| `omi_port_scope_from_string` | Parse URI-CIDR text into scope |
| `omi_port_transform` | Core PortTensor_G transform |
| `omi_port_is_authoritative` | v0 stub: always returns 0 (authority conferred externally) |
| `omi_port_has_side_effects` | v0 stub: always returns 0 (no I/O in dormant layer) |
| `omi_port_is_omicron_ascii` | Check o/O |
| `omi_port_chirality_bit` | 0x20 bit value |
| `omi_port_flip_case_bit` | XOR 0x20 |

### Authority Stubs (v0)

Both `omi_port_is_authoritative()` and `omi_port_has_side_effects()`
always return 0 regardless of the authority flag values. Authority is
conferred externally by the validation/receipt/acceptance pipeline.
These stubs will be wired when the downstream layer connects authority
queries.

### Deprecated Mnemonics

The canonical output topology uses FS/GS/RS/US (four-scope) ordering.
LL, MM, and NN are deprecated historical 3-slot transform mnemonics
only. No public ABI symbol contains the substrings `LL`, `MM`, or `NN`.

### Portability

Strict C99, no VLAs, no thread-local storage, no atomics, no I/O.
