# CORPUS.md — about the training data

## The engine ships; the corpus doesn't

Qapla' publishes the **engine** — the on-chip trainer — not a dataset.
The whole point is that the chip learns *your* text, on the device, from
scratch. So there is no corpus committed to this repo. Bring your own.

## Build your own corpus header

1. Put your training text in a plain UTF-8 `.txt` file (one sample per line
   works well). Keep the character set small — this is a *char-level* model,
   so every distinct character is a vocabulary entry (default max: 32).
2. Generate the header:
   ```
   python tools/gen_header.py your_text.txt src/corpus_klingon.h
   ```
3. Build and flash with PlatformIO.

A tiny placeholder (`src/corpus_klingon.h.example`) is included only so the
project compiles out of the box. It won't produce anything meaningful.

## Reproducing the Klingon demo

The demo in the write-up was trained on Klingon example sentences extracted
from **boQwI' / klingon-assistant-data**, which is published under the
**Apache License 2.0**. If you want to reproduce it, that community project
is the clean, permissively-licensed source to work from. Extract the example
sentences, run them through `tools/gen_header.py`, and train.

## Notes on Klingon and copyright

The Klingon language (*tlhIngan Hol*) was created by Marc Okrand. Klingon,
Star Trek and associated marks are the property of their respective owners
(CBS Studios / Paramount). This is an open-source, educational and research
project, not affiliated with or endorsed by them.

Short phrases of a language are generally treated as facts rather than
protectable expression — a point raised in the Axanar litigation regarding
Klingon. Curated *compilations*, however, can carry their own protection.
That's another reason this repo ships no dataset and points you to a
permissively-licensed source instead: use data you have the right to use.
