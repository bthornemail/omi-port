# OMI-Port Transform

## PortTensor_G

```
PortTensor_G(source, target) -> OMI_PortRoute
```

The transform accepts two scopes and a gauge, and produces a deterministic
route candidate. The gauge selects the transform dialect within the F0..FF
family.

### Algorithm (C99)

1. Validate gauge in F0..FF
2. Mix source URI bytes and prefix_len into 32-bit accumulator
3. Mix gauge into accumulator
4. Mix target URI bytes and prefix_len into accumulator
5. Derive route fields from accumulator:

```
fs   = acc[0:16]
gs   = acc[8:24]
rs   = acc[16:32]
us   = acc[24:40]
fs_i = acc[4:20]
gs_i = acc[12:28]
rs_i = acc[20:36]
us_i = acc[28:44]
reg   = acc
stack = acc ^ 0xDEADBEEF
car   = acc ^ 0xCAFEBABE
cdr   = acc ^ 0xBAADF00D
```

6. All authority flags set to 0

### Invariants

- Same source, target, gauge -> same route
- Different source -> different route
- Different gauge -> different route
- All authority flags remain 0
