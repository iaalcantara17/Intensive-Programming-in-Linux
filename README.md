# Intensive Programming in Linux Homework

Coursework for CS288 (Ubuntu, Bash, C, Webscraping in Python).

## Environment

**OS**: Ubuntu 25.04
**Compiler**: `gcc`
**Shell**: `bash`

## Summary:

This is a collection of the various assignments given during the semester, consisting of Bash scripts, advanced topics in the C programming language,
and a webscraping assignment consisting of Python, PHP, and some MongoDB.

---

## Highlights
- **Bash:** recursive traversal, CSV/text pipelines, input validation, timestamped backups with logs.
- **C (systems):** binary I/O, matrix multiply, CLI parsing with `getopt`, hex/ASCII memory viewer.
- **Algorithms & DS:** radix sort (ints/floats via bit tricks), singly-linked-list reverse & in-place sort.
- **A\* search (15-puzzle):** OPEN/CLOSED sets, `f=g+h` with Manhattan heuristic; generator ensures solvable start states.
- **Parallelism:** Pthreads work splitting (Leibniz π), MPI histogram/count sort with scatter/reduce.
- **Data pipeline:** curl snapshot → BeautifulSoup parse → persist to MongoDB → PHP table view.

---

## Assignments (what’s in each folder)

### Extra Homework Assignment
- `skeleton-1.c` — **MPI dot-product** scaffold: rank/size init, contiguous chunking, per-rank partial dot, reduction.
- `skeleton-2.c` — **15-puzzle search** scaffold: node representation, successors, and path reconstruction hooks.

### Homework 1 — Bash fundamentals
- `31569756_Problem1.sh` — **Rock–Paper–Scissors** (validated input, random CPU choice, result logic).
- `31569756_Problem2.sh` — **Path inspector**: file/dir detection, perm checks, counts of files/dirs, sizes.
- `31569756_Problem3.sh` — **Timestamped backup** of ≥3 files into `backup_YYYYMMDD/` with `backupLog.txt`.
- `31569756_Problem4.sh` — **Interactive dir browser**: create/enter dir, list entries, page through file contents.

### Homework 2 — Text processing (Bash) + small C I/O demo
- `Problem1.sh` — Dictionary analytics:
  - Count words with ≥3 `a`/`A`.
  - Count words with **exactly three** `e`/`E`.
  - Among words containing `"ee"`, compute **top-3** 3-char **suffixes**.
- `Problem2.sh` — C-source metrics: total lines; count & percentage of lines with `scanf` vs `printf`.
- `Problem3.sh` — **Recursive email extractor**: walk a tree, extract, and write **unique** emails to `unique_emails.txt`.
- `Problem4.sh` — **Age ranking** from `people.csv` (`Name,YYYY-MM-DD,…`), compute ages (base year 2024), sort desc.
- `example.c` — Minimal program to generate `scanf`/`printf` hits for Problem2.

### Homework 3 — Binary I/O + recursion (C)
- `create_matrix.c` — Write binary matrix file: header `n`, then `n^3` random ints.
- `31569756_Problem1.c` — **Matrix multiply**: `matrix1.bin × matrix2.bin → result.bin` (header validation, bounds).
- `31569756_Problem2.c` — **Recursive .txt line counter**: descend directories, sum newline counts in `.txt` files.

### Homework 4 — Radix sorting of ints/floats (C)
- `31569756_Problem1.c` — **Bit-wise radix** for unsigned ints; **float sort** via sign/magnitude transform + mapping back.
- `31569756_Problem2.c` — **Nibble (4-bit) radix**: 16 buckets × 8 passes; rebuild in stable order.
- (Images show correctness runs.)

### Homework 5 — Unix-style utilities (C)
- `31569756_Problem1.c` — **Hex/ASCII memory viewer**: print addresses, 8-byte lanes, and ASCII where printable.
- `31569756_Problem2.c` — **`getopt` demo**: options `-c -d -u -f <arg> -s <arg>` + operand handling with validation.
- `31569756_Problem3.c` — **Environment sorter**: bubble-sort `envp` by key using temporary null-terminators around `=`.

### Homework 6 — Linked lists (C)
- `31569756_Problem1.c` — **Reverse** a singly linked list (build from stdin until `-1`, reverse, print, free).
- `31569756_Problem2.c` — **In-place bubble sort** of a singly linked list (pointer-to-pointer traversal), then print & free.

### Homework 7 — **A\*** search on the 15-puzzle (C)
- `31569756_Problem1.c` — Full **A\*** implementation:
  - Node with `f,g,h`, parent link; Manhattan distance `h(n)`; `f=g+h`.
  - OPEN (priority by `f`), CLOSED sets; expand via legal moves; iterate until goal or exhaustion.
  - Progress logging (`iter % 1000`).
- `GenGemPuzzle.c` — **Solvable puzzle generator**:
  - Randomize tiles until parity/blank-row rule indicates **solvable**; print grid and one-line formats for A\* input.

### Homework 8 — Parallel programming
- `31569756_Problem1.c` — **MPI count sort** on `values.bin`:
  - Rank 0 reads `N` ints, broadcasts `N`, **scatters** chunks; each rank builds 0–999 histogram; global **reduce** to counts; reconstruct sorted stream.
- `31569756_Problem2.c` — **Pthreads π (Leibniz)**: split term range across threads; each accumulates partial sum; join + aggregate.
- Utilities: `gendatai.c` (mmap-backed random int file writer), `checkdatai.c` (verify ascending & checksum).

### Homework 9 — Web scraping pipeline
- `script3.sh` — `curl` Yahoo Finance **Most Active** with rotating UAs → `most_active.html`.
- `31569756_Problem.py` — Parse HTML table with **BeautifulSoup**; insert rows into **MongoDB** (`stocks_db.most_active`).
- `index.php` — Display MongoDB collection as a sortable table (`?sort=Symbol|Name|Price|Change|Volume`) using the **MongoDB PHP library**.

### Notes and Practice — drills
Small C experiments (threads, memory, pointer arithmetic) and shell exercises used to prototype before final HWs.
