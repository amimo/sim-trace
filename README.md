# sim-trace
a poc implementation arm64 tracer based on simulation

### Build Test

```
ndk-build NDK_DEBUG=1
```

### Run Test
```
adb push test /data/local/tmp/test && adb shell chmod +x /data/local/tmp/test
adb shell /data/local/tmp/test
```

expected result:

```
#    x0: 0x0000000000000003
#    x1: 0x0000000000000005
#    x2: 0x0000007fe7960924
#    x3: 0x0000000000000040
#    x4: 0x0000007f8aebc100
#    x5: 0x0000000000000000
#    x6: 0x0000000000000003
#    x7: 0xffffffffffffffff
#    x8: 0x3d39d1cf02e47cf9
#    x9: 0x3d39d1cf02e47cf9
#   x10: 0x000000000000002f
#   x11: 0x0000000000000000
#   x12: 0x0000000000000010
#   x13: 0x0000000000000008
#   x14: 0xfffffffffffffffc
#   x15: 0x0000000000000001
#   x16: 0x0000007fe7960920
#   x17: 0x0000007f8a7fff00
#   x18: 0x00000000ffffffff
#   x19: 0x0000000000001000
#   x20: 0x0000007f8aebc000
#   x21: 0x0000007f8af86b30
#   x22: 0x0000007fe79609d8
#   x23: 0x0000000000000000
#   x24: 0x0000000000000000
#   x25: 0x0000000000000000
#   x26: 0x0000000000000000
#   x27: 0x0000000000000000
#   x28: 0x0000000000000000
#   x29: 0x0000007fe7960950
#    lr: 0x0000005587214af4
#    sp: 0x0000007fe7960920
#    v0: 0x7ff0dead7f8beef17ff00cab7f8ba9e1
#    v1: 0x7ff0dead7f8beef17ff00cab7f8ba9e1
#    v2: 0x7ff0dead7f8beef17ff00cab7f8ba9e1
#    v3: 0x7ff0dead7f8beef17ff00cab7f8ba9e1
#    v4: 0x7ff0dead7f8beef17ff00cab7f8ba9e1
#    v5: 0x7ff0dead7f8beef17ff00cab7f8ba9e1
#    v6: 0x7ff0dead7f8beef17ff00cab7f8ba9e1
#    v7: 0x7ff0dead7f8beef17ff00cab7f8ba9e1
#    v8: 0x7ff0dead7f8beef17ff00cab7f8ba9e1
#    v9: 0x7ff0dead7f8beef17ff00cab7f8ba9e1
#   v10: 0x7ff0dead7f8beef17ff00cab7f8ba9e1
#   v11: 0x7ff0dead7f8beef17ff00cab7f8ba9e1
#   v12: 0x7ff0dead7f8beef17ff00cab7f8ba9e1
#   v13: 0x7ff0dead7f8beef17ff00cab7f8ba9e1
#   v14: 0x7ff0dead7f8beef17ff00cab7f8ba9e1
#   v15: 0x7ff0dead7f8beef17ff00cab7f8ba9e1
#   v16: 0x7ff0dead7f8beef17ff00cab7f8ba9e1
#   v17: 0x7ff0dead7f8beef17ff00cab7f8ba9e1
#   v18: 0x7ff0dead7f8beef17ff00cab7f8ba9e1
#   v19: 0x7ff0dead7f8beef17ff00cab7f8ba9e1
#   v20: 0x7ff0dead7f8beef17ff00cab7f8ba9e1
#   v21: 0x7ff0dead7f8beef17ff00cab7f8ba9e1
#   v22: 0x7ff0dead7f8beef17ff00cab7f8ba9e1
#   v23: 0x7ff0dead7f8beef17ff00cab7f8ba9e1
#   v24: 0x7ff0dead7f8beef17ff00cab7f8ba9e1
#   v25: 0x7ff0dead7f8beef17ff00cab7f8ba9e1
#   v26: 0x7ff0dead7f8beef17ff00cab7f8ba9e1
#   v27: 0x7ff0dead7f8beef17ff00cab7f8ba9e1
#   v28: 0x7ff0dead7f8beef17ff00cab7f8ba9e1
#   v29: 0x7ff0dead7f8beef17ff00cab7f8ba9e1
#   v30: 0x7ff0dead7f8beef17ff00cab7f8ba9e1
#   v31: 0x7ff0dead7f8beef17ff00cab7f8ba9e1
0x0000005587214a48  90000709            adrp x9, #+0xe0000 (addr 0x55872f4000)
#    x9: 0x00000055872f4000
0x0000005587214a4c  f9467929            ldr x9, [x9, #3312]
#    x9: 0x00000055872f5618 <- 0x00000055872f4cf0
0x0000005587214a50  0b000028            add w8, w1, w0
#    x8: 0x0000000000000008
0x0000005587214a54  b9000048            str w8, [x2]
#    w8:         0x00000008 -> 0x0000007fe7960924
0x0000005587214a58  b9000128            str w8, [x9]
#    w8:         0x00000008 -> 0x00000055872f5618
0x0000005587214a5c  b9400040            ldr w0, [x2]
#    x0: 0x0000000000000008 <- 0x0000007fe7960924
0x0000005587214a60  d65f03c0            ret
# Branch to 0x0000005587214af4.
stack result  = 8, register result = 8, global result = 8
```
