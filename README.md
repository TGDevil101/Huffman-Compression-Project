# 🗜️ Huffman Encoder

A command-line text compression tool written in C that implements the **Huffman coding algorithm** — a classic greedy algorithm for lossless data compression.

---

## How It Works

Huffman coding assigns shorter binary codes to more frequent characters and longer codes to rarer ones, so the overall bitstream is as compact as possible.

This implementation:

1. Scans the input text and counts how often each character appears.
2. Builds a **min-heap priority queue** ordered by frequency.
3. Repeatedly merges the two lowest-frequency nodes into a parent node until a single **Huffman tree** remains.
4. Traverses the tree to assign a unique binary code to each character (left = `0`, right = `1`).
5. Encodes the original text using those codes and reports compression statistics.

---

## Features

- Supports all 256 ASCII characters
- Min-heap based priority queue for efficient tree construction — O(n log n)
- Displays a formatted code table with each character, its frequency, and its Huffman code
- Prints the full compressed bitstring for the input
- Reports original size, compressed size, and percentage saved

---

## Getting Started

### Prerequisites

- A C compiler (GCC recommended)

### Build

```bash
gcc -o huffman huffman.c
```

### Run

```bash
./huffman
```

Then enter any text at the prompt:

```
Enter text: hello world
```

### Example Output

```
--- Huffman Code Table ---
Character   Times Used   Code
------------------------------
    d           1          0000
    e           1          0001
    h           1          001
    l           3          10
    o           2          11
    r           1          0100
    w           1          0101
      (space)   1          011

--- Compressed Output ---
001 0001 10 10 11 011 0101 11 0100 10 0000

--- Stats ---
Original  : 88 bits  (11 characters x 8 bits each)
Compressed: 27 bits
Saved     : 69.32%
```

---

## Project Structure

```
huffman.c        # Full source — tree, heap, code generation, and main
```

---

## Limitations

- Input is limited to 999 characters
- No file I/O — operates on stdin/stdout only
- Does not produce an actual binary file output; the compressed representation is printed as a readable bitstring for demonstration

---

## Concepts Demonstrated

- Greedy algorithms
- Binary trees and recursion
- Priority queues / min-heaps
- Lossless data compression
- Dynamic memory management in C
