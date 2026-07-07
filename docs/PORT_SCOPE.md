# OMI-Port Scope Grammar

## Default: URI-CIDR

The default scope grammar is URI-CIDR:

```
<uri>#/<prefix>
```

### Examples

| Text | URI | Prefix |
|------|-----|--------|
| `file:///repo/input.omi#/64` | `file:///repo/input.omi` | 64 |
| `lora://915/node/alpha#/16` | `lora://915/node/alpha` | 16 |
| `https://example.com/api#/40` | `https://example.com/api` | 40 |

### Validation Rules

- Must contain `#/` separator
- URI before `#/` must be non-empty and <= 255 bytes
- Prefix after `#/` must be a decimal integer 0..255
- Trailing characters after prefix integer are rejected

## Topology

The transform output uses canonical FS/GS/RS/US four-scope topology:

| Separator | Name | Role |
|-----------|------|------|
| FS | File Separator | Origin scope |
| GS | Group Separator | Group scope |
| RS | Record Separator | Record scope |
| US | Unit Separator | Unit scope |

LL/MM/NN are deprecated historical 3-slot transform mnemonics only.
