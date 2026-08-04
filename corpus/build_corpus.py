#!/usr/bin/env python3
"""build_corpus.py — rebuild corpus/klingon.txt from its original source.

Downloads De7vID/klingon-assistant-data (the boQwI' dictionary data, Apache 2.0),
extracts the example sentences, and writes them out repeated a number of times
so a tiny char-level model has enough signal to chew on.

    python corpus/build_corpus.py

Everything it produces is derived from an Apache 2.0 source. See NOTICE.
"""
import io
import os
import re
import tarfile
import urllib.request

URL = "https://codeload.github.com/De7vID/klingon-assistant-data/tar.gz/main"
OUT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "klingon.txt")

# Klingon romanised orthography plus basic punctuation. Anything outside this
# set is dropped, which keeps the byte-level vocabulary small enough for NV=32.
ALLOWED = set("abcDeghHIjlmnopqQrStuvwy' ?!.,")
REPEATS = 15  # a 1.3k-sentence corpus is too small to train on just once

SENTENCE = re.compile(r"\{([^{}]+?):sen[^}]*\}")


def clean(sentence):
    s = sentence.strip()
    if not s or len(s.split()) < 2:
        return None
    if any(ch not in ALLOWED for ch in s):
        return None
    return s


def main():
    print(f"downloading {URL} ...")
    with urllib.request.urlopen(URL) as r:
        blob = r.read()
    print(f"  {len(blob) // 1024} KB")

    sentences = set()
    with tarfile.open(fileobj=io.BytesIO(blob), mode="r:gz") as tf:
        for member in tf.getmembers():
            if not member.name.endswith(".xml"):
                continue
            data = tf.extractfile(member).read().decode("utf-8", "ignore")
            for candidate in SENTENCE.findall(data):
                c = clean(candidate)
                if c:
                    sentences.add(c)

    sentences = sorted(sentences)
    text = "\n".join(sentences * REPEATS) + "\n"
    with open(OUT, "w", encoding="utf-8", newline="\n") as f:
        f.write(text)

    encoded = text.encode("utf-8")
    print(f"wrote {OUT}")
    print(f"  {len(sentences)} unique sentences, repeated {REPEATS}x")
    print(f"  {len(encoded)} bytes, {len(set(encoded))} distinct bytes")


if __name__ == "__main__":
    main()
