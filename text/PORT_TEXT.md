# OMI-Port Text Notation

## Compact Route Candidate

```
omi---imo
```

The canonical FS/GS/RS/US output topology produces a compact OMI-IMO route
candidate string composed of four scope positions connected by `---`.

## Expanded Printable Route Surface

```
o---o/---/?---?@---@
```

Each scope position is rendered using omicron (`o`/`O`) chirality markers:

| Scope | Marker | Description |
|-------|--------|-------------|
| FS    | `o`    | File Separator scope |
| GS    | `o`    | Group Separator scope |
| RS    | `?`    | Record Separator scope |
| US    | `?`    | Unit Separator scope |

The `/` and `@` are structural delimiters separating the four scope positions
into their canonical routing planes.

## Gauge Notation

Gauges are specified as F0..FF hex values indicating the transform operator
dialect selected for the PortTensor_G computation.

## Scope Grammar

Default scope grammar is URI-CIDR:

```
<uri>#/<prefix>
```

## Deprecated

LL/MM/NN are historical 3-slot transform mnemonics only.
The canonical output topology uses FS/GS/RS/US four-scope ordering.
