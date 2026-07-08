# OMI-Port Boundary Checklist

Use this checklist before committing changes or declaring a milestone.

## Build

- [ ] `make clean && make test` — all binaries pass, 0 warnings
- [ ] `make hs-check` — Haskell module compiles (optional, skips if ghc absent)

## No Forbidden APIs

The following patterns must not appear in `src/` or `include/`:

```sh
grep -rn 'connect\|send\|recv\|socket\|open\|mount' src/ include/ || true
```

Expected result: no matches in library code (test files may use these
in strings or comments, but the library itself must not).

## No Sibling Repo Imports

```sh
grep -rn 'omi_lisp\|omi_isa\|omi_canvas\|omi_tetragrammatron\|omi_protocol' include/ src/ || true
```

Expected result: no matches.

## Sibling Repos Untouched

```sh
git -C /home/main/omi/omi-lisp status --short
git -C /home/main/omi/omi-protocol status --short
```

Expected result: no output (clean working trees).

## No Authority Flags Set

```sh
grep -rn 'authority\.\(accepted\|validated\|receipted\|connects\|transmits\|mounts\)\s*=\s*[^0]' src/ || true
```

Expected result: no matches in library code (test files may set flags
to 1 for negative proof).

## No Hash Identity

```sh
grep -rn 'hash.*identity\|digest.*identity\|checksum.*identity' docs/ src/ include/ || true
```

Expected result: no matches.

## Deprecated Mnemonics

```sh
grep -rn '\bLL\b\|\bMM\b\|\bNN\b' include/ src/ || true
```

Expected result: no matches in public API (docs may reference them
as historical context).

## Manifest Current

- [ ] `MANIFEST.md` lists all release files
- [ ] `STATUS.md` reflects current binary count and assertion count
- [ ] `VERSION.md` milestone name matches the release
- [ ] `RELEASE_NOTES_v0_1.md` exists
- [ ] `docs/RELEASE_GATE.md` exists

## Release Gate

After boundary checks pass, run the full release gate:

```sh
docs/RELEASE_GATE.md
```

All items must pass before v0.2 work begins.

## Run Checklist

```sh
make clean && make test && make hs-check
git -C /home/main/omi/omi-lisp status --short
git -C /home/main/omi/omi-protocol status --short
echo "Boundary check complete"
```
