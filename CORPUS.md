# CORPUS.md — about the training data

## Ours is in the box. Yours is the interesting one.

`corpus/klingon.txt` is the Klingon corpus this project trained on: 1,337 unique
sentences repeated 15 times, 539 KB, 31 distinct bytes. It's there so you can
clone the repo and reproduce a run without hunting for data first.

But the whole point of Qapla' is that the chip learns *your* text. Klingon was a
testbed, not a destination. The interesting experiment isn't repeating ours —
it's pointing this engine at a language, a dialect or a dataset that matters to
you and seeing how far an eight-buck micro gets.

## Using either one

```bash
# Ours, to reproduce
python tools/gen_header.py corpus/klingon.txt src/corpus_klingon.h

# Yours, to find out something new
python tools/gen_header.py your_text.txt src/corpus_klingon.h
```

Then `pio run -t upload`.

If you skip this step entirely the project still builds, falling back to a tiny
placeholder (`src/corpus_klingon.h.example`) that won't learn anything useful.

## Constraints on your corpus

- **Plain UTF-8 text**, one sample per line.
- **At most 32 distinct bytes.** The model is byte-level, so every distinct byte
  is a vocabulary entry — and a multi-byte UTF-8 character like `á` or `ñ` costs
  several slots. `gen_header.py` counts what the firmware counts and refuses to
  generate a header that would overflow. If you need a bigger alphabet, raise
  `NV` in `src/handgpt.h` and accept the extra memory.
- **Small and regular beats big and messy.** A few hundred KB of consistent,
  structured text will teach a 319K-parameter model far more than megabytes of
  noise.

## Provenance and licensing

`corpus/klingon.txt` is derived entirely from **klingon-assistant-data** (the
data behind the boQwI' dictionary), published under the **Apache License 2.0**.
`corpus/build_corpus.py` regenerates it from that source, so you can audit every
transformation. See `corpus/NOTICE` for the attribution the licence requires,
and for what we deliberately left out.

The Klingon language was created by Marc Okrand; Klingon, Star Trek and
associated marks belong to their respective owners (CBS Studios / Paramount).
This is an open-source, educational and research project, unaffiliated with
them. Short phrases of a language are generally treated as facts rather than
protectable expression — a point raised in the Axanar litigation — while curated
*compilations* can carry their own protection. Which is why what ships here
comes from a source that explicitly permits redistribution: use data you have
the right to use.
