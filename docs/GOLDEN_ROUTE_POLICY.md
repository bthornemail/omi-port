# OMI-Port Golden Route Output Policy

## Purpose

Golden route output files freeze the deterministic candidate derivation
behavior of the PortTensor_G transform across the F0..FF gauge family.

They detect accidental transform drift when the algorithm is changed
without a version bump.

## Doctrine

- **Golden outputs freeze candidate ABI behavior.**
- They do not freeze truth.
- They do not validate a route.
- They do not receipt a route.
- They do not create identity.
- They only detect accidental transform drift.

## Policy

### Adding a Golden Vector

New gauge vectors may be added to `tests/golden/route_expected.txt`
without a version bump. The test must verify the new vector using the
existing transform algorithm.

### Changing a Golden Value

Changing a golden route output value is allowed **only** when the
transform algorithm is intentionally versioned. Unversioned drift is
a failure.

Procedure for intentional change:

1. Bump `transform_version` in the golden file (e.g., 0.1 → 0.2).
2. Update all affected vector values to match the new algorithm.
3. Pass the full release gate (`docs/RELEASE_GATE.md`).
4. Document the version change in release notes.

### Version String

The golden file header records:

```
transform_version=0.1
```

This version identifies the algorithm that produced the frozen outputs.
A future algorithm change must increment this version.

## Relationship to Other Tests

| Test | Proves |
|------|--------|
| `test_gauge_vectors` | Same input → same route during this implementation (determinism) |
| `test_route_expected` | Same input → same named route fields across versions (ABI freeze) |

## Non-Negotiable

Golden route outputs are not authority. They are not validation.
They are not receipts. They are not identity.

They are a behavioral freeze of the candidate derivation algorithm only.
