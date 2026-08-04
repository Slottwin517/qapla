# Tests and evidence

Two claims in the main README deserve proof rather than trust: that the
hand-derived backward pass is correct, and that this kernel really trains on
xtensa. Here's how to check both yourself.

## 1. Gradient check

`gradcheck.c` compares every analytic gradient produced by `backward()` against
a centred finite difference of `forward()`, on the **published** `src/handgpt.h`
— not on a copy. Built in double precision with small dimensions so the finite
difference is accurate enough to mean something.

```bash
cc -O2 -DHANDGPT_DOUBLE -DNV=11 -DNC=16 -DNT=8 tests/gradcheck.c -lm -o gradcheck
./gradcheck
```

Result on a clean clone:

```
gradient check - analytic vs. centred finite differences
  dims: NV=11 NC=16 NT=8, 3552 parameters, double precision

  param[  1035]  numeric +0.00398517   analytic +0.00398517   rel 7.38e-10
  param[  2795]  numeric -0.01040326   analytic -0.01040326   rel 4.63e-10
  param[  2766]  numeric +0.01528546   analytic +0.01528546   rel 3.94e-10
  ...
  worst relative error: 1.07e-08  ->  PASS
```

Twenty parameters sampled at random across the whole model. The threshold is
`1e-4`; the worst case comes in about four orders of magnitude under it.

## 2. Emulator run (QEMU, xtensa)

Before touching real silicon, the same kernel was built with ESP-IDF v5.3.2 and
run under QEMU's xtensa emulation, to confirm it trains on the target
architecture rather than just on a laptop:

```
=== HandGPT training INSIDE the ESP32-S3 (QEMU) ===
 vocab=27 params=14016 C=32 T=16
 step   0 | loss(x1000) 3287
 step  50 | loss(x1000) 122
 step 100 | loss(x1000) 31
 step 150 | loss(x1000) 14
 step 200 | loss(x1000) 9
 step 250 | loss(x1000) 6
 step 300 | loss(x1000) 5
```

Smaller dimensions and a toy corpus — the point was the architecture, not the
result. The loss dropping is what mattered: the kernel trains on xtensa.

## What is *not* here

No GPU training code. The reference implementation used during development to
sanity-check behaviour stays out of this repo on purpose: the claim is that the
chip trains, and nothing in here should muddy that. What you can verify is the
part that matters — that the gradients this code computes are the right ones.
