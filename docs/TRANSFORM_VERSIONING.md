# OMI-Port Transform Versioning

## Purpose

This document defines when `tests/golden/route_expected.txt` must change
and how version bumps work. It protects the golden route freeze from
accidental or unversioned drift.

## Version String

The golden file header records a `transform_version` value:

```
transform_version=0.1
```

This version identifies the derivation algorithm that produced the frozen
outputs. It is independent of the omi-port release version.

## When to Bump

A version bump is required when any change alters the deterministic route
field values produced by `omi_port_transform()` for any existing gauge
vector.

### Changes That Require a Bump

- Changing the hash/mix constants inside the transform accumulator
- Changing how FS/GS/RS/US fields are extracted from the accumulator
- Changing how `reg`, `stack`, `car`, `cdr` are derived
- Adding a new field to `OMI_PortRoute` that affects existing field values
- Changing the order or presence of scope bytes in the mix loop
- Changing how gauge bytes are folded into the accumulator

### Changes That Do NOT Require a Bump

- Adding new gauge vectors (new inputs produce new outputs)
- Adding new test binaries that exercise existing paths
- Changing documentation, comments, or whitespace
- Changing non-transform code paths (scope parser, chirality helpers, init)
- Adding authority stubs that do not alter route field derivation

## Bump Procedure

1. Increment `transform_version` in `tests/golden/route_expected.txt`
   (e.g., 0.1 → 0.2).
2. Regenerate all golden expected values to match the new algorithm.
3. Update `docs/PORT_TRANSFORM.md` to document the algorithm change.
4. Note the version change in the release notes.
5. Pass the full release gate (`docs/RELEASE_GATE.md`).

## Non-Negotiable

- Golden values are ABI fixtures, not identity.
- Golden values do not validate, receipt, or accept.
- Validation and receipt remain external to omi-port.
- A version bump without passing the release gate is not valid.
- Changing golden values without a version bump is drift, not versioning.
