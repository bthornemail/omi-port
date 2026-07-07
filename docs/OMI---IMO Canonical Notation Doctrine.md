# OMI---IMO Canonical Notation Doctrine

## Status

Canonical Draft
Authority Layer: OMI pre-language notation, memory topology, and porting annotation
Depends on: FS/GS/RS/US control envelope doctrine
Deprecates: LL/MM/NN as canonical authority
Preserves: LL/Ket as historical nibble-selection analogy only

---

## 1. Canonical Form

The canonical compact OMI route form is:

```text
omi---imo
```

The canonical expanded route form is:

```text
o---o/---/?---?@---@
```

The canonical machine expansion is:

```text
o-FS-GS-RS-US/FS/GS/RS/US?REGISTER?STACK@CAR@CDR
```

The compact ruler form is:

```text
o-S0-S1-S2-S3/S4/S5/S6/S7?REGISTER?STACK@CAR@CDR
```

Where:

```text
S0 = FS
S1 = GS
S2 = RS
S3 = US

S4 = FS'
S5 = GS'
S6 = RS'
S7 = US'
```

The primed fields are the inverse/carrier-side IMO scope.

---

## 2. Core Doctrine

OMI does not begin as a function call.

OMI begins as a scoped memory envelope.

Therefore:

```text
LL/MM/NN is deprecated as canonical authority.
FS/GS/RS/US is canonical.
```

The canonical order is:

```text
place first
relation second
interpretation third
validation fourth
receipt last
```

OMI-Lisp dot notation is not byte-zero primitive. Dot notation is earned after `SP`.

---

## 3. Separator Meaning

The expanded notation:

```text
o---o/---/?---?@---@
```

uses four separator classes.

```text
-  OMI forward scope / citation route
/  IMO inverse scope / carrier route
?  payload, register, stack, mask, witness, or query field
@  CAR/CDR relation pointer
```

Expanded:

```text
o-FS-GS-RS-US/FS/GS/RS/US?REGISTER?STACK@CAR@CDR
```

This gives:

```text
four OMI-side scope fields
four IMO-side scope fields
two query/register fields
two CAR/CDR relation fields
```

The frame is not merely text.

The frame is a printable memory pointer surface.

---

## 4. Binary Frame

The OMI-IMO frame is:

```text
256 bits
32 bytes
64 hex nibbles
```

It is divided into two 128-bit halves.

### Ruler Half

```text
S0 S1 S2 S3 S4 S5 S6 S7
```

Each field is 16 bits.

```text
8 × 16 bits = 128 bits
128 bits = 16 bytes
16 bytes = 32 hex nibbles
```

This is the FS/GS/RS/US ruler cascade.

### Payload / Pair Half

```text
REGISTER STACK CAR CDR
```

Each field is 32 bits.

```text
4 × 32 bits = 128 bits
128 bits = 16 bytes
16 bytes = 32 hex nibbles
```

Together:

```text
ruler half        = 128 bits = 32 nibbles
payload/pair half = 128 bits = 32 nibbles
full frame        = 256 bits = 64 nibbles
```

---

## 5. CONS Spine

The expanded notation may be represented as a CONS spine:

```lisp
(omi---imo . (o---o . (/---/ . (?---? . @---@))))
```

This means:

```text
omi---imo
    canonical reversible frame

o---o
    forward OMI scope ruler

/---/
    inverse IMO carrier ruler

?---?
    witness / register / stack / query ruler

@---@
    CAR/CDR relation ruler
```

The surface route and the CONS spine are dual views of the same structure.

```text
surface route = URI-compatible traversal
CONS spine    = relation-composed traversal
```

---

## 6. Slide Rule and Nomogram Interpretation

`|OMI---IMO>` may be interpreted as a slide-rule-like or nomographic address surface.

It provides:

```text
start point
stop point
orientation
place-value ruler
subpath decomposition
```

It does not provide acceptance.

The notation behaves like a calibrated ruler:

```text
source scope
→ place-value displacement
→ inverse carrier scope
→ witness/query field
→ relation pointer field
```

A slide rule does not own multiplication. It aligns scales.

Likewise, OMI notation does not own data. It aligns sign-value data against a reversible place-value memory frame.

---

## 7. Radix Decomposition

The full frame is base16 at the nibble level.

```text
1 nibble  = 4 bits
1 nibble  = one base16 digit
4 nibbles = 16 bits
8 nibbles = 32 bits
32 nibbles = 128 bits
64 nibbles = 256 bits
```

Each visible subpath may be decomposed into base4 pairs
