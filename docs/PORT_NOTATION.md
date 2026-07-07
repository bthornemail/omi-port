# OMI-Port Notation

## Compact Route Candidate

```
omi---imo
```

Four-scope OMI-IMO route candidate using canonical FS/GS/RS/US topology.

## Expanded Printable Route Surface

```
o---o/---/?---?@---@
```

### Chirality Markers

| Marker | Meaning |
|--------|---------|
| `o` (lowercase) | Lower chirality (deviation) |
| `O` (uppercase) | Upper chirality (norm) |

The 0x20 bit in ASCII distinguishes chirality:

| Char | 0x20 bit | Chirality |
|------|----------|-----------|
| `o` | 1 | Lower / deviation |
| `O` | 0 | Upper / norm |

### Structural Delimiters

| Delimiter | Role |
|-----------|------|
| `---` | Scope connector |
| `/` | Plane separator (FS/GS -> RS/US) |
| `@` | Route boundary marker |

## Omicron Helpers

Three C functions provide chirality operations:

- `omi_port_is_omicron_ascii(byte)` — returns 1 if byte is 'o' or 'O'
- `omi_port_chirality_bit(byte)` — returns 0x20 bit (0 uppercase, 1 lowercase)
- `omi_port_flip_case_bit(byte)` — XOR with 0x20 to flip case
