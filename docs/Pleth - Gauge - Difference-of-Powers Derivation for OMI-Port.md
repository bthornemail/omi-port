## Pleth / Gauge / Difference-of-Powers Derivation for OMI-Port

OMI-Port derives a readable route from a source-target relation.

The source and target alone do not determine how the relation should be read. They provide the two addressed quantities. A gauge is still required to select the alignment by which their difference becomes readable.

This follows from the first algebraic decomposition:

```text
a² − b² = (a − b)(a + b)
```

The binary relation splits into:

```text
a − b
    gauge line / selected difference / traversal direction

a + b
    span / carrier width / reference extent
```

Thus even at the square level, relation is not primitive unity. It decomposes into difference and span.

For cubic comparison:

```text
a³ − b³ = (a − b)(a² + ab + b²)
```

The first factor remains the gauge line:

```text
a − b
```

The second factor is not merely a scalar product. It is the reference surface between the two cubic quantities:

```text
a² + ab + b²
```

This surface is the pleth: the fullness, plinth, or readable extension between two relation volumes.

Therefore a source-target port transform has the form:

```text
PortTensor_G(source, target)
    = GaugeLine(source, target) × Pleth_G(source, target)
```

or:

```text
T_G(a, b)
    = (a − b) × Pleth_G(a, b)
```

The gauge line selects the difference.

The pleth supplies the readable surface.

The F* gauge selects which pleth weighting is used.

The derived OMI-IMO route is the resulting readable candidate frame.

In OMI-Port terms:

```text
a
    source scope

b
    target scope

a − b
    selected source-target difference

a + b
    carrier span

a² + ab + b²
    reference plinth / pleth surface

G
    F* gauge dialect

Pleth_G(a,b)
    selected weighted reference surface

T_G(a,b)
    derived OMI-IMO route candidate
```

This means URI-CIDR source and target declarations are not themselves enough. They name and scope the endpoints, but they do not select the interpolation. The gauge provides the late-bound alignment selector.

Canonical rule:

```text
URI names.
CIDR scopes.
F* gauges.
Pleth surfaces make the difference readable.
OMI routes.
Validation and receipt accept.
```

The gauge is not primitive structure. It is not the source. It is not the target. It is not the carrier. It is not validation.

The gauge is a late-bound selector over an already addressed relation.

Therefore OMI-Port must treat the gauge as non-authoritative:

```text
gauge selected does not mean route accepted
gauge selected does not mean route validated
gauge selected does not mean route connected
gauge selected does not mean route receipted
```

The gauge table defines possible alignments.

The gauge word selects one alignment in-stream.

The route candidate preserves that selected alignment for downstream inspection.

Only downstream validation and receipt authority may accept.

### Weighted Pleth and Sexagesimal Frame

A weighted pleth such as:

```text
60x² + 16xy + 4y²
```

acts as a numeration surface.

It does not replace the source-target relation. It makes the selected relation countable at a declared resolution.

In OMI-Port, this means:

```text
source-target relation
    gives the addressed pair

gauge line
    selects the difference to read

weighted pleth
    supplies the countable reference surface

OMI-IMO frame
    stores the derived route candidate
```

So the OMI-Port tensor may be read as:

```text
PortTensor_G(source, target)
    = selected difference × weighted pleth
```

The result is not a connection.

It is a readable route candidate.

### Kernel Boundary

The gauge does not belong in the kernel.

The kernel has:

```text
NULL
BIT
PAIR
RELATION
```

The gauge appears later, when an addressed relation must be aligned into a readable frame.

Thus:

```text
kernel
    defines primitive structures

address/frame
    defines where the relation is placed

gauge
    selects how the addressed relation is read

projection
    displays the selected reading

validation/receipt
    accept or reject
```

Canonical rule:

```text
The gauge is not the cube.
The gauge is not the plinth.
The gauge is the cursor line that selects how the plinth is read.
```

### OMI-Port Consequence

OMI-Port is therefore not merely:

```text
source → target
```

It is:

```text
source × target × gauge → route candidate
```

or:

```text
PortTensor_G(source, target) → OMI-IMO place-value route
```

The source and target supply the addressed relation.

The gauge supplies the selected difference.

The pleth supplies the readable surface.

The OMI-IMO route supplies the place-value candidate.

Validation and receipt accept.

### One-Line Canon

```text
OMI-Port derives route candidates by applying an F*-selected gauge line to a source-target pleth surface, producing an OMI-IMO place-value frame without connecting, validating, accepting, or receipting it.
```
