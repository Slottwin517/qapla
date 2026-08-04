*This text was written with the assistance of an AI. Careful: assistance doesn't mean the AI wrote it. It means it corrected, reviewed and filled in some parts, but the author is human (or so I believe).*

*[Léeme en español](README.es.md)*

# Qapla' Project
## This is how you train a transformer from scratch on an eight-buck ESP32-S3.

*The (Klingon) GPT nobody asked for but everybody needed.*

![Qapla' training on an ESP32-S3](assets/training-alt.jpg)

**And why did we need it?** Because we take for granted that training a model requires a GPU or a datacenter. Not always: sometimes something as small and as cheap as an eight-buck micro is enough to train one from scratch.

**Read that again: train. From scratch.**
Not run a pre-cooked model. Train. Forward pass, backprop and weight updates, inside the chip.

## What is Qapla'?

Edge AI is nothing new. TinyML has been doing inference on microcontrollers for years, community ports of llama2.c — Andrej Karpathy's minimalist project — put ~260K-parameter transformers on an ESP32, and just recently a brilliant project got a model of almost 29 million parameters running on an $8 ESP32-S3. They're excellent pieces of work, and although they happen to have overlapped in time with this experiment, they weren't the model we were following.

The [esp32-ai](https://github.com/slvDev/esp32-ai) project by Slava S. (slvDev), and others like it, all share one thing: they are inference. The model is born somewhere else — a GPU, a datacenter — trained on its data, quantized, and only then loaded onto the chip so it can *run* it. The brain is cooked outside and served on-chip.

We asked ourselves a different question: **what happens when the model can't be born outside?** What happens when it can't come pre-trained — because the data it needs to learn doesn't exist until the device is *in place* — can't carry that data with it, and has no internet to download it?

We know what you're thinking: "Fine, but… why would anyone need to train a transformer on an ESP32?" And it's a fair question. Maybe the answer is "no reason at all". But… if we're going to get creative, picture this: a sensor bolted to a piece of farm machinery in the middle of a field, which has to learn the normal vibration of *that specific machine* (different from any other machine in the world) to spot when something's going wrong and schedule maintenance before it breaks (and no, you won't catch me out: I said there's no internet, but… LoRa? ;). Or picture a sensor in a plot of land that learns how *that particular* soil dries out — its earth, its sun, its drainage — and predicts when it'll need watering, before the plants suffer. In those cases (and others we can think of) the data didn't exist until the device was installed: nobody could have pre-trained it. The chip has to learn on the fly, alone, right where it stands.

We don't have a piece of farm machinery lying around to experiment with. So, to put the real learning ability of an ESP32 to the test, we designed the experiment around the only thing we did have: **language.** How far can an eight-buck chip get, learning a language from scratch, with nobody's help?

## What does training on a micro actually mean?

Training inside an eight-buck micro imposes rules of the game a datacenter doesn't have. And those rules dictate everything else:

**Once again, memory rules.** An ESP32-S3 has a few MB of RAM/PSRAM, not gigabytes. That caps the size of the model: we're talking hundreds of thousands of parameters here, not millions. A model that "fits" and trains on the chip is, by necessity, small.

**The small model rules the task.** A model this size can learn the *structure* of a language (how words are built, its phonotactics, some grammar), but not the deep *semantics* of an entire tongue. The task has to be cut to the model's size.

**And the corpus rules the result.** With a small model you don't need gigabytes of text. You need a corpus that is compact, clean and structured. And, if you're going to publish it, you need it free of copyright headaches.

Put the three constraints together — small model, narrow task, clean and compact corpus — and the question becomes concrete: *which language ticks all of those at once?*

I could tell you we ran a brainstorming session to decide which language to experiment with in this first phase, but sometimes it's better to stick to the old "the first idea is usually the good one"… and in this particular case, the first language that came to mind… was **Klingon.**

## The Klingon language

Yes, Klingon. The language of the *Star Trek* warriors. And if you keep reading you'll find the choice has less of the nerd about it and more of the engineer than it seems.

Klingon isn't gibberish that spits out alien-sounding noises and calls it a day. It was created by the linguist Marc Okrand in 1984, and it is a constructed language with systematic phonology, grammar and morphology: it has an unusual word order (object-verb-subject) and a morphology with strict rules. In other words: it has real structure to learn, which is exactly what a small model needs in order to prove it's really learning and not just memorising noise.

And it fits our constraints:

- **Rich structure, bounded vocabulary.** Enough grammar for the model to have something to capture, but a corpus small enough to fit the micro's rules.
- **Reduced alphabet.** Working character by character, a vocabulary of ~30 symbols keeps the model tiny — exactly what the ESP32's memory demands.
- **A clean, free corpus.** There's a community dictionary under an open licence (boQwI'), so we could train and share without stepping on anyone else's legal turf.

Put another way: Klingon is an ideal testbed. A real language, with real grammar, but of a size that fits in the palm of your hand. The perfect lab in which to squeeze the engine before taking it — perhaps in another phase of the project — to real minority languages, with real speakers. Sami? Quechua? Nahuatl? That… is another story.

Oh, and yes: it's undeniably cool. A low-cost chip whispering Klingon on a 1.3" OLED has something of the nerd about it, but something of magic too. But that… is just the bonus.

**qapla'.** *(Klingon for "success". It seemed like the right name.)*

## What it is NOT (let's be honest)

So nobody walks away with the wrong idea, and because rigour matters:

**It is not a pocket ChatGPT.** It doesn't chat, doesn't answer questions, doesn't reason. It's a tiny generative model that learns the *shape* of a language, not its meaning.

**It does not produce semantically perfect Klingon.** It learns structure — prefixes, suffixes, word order, how phrases sound — and produces text that *looks* like Klingon and respects many of its rules. But don't expect fully meaningful sentences that a Klingon scholar would sign off on without complaint (if someone aboard the Enterprise received a message from our ESP32, it would probably end up causing a diplomatic incident). And in any case, there isn't enough Klingon in the world to pull that off, nor would the model it would take fit on the chip.

**It is not inference in disguise.** There is no pre-trained model hidden anywhere. The chip starts with random weights and no prior knowledge of Klingon, and learns from scratch. What you're seeing is real learning, not a model cooked somewhere else and served here.

**It is not fast.** Let's be serious: we've said it to death, but… it's an eight-buck micro, not a GPU! Training takes hours. That's precisely the point: that it's slow and still works.

What it **is**: proof that a humble microcontroller with a maker's spirit can train a language model from scratch, entirely on board. No more, no less. Which is no small thing.

## How it works

Here's what really matters, and what you can verify for yourself in the code. The entire learning cycle happens on board:

**Inside the ESP32-S3:**
- ✓ Random initialisation of the weights (mind the seed, ahem)
- ✓ Reading and tokenising the corpus
- ✓ Forward pass
- ✓ Loss computation (cross-entropy)
- ✓ Backpropagation (gradients derived by hand)
- ✓ Weight updates (SGD with momentum + cosine LR)
- ✓ Saving the best model to flash (LittleFS)
- ✓ Text generation with the learned weights

**Outside the ESP32-S3:**
- ✗ Nothing.

### The architecture

There's nothing new here. It's a tiny but complete transformer: one block, single-head causal attention, tied weights, a ReLU FFN and LayerNorm. It works character by character, with a vocabulary of ~31 symbols. In total, **~319,000 parameters**.

### The backprop, by hand

There's no PyTorch and no autograd here. Every derivative of the forward pass is written out explicitly in C. To make sure there were no mistakes, we checked those gradients numerically against a PyTorch reference implementation (*gradient checking*) before laying a finger on the chip. It's the most delicate part and the most fun to watch working.

### The feat isn't the parameters: it's the memory

A 319K-parameter model "only" takes ~1.3 MB. But **training** isn't just holding the weights. You need, all at once and in memory: the weights, an equally large copy for the gradients, another for the optimiser momentum, another to keep the best model, plus all the intermediate activations the backward pass needs, plus the corpus. Several MB in the chip's PSRAM, all told.

That's the real difference between *inferring* (the weights are enough) and *training* (weights + gradients + momentum + activations). And it's exactly what makes this project different: it doesn't store a model to run it, it **trains** it, with everything that drags along.

## Reproduce it

This repo ships the **engine**, not the corpus. The whole point is that the chip learns *your* text, so the corpus is on you.

**What you'll need:** an ESP32-S3 with PSRAM (the N16R8), an SH1106 OLED over I2C (optional, but it's half the fun), and PlatformIO.

```bash
# 1. Your corpus, in plain text (one sample per line)
python tools/gen_header.py my_text.txt src/corpus_klingon.h

# 2. Build and flash
pio run -t upload

# 3. Watch it learn: the loss dropping live
pio device monitor
```

And that's it. The chip starts with random weights, trains, saves the best model to flash and, on the next boot, loads it and generates. Unplug it halfway through and you lose whatever it learned since the last checkpoint; unplug it after it's done and the brain is still there.

**One warning:** this takes hours. Many. Even days. It's not a bug: it's training a transformer from scratch on an eight-buck ESP32-S3.

## The numbers

All of this happened inside the chip, powered by a phone charger.

![Training](assets/training.jpg)

| | |
|---|---|
| **Parameters** | ~319,000 |
| **Vocabulary** | 31 characters |
| **Context** | 32 characters |
| **Optimiser** | SGD with momentum (0.9) + cosine LR |
| **Steps** | 5,000 |
| **Duration** | ~2 days plugged into a charger |
| **Hardware** | ESP32-S3 N16R8 + SH1106 OLED |

And the loss dropping, exactly as it looked on the screen:

| Step | loss (batch) | moving average |
|---|---|---|
| 1,495 | 2.193 | 2.137 |
| 2,549 | 1.982 | 2.035 |
| 4,905 | 1.996 | **1.871** |

*(We have no photo of the very first boot: by the time it occurred to us to document it, the chip had already been at it for a good while.)*

![Final step](assets/final-step.jpg)

The moving average is the one that matters: each batch's loss jumps around a lot (it depends which sentences it got), but the average comes down steadily. **The chip finished at ~1.87.**

### And this is what it spits out

![Generated Klingon](assets/klingon-output.jpg)

```
hIngan motlh puS ruq tuq DujDaq SISwI' nge'vI'
vIn SuvwI' yIvwI' qarghtaHvIS SIchoH
```

It's not fully meaningful Klingon — we did warn you — but look at the morphology:

- **`SuvwI'`** is *warrior*: the root `Suv` (to fight) plus the suffix `-wI'` ("one who does"). A real word, correctly built.
- **`DujDaq`** is *on the ship*: `Duj` (vessel) plus the locative suffix `-Daq`.
- **`qarghtaHvIS`** carries `-taHvIS` (*while*, continuous + adverbial), a compound suffix stuck exactly where it belongs.
- And **`hIngan`** lands two letters short of `tlhIngan`, which is literally the word for "Klingon".

Other words are well formed but don't exist: the model learned the **rules**, not the dictionary. Which is exactly what we said it would do.

Nobody taught it those suffixes. It worked them out on its own, character by character, inside an eight-buck micro.

## And from here, where?

Anyone with time, curiosity and enough willpower can write a backprop by hand and train a little model on a micro. That's not the hard part.

The interesting bit comes next: pushing the engine to its limit with a real task — a real language, with real speakers and a corpus far larger than Klingon can offer. That's where the lab ends and the actual engineering begins: getting a more capable model to fit and learn on a chip that hasn't grown.

We have an idea or two. But that, if it happens, is another story.

## Licence

Code under **Apache 2.0**. Take it, hack it, feed it your own language.

---

*All the training corpus comes from freely licensed sources (boQwI' / klingon-assistant-data, Apache 2.0). The Klingon language was created by Marc Okrand; Klingon, Star Trek and associated marks are the property of their respective owners (CBS Studios / Paramount). This is an open-source, educational and research project, not affiliated with or endorsed by them. See [CORPUS.md](CORPUS.md) for the details of sources and licences.*

*Oh, and the random number generator's seed is 1701. If you don't know why… then maybe, just maybe, this isn't your repo ;)*
