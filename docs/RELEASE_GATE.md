# OMI-Port Release Gate

Before any v0.2 work begins, the following must be true.

## Required Artifacts

- [ ] `VERSION.md` exists and names the current milestone
- [ ] `RELEASE_NOTES_v0_1.md` exists
- [ ] `docs/RELEASE_GATE.md` exists (this file)
- [ ] `docs/BOUNDARY_CHECKLIST.md` exists
- [ ] `MANIFEST.md` lists all release files
- [ ] `STATUS.md` names the current milestone

## Build

- [ ] `make clean && make test` passes (0 failures, 0 warnings)
- [ ] `make hs-check` passes or cleanly skips if GHC is absent

## Forbidden API Scan

```sh
grep -rn 'connect\|send\|recv\|socket\|open\|mount' src/ include/ || true
```

Expected: no matches in library code (comments and zero-assigns are allowed).

## Sibling Import Scan

```sh
grep -rn 'omi_lisp\|omi_isa\|omi_canvas\|omi_tetragrammatron\|omi_protocol' include/ src/ || true
```

Expected: no matches.

## Authority Non-Zero Scan

```sh
grep -rn 'authority\.\(accepted\|validated\|receipted\|connects\|transmits\|mounts\)\s*=\s*[^0]' src/ || true
```

Expected: no matches.

## Deprecated Mnemonic Scan

```sh
grep -rn '\bLL\b\|\bMM\b\|\bNN\b' include/ src/ || true
```

Expected: no matches.

## Sibling Repo Status

```sh
git -C /home/main/omi/omi-lisp status --short
git -C /home/main/omi/omi-protocol status --short
```

Expected: no output (clean working trees).

## Boundary Checklist

- [ ] `docs/BOUNDARY_CHECKLIST.md` has been run and all items pass

## Gate Decision

If all items pass, v0.1 is intact and v0.2 work may begin.

If any item fails, the release gate is closed until the failure is
resolved or the milestone version is intentionally bumped.
