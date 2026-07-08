# OMI-Port Version

**omi-port v0.3-omi-lisp-port-fixtures**

Status: frozen / documented candidate ABI + golden route + fixture handoff

This version adds read-only OMI-Lisp-shaped port binding fixture
declarations, proven by test, without creating a code dependency
on omi-lisp.

Milestone ladder:

```text
v0.1-gauge-vector-candidate-abi
    candidate ABI exists and is release-gated

v0.2-golden-route-outputs
    route field behavior is frozen against drift

v0.3-omi-lisp-port-fixtures
    OMI-Lisp-shaped declarations exist as fixture handoff only
```

Doctrine:

```text
omi-lisp shape may declare.
omi-port may derive.
golden outputs may freeze behavior.
fixtures may demonstrate handoff.

None of these validate.
None of these receipt.
None of these accept.
None of these connect.
```
