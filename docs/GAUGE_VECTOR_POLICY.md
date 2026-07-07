# OMI-Port Gauge Vector Policy

## Purpose

This document defines the policy governing F*-gauge vector labels in
omi-port. Gauges are transform operator dialect hints within the F0..FF
family. They are not validation, not receipt, and not truth.

## Scope

This policy applies to all gauge-labelled vectors in `tests/golden/`,
`tests/test_gauge_vectors.c`, and any downstream documentation that
references F* gauge semantics.

## Principles

### F* Labels Are Transform Dialect Hints Only

An F* gauge selects a deterministic transform path from source and target
scopes to an OMI_PortRoute candidate. The labels "XOR-like", "AND-like",
"implication", etc. describe the algebraic intuition behind the gauge
selection—they do not construct actual logical operations on route values.

No gauge:

- Validates the route
- Receipts the route
- Creates truth about the route
- Confers authority on the route

### FF Is Default Canonical Closure

`0xFF` is the default gauge. When no gauge is specified, FF is used.
It represents the full closure of the source-target difference under the
PortTensor_G transform.

### F0 Is Allowed as Candidate Contradiction

`0xF0` is the lower bound of the F* gauge family. It is a valid gauge
for transform and produces a deterministic route candidate. An F0 route
is a **candidate contradiction**—it is not an accepted contradiction.
The route it produces does not assert impossibility; it merely records
that the gauge family's lower bound was selected.

## Gauge Semantics Summary

| Gauge | Mnemonic | Intuition |
|-------|----------|-----------|
| F0 | Contradiction | Gauge family lower bound |
| F6 | XOR-like | Asymmetric difference |
| F8 | AND-like | Intersection |
| F9 | XNOR-like | Equivalence |
| FB | Implication | Source→target directed |
| FD | Converse | Target→source directed |
| FE | OR-like | Union |
| FF | Closure | Default canonical |

## Non-Negotiable

No gauge may:

- Validate receipted state
- Accept authority
- Create truth
- Connect, transmit, or mount
- Override authority flags
- Escape the F0..FF range

All gauges produce candidates only. Authority is conferred externally
by the validation/receipt/acceptance pipeline, which is not part of
omi-port.
