# OMI-Port Authority

## Principle

OMI-Port produces **dormant route candidates**. No produced route carries
authority. Authority is the responsibility of downstream validation,
receipt, and acceptance layers (not part of omi-port).

## Authority Flags

| Flag | Default | Meaning |
|------|---------|---------|
| `connects` | 0 | Would connect to a transport |
| `transmits` | 0 | Would transmit over a carrier |
| `mounts` | 0 | Would mount a filesystem or device |
| `accepted` | 0 | Has been accepted by a validation layer |
| `validated` | 0 | Has been validated |
| `receipted` | 0 | Has been receipted |

## Queries

- `omi_port_is_authoritative(a)` — returns 1 only if all three of
  accepted, validated, and receipted are non-zero
- `omi_port_has_side_effects(a)` — returns 1 if connects, transmits,
  or mounts is non-zero

Since all flags default to 0, both queries always return 0 for any
route produced by omi-port.

## Non-Negotiable

No route produced by omi-port may ever have non-zero authority flags.
Authority is conferred externally by the validation and acceptance
pipeline.
