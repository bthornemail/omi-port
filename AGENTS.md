# OMI-Port Agent Contract

## Repository Role

`omi-port` is a standalone repository for dormant port-notation and
source-target transform declarations. It is not a runtime or transport
layer. It is a **carrier layer** artifact.

## Non-Negotiable Boundaries

Agents must not:

- Connect, send, receive, or mount
- Open files or sockets as part of the library
- Add transport APIs
- Validate, receipt, or accept state
- Use hashes as identity
- Treat URI as authority
- Treat display order as authority
- Restore archive code
- Import sibling repos (omi-lisp, omi-isa, omi-canvas, omi-tetragrammatron, omi-protocol)

## Canonical Concepts

| Concept | Role |
|---------|------|
| URI-CIDR | Default scope grammar: `<uri>#/<prefix>` |
| F* gauge | Transform operator dialect: F0..FF |
| FS/GS/RS/US | Canonical four-scope output topology |
| omi---imo | Compact route candidate |
| o---o/---/?---?@---@ | Expanded printable route surface |
| LL/MM/NN | Deprecated historical 3-slot mnemonic only |

## Verification Commands

```sh
make clean && make test
make hs-check 2>/dev/null || echo "ghc not found"
git -C /home/main/omi/omi-lisp status --short
git -C /home/main/omi/omi-protocol status --short
```

## Handoff Format

When finishing a task, report:

- Summary
- Files changed
- Boundary checks (no I/O, no authority, no sibling imports)
- Verification results
- Next recommended step
