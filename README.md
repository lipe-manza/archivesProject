# Archives Project

> A low-level data storage and query engine implemented in C, exploring binary file organization, persistent indexing, hash tables, B-Trees, sorting and join algorithms.

[![Language](https://img.shields.io/badge/language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Data Structures](https://img.shields.io/badge/data%20structures-Hash%20Table%20%7C%20B--Tree-orange.svg)](#data-structures)
[![Algorithms](https://img.shields.io/badge/algorithms-Sorting%20%7C%20Joins-green.svg)](#join-algorithms)
[![Storage](https://img.shields.io/badge/storage-Binary%20Files-yellow.svg)](#binary-file-organization)

---

## Overview

**Archives Project** is a database-oriented storage engine implemented entirely in **C**, without relying on an external DBMS.

The project explores how fundamental database-engineering techniques can be implemented directly over binary files:

- Fixed-size binary records
- Direct record addressing using RRN and byte offsets
- Logical deletion
- Free lists
- Hash tables
- Persistent B-Tree indexing
- B-Tree insertion and deletion
- File sorting
- Nested Loop Join
- Single Loop Join using a B-Tree
- Sort-Merge Join
- SQL-like operations

The project focuses not only on functionality, but also on the relationship between **data structures, algorithmic complexity, disk I/O and query performance**.

---

# Architecture

The project is divided into three main layers:

```text
                         ┌──────────────────┐
                         │     main.c       │
                         │ Command Dispatch │
                         └────────┬─────────┘
                                  │
                                  ▼
                         ┌──────────────────┐
                         │   SQL Layer      │
                         │ Operations 1–14  │
                         └────────┬─────────┘
                                  │
                 ┌────────────────┼────────────────┐
                 │                │                │
                 ▼                ▼                ▼
          ┌────────────┐   ┌────────────┐   ┌────────────┐
          │    Core    │   │   B-Tree   │   │   Joins    │
          │ Data / I/O │   │   Index    │   │ Algorithms │
          └──────┬─────┘   └──────┬─────┘   └──────┬─────┘
                 │                │                │
                 └────────────────┼────────────────┘
                                  ▼
                         ┌──────────────────┐
                         │ Binary Files     │
                         │ Persistent Data  │
                         └──────────────────┘
```

## Directory Structure

```text
archivesProject/
│
├── include/
│   ├── IO.h
│   ├── btree.h
│   ├── data_header.h
│   ├── data_record.h
│   ├── filtro.h
│   ├── hash_tables.h
│   ├── sql_functions.h
│   └── tools.h
│
├── src/
│   ├── core/
│   │   ├── IO.c
│   │   ├── data_header.c
│   │   ├── data_record.c
│   │   ├── filtro.c
│   │   ├── hashes.c
│   │   └── tools.c
│   │
│   ├── btree/
│   │   ├── btree_header.c
│   │   ├── btree_page.c
│   │   ├── btree_search.c
│   │   ├── btree_insert.c
│   │   └── btree_delete.c
│   │
│   ├── sql/
│   │   ├── 01_create_table.c
│   │   ├── 02_select_from.c
│   │   ├── 03_select_from_where.c
│   │   ├── 04_delete_from_where.c
│   │   ├── 05_insert_into.c
│   │   ├── 06_update_set_where.c
│   │   ├── 07_create_index.c
│   │   ├── 08_select_from_where_ab.c
│   │   ├── 09_insert_into_ab.c
│   │   ├── 10_delete_from_where_ab.c
│   │   ├── 11_nested_loop_join.c
│   │   ├── 12_single_loop_join.c
│   │   ├── 13_sort_file.c
│   │   └── 14_merge_sort_join.c
│   │
│   └── main.c
│
├── tests/
├── Makefile
└── README.md
```

---

# Binary File Organization

The main database is stored in a binary file instead of a traditional DBMS.

The file consists of a header followed by fixed-size records:

```text
┌───────────────────────────┐
│          Header           │
├───────────────────────────┤
│         Record 0          │
├───────────────────────────┤
│         Record 1          │
├───────────────────────────┤
│         Record 2          │
├───────────────────────────┤
│            ...            │
├───────────────────────────┤
│         Record N          │
└───────────────────────────┘
```

Using fixed-size records allows the system to calculate the physical position of a record directly.

---

# RRN and Byte Offset

The physical position of a record can be calculated from its RRN:

```text
offset = header_size + (record_size × RRN)
```

Therefore:

```text
RRN
 │
 ▼
Byte Offset
 │
 ▼
Record
```

The calculation itself is:

```text
O(1)
```

This becomes particularly useful when combined with the B-Tree index, since the index stores the byte offset associated with an indexed key.

---

# Logical Deletion

Records are not physically shifted when deleted.

Instead, they are marked as removed:

```text
removido = '1'
```

and inserted into a free list.

Conceptually:

```text
Header
  │
  ▼
Removed Record
  │
  ▼
Removed Record
  │
  ▼
Removed Record
  │
  ▼
  -1
```

This avoids physically reorganizing the file after every deletion.

### Advantages

- No record shifting
- No complete file compaction
- Reduced disk I/O
- Constant-time physical deletion
- Deleted space can be reused

---

# Free List

The free list allows future insertions to reuse previously deleted records.

Instead of always appending a new record:

```text
new record → end of file
```

the system first checks whether there is available space:

```text
INSERT
  │
  ▼
Free List available?
  │
 ┌┴─────────────┐
 │              │
Yes             No
 │              │
 ▼              ▼
Reuse          proxRRN
record         append
```

This reduces unnecessary growth of the binary data file.

---

# File Consistency

The binary file maintains a consistency status.

Conceptually:

```text
'0' → inconsistent
'1' → consistent
```

Before modifying the file, the status is changed to inconsistent.

After the operation succeeds, it is restored to consistent.

```text
           Write Operation
                 │
                 ▼
        status = inconsistent
                 │
                 ▼
             modify file
                 │
                 ▼
        status = consistent
```

This provides a basic mechanism for detecting files that may have been left in an incomplete state after a write operation.

---

# Data Structures

## Hash Tables

Hash tables are used to efficiently maintain:

- Unique stations
- Unique station pairs

The implementation uses **Separate Chaining** for collision resolution:

```text
Bucket
  │
  ▼
┌──────┐    ┌──────┐    ┌──────┐
│ Node │ →  │ Node │ →  │ Node │ → NULL
└──────┘    └──────┘    └──────┘
```

For station names, the project uses the **djb2** hashing algorithm.

For station pairs, the pair is normalized so that:

```text
(A, B) == (B, A)
```

This prevents the same relationship from being counted twice.

---

## Why Hash Tables?

A naive implementation could search the entire collection whenever a new station is encountered:

```text
for each station:
    search all previous stations
```

This can lead to:

```text
O(N²)
```

behavior.

With a hash table, lookup and insertion have expected:

```text
O(1)
```

complexity.

Therefore, building the set of unique stations can be performed in expected:

```text
O(N)
```

time.

> The hash table is primarily used for uniqueness and cardinality. It is not the primary index for arbitrary `WHERE` queries in this project.

---

# B-Tree

The project implements a persistent **B-Tree of order 4**.

Each page can contain up to:

```text
3 keys
4 children
```

The B-Tree stores the indexed key together with the physical position of the corresponding record:

```text
┌──────────────────────┐
│       BTreeKey       │
├──────────────────────┤
│ C  → indexed key     │
│ Pr → byte offset     │
└──────────────────────┘
```

The resulting architecture is:

```text
             Search Key
                 │
                 ▼
          ┌────────────┐
          │   B-Tree   │
          └─────┬──────┘
                │
                ▼
           Byte Offset
                │
                ▼
       ┌─────────────────┐
       │   Binary File   │
       └─────────────────┘
```

---

# B-Tree Search

For a balanced B-Tree:

```text
Search = O(log N)
```

Instead of scanning every record:

```text
Record 0
Record 1
Record 2
...
Record N
```

the system can perform:

```text
Search Key
    ↓
B-Tree
    ↓
Byte Offset
    ↓
Record
```

This changes indexed lookup from a sequential scan to logarithmic tree traversal, followed by direct file addressing.

---

# B-Tree Insertion

Insertion is implemented recursively.

The algorithm handles:

- Searching for the correct child
- Ordered insertion
- Page overflow
- Page splitting
- Key promotion
- Creation of a new root

Conceptually:

```text
             Full Page
                 │
                 ▼
               Split
             /       \
            /         \
       Left Page    Right Page
            \         /
             \       /
              Promoted
                 Key
                  │
                  ▼
                Parent
```

When a split reaches the root, a new root is created.

---

# B-Tree Deletion

Deletion maintains the structural properties of the B-Tree.

The implementation handles:

```text
Deletion
   │
   ├── Leaf deletion
   │
   ├── Internal node
   │      └── In-order successor
   │
   └── Underflow
          │
          ├── Redistribution
          │
          └── Merge
```

When a node has insufficient keys, the implementation can redistribute keys with a sibling or merge pages when redistribution is not possible.

The root can also shrink when required.

---

# B-Tree Page Reuse

The B-Tree maintains its own free list.

Therefore, the project has two separate free-space management mechanisms:

```text
                    Storage
                       │
             ┌─────────┴─────────┐
             ▼                   ▼
        Data File             B-Tree
             │                   │
             ▼                   ▼
       Record Free List    Page Free List
```

When a new B-Tree page is required, a previously removed page can be reused before extending the index file.

This reduces unnecessary growth of the index.

---

# SQL-like Operations

The program exposes 14 operations:

| # | Operation |
|---:|---|
| 1 | CREATE TABLE |
| 2 | SELECT FROM |
| 3 | SELECT FROM WHERE |
| 4 | DELETE FROM WHERE |
| 5 | INSERT INTO |
| 6 | UPDATE SET WHERE |
| 7 | CREATE INDEX |
| 8 | SELECT FROM WHERE using index |
| 9 | INSERT INTO using index |
| 10 | DELETE FROM using index |
| 11 | Nested Loop Join |
| 12 | Single Loop Join |
| 13 | Sort File |
| 14 | Merge Sort Join |

The main program dispatches the requested operation based on the operation number.

```text
Input
  │
  ▼
Operation Number
  │
  ├── 1  → CREATE
  ├── 2  → SELECT
  ├── 3  → SELECT WHERE
  ├── ...
  ├── 11 → Nested Loop Join
  ├── 12 → Single Loop Join
  ├── 13 → Sort
  └── 14 → Merge Sort Join
```

---

# Join Algorithms

One of the main objectives of the project is to demonstrate how different algorithms affect query performance.

Three join strategies are implemented:

1. Nested Loop Join
2. Single Loop Join using a B-Tree
3. Sort-Merge Join

This allows direct comparison between brute-force, indexed and sorting-based approaches.

---

# 11. Nested Loop Join

The Nested Loop Join is the baseline implementation.

For every record in the first file, the second file is scanned:

```text
for each A:
    for each B:
        if A.key == B.key:
            JOIN
```

Its complexity is:

```text
O(N × M)
```

For similarly sized datasets:

```text
O(N²)
```

### Characteristics

- Simple
- No preprocessing
- Does not require an index
- Works with arbitrary join conditions
- Expensive for large datasets

This implementation serves as the baseline against which the optimized strategies can be compared.

---

# 12. Single Loop Join + B-Tree

The Single Loop Join uses the B-Tree index to avoid scanning the second file for every record.

Without an index:

```text
A1 → scan B
A2 → scan B
A3 → scan B
...
```

With the B-Tree:

```text
A1 ──→ B-Tree ──→ offset ──→ B
A2 ──→ B-Tree ──→ offset ──→ B
A3 ──→ B-Tree ──→ offset ──→ B
```

For each record from the first file, the indexed lookup takes approximately:

```text
O(log M)
```

Therefore, the join has expected complexity:

```text
O(N × log M)
```

instead of:

```text
O(N × M)
```

This demonstrates the practical impact of adding an index to a query workload.

---

# 13. Sort File

The project can physically sort a binary file according to a selected field.

The process is:

```text
Binary File
    │
    ▼
Read valid records
    │
    ▼
Load into RAM
    │
    ▼
qsort()
    │
    ▼
Rewrite file
```

The implementation uses the C standard library `qsort()`.

Sorting complexity:

```text
O(N log N)
```

with approximately:

```text
O(N)
```

additional memory for the loaded records.

The sorted files are used by the Sort-Merge Join.

---

# 14. Sort-Merge Join

The Sort-Merge Join is the most optimized join strategy implemented in the project for large datasets where sorting is appropriate.

Both files are first sorted according to their join attributes:

```text
File A
  │
  └── sort by codProxEstacao

File B
  │
  └── sort by codEstacao
```

After sorting, the files are traversed simultaneously:

```text
             File A                 File B
                │                      │
                ▼                      ▼
              i = 0                  j = 0
                │                      │
                └──────────┬───────────┘
                           ▼
                       Compare
                           │
             ┌─────────────┼─────────────┐
             ▼             ▼             ▼
          A < B         A == B        A > B
             │             │             │
             ▼             ▼             ▼
           i++            JOIN           j++
```

The merge phase takes:

```text
O(N + M)
```

After accounting for sorting, the total complexity is approximately:

```text
O(N log N + M log M)
```

This is significantly better than the quadratic Nested Loop Join for sufficiently large datasets.

---

# Performance Evolution

The project intentionally implements multiple approaches to the same class of problem.

```text
┌────────────────────────┬───────────────────────────────┐
│ Strategy               │ Complexity                    │
├────────────────────────┼───────────────────────────────┤
│ Nested Loop Join       │ O(N × M)                      │
│                        │                               │
│ Single Loop + B-Tree   │ O(N × log M)                 │
│                        │                               │
│ Sort-Merge Join        │ O(N log N + M log M)         │
└────────────────────────┴───────────────────────────────┘
```

This progression demonstrates an important principle in database systems:

> **The choice of data structure and access strategy can have a much greater impact on performance than micro-optimizing the implementation itself.**

The project therefore provides a practical comparison between:

```text
Brute Force
    ↓
Indexed Search
    ↓
Sorting + Sequential Merge
```

---

# Complexity Summary

| Operation | Technique | Expected Complexity |
|---|---|---:|
| RRN → physical position | Offset calculation | **O(1)** |
| Record removal | Logical deletion | **O(1)** |
| Hash lookup | Hash Table | **O(1)** average |
| Hash insertion | Hash Table | **O(1)** average |
| Unique element construction | Hash Table | **O(N)** average |
| Sequential search | File scan | **O(N)** |
| B-Tree search | B-Tree | **O(log N)** |
| B-Tree insertion | B-Tree | **O(log N)** |
| B-Tree deletion | B-Tree | **O(log N)** |
| File sorting | `qsort` | **O(N log N)** |
| Nested Loop Join | Brute force | **O(NM)** |
| Single Loop Join | B-Tree | **O(N log M)** |
| Sort-Merge Join | Sorting + merge | **O(N log N + M log M)** |

> Hash table operations assume a reasonable hash function and controlled load factor. B-Tree operations assume a balanced tree.

---

# Design Decisions

## Fixed-size records

Fixed-size records allow direct addressing:

```text
offset = header_size + record_size × RRN
```

This provides constant-time physical address calculation.

---

## Logical deletion

Physical deletion would require moving subsequent records.

Logical deletion avoids this cost and enables free-list reuse.

---

## Hash Table for uniqueness

A hash table is more appropriate than repeated linear searches for maintaining unique stations and station pairs.

This changes the expected construction cost from quadratic behavior toward linear behavior.

---

## B-Tree for indexing

Hash tables are excellent for exact in-memory lookup, but a B-Tree is more appropriate for a persistent ordered index.

The B-Tree provides:

- Ordered keys
- Balanced search
- Persistent pages
- Page reuse
- Logarithmic search
- Integration with byte offsets
- Disk-oriented organization

---

## Multiple Join Algorithms

Instead of implementing only one join algorithm, the project intentionally provides multiple strategies.

This allows the same logical operation to be solved using:

```text
Brute Force
    ↓
Nested Loop
    ↓
O(NM)
```

then:

```text
Index
    ↓
B-Tree
    ↓
O(N log M)
```

and finally:

```text
Sort
    ↓
Merge
    ↓
O(N log N + M log M)
```

This makes the project useful not only as an implementation exercise, but also as a practical study of algorithmic optimization.

---

# Data Flow

## Indexed Query

A typical indexed query follows:

```text
                 Query
                   │
                   ▼
             Search Key
                   │
                   ▼
                B-Tree
                   │
                   ▼
              Byte Offset
                   │
                   ▼
             Binary File
                   │
                   ▼
                Record
```

---

## Sort-Merge Join

The Sort-Merge Join follows:

```text
        File A                    File B
           │                         │
           ▼                         ▼
         Sort                      Sort
           │                         │
           └──────────┬──────────────┘
                      ▼
                 Merge Join
                      │
                      ▼
                   Result
```

---

# Storage Model

The main binary file contains a header followed by fixed-size records:

```text
┌───────────────────────────────┐
│             HEADER            │
├───────────────────────────────┤
│            RECORD 0           │
├───────────────────────────────┤
│            RECORD 1           │
├───────────────────────────────┤
│            RECORD 2           │
├───────────────────────────────┤
│              ...              │
├───────────────────────────────┤
│            RECORD N           │
└───────────────────────────────┘
```

The header maintains metadata such as:

- File consistency status
- Free-list top
- Next available RRN
- Number of stations
- Number of unique station pairs

---

# Performance Considerations

The project uses different structures according to the access pattern.

```text
Problem
   │
   ├── Direct record access
   │       ↓
   │     RRN / Offset
   │       ↓
   │      O(1)
   │
   ├── Exact uniqueness lookup
   │       ↓
   │   Hash Table
   │       ↓
   │   O(1) average
   │
   ├── Indexed search
   │       ↓
   │     B-Tree
   │       ↓
   │    O(log N)
   │
   └── Large join
           ↓
      Sort-Merge
           ↓
   O(N log N + M log M)
```

The important optimization is therefore not simply choosing the fastest structure in isolation, but matching the structure to the workload.

---

# Build

The project uses `gcc` and `make`.

## Compile

```bash
make
```

## Debug Build

```bash
make debug
```

## Run

```bash
make run
```

## Clean

```bash
make clean
```

## Manual Compilation

```bash
gcc -Wall -Wextra \
    src/main.c \
    src/core/*.c \
    src/sql/*.c \
    src/btree/*.c \
    -Iinclude \
    -lm \
    -o programTrab
```

---

# Development

The project is written in C and uses manual memory management.

Important low-level concepts involved include:

- `malloc`
- `calloc`
- `realloc`
- `free`
- `FILE`
- `fopen`
- `fread`
- `fwrite`
- `fseek`
- `ftell`
- Binary serialization
- Pointer manipulation
- Dynamic data structures
- File offsets
- Persistent data structures

The project therefore combines algorithmic reasoning with systems-level programming.

---

# Testing

The repository contains test inputs and expected outputs for validating the implemented operations.

The general testing workflow is:

```text
Input
  │
  ▼
programTrab
  │
  ▼
Output
  │
  ▼
Expected Output
```

This allows deterministic validation of the SQL-like operations, indexing mechanisms and join algorithms.

---

# Technical Highlights

## Data Structures

- Hash Table
- Separate Chaining
- B-Tree
- Linked Free Lists
- Fixed-size Records

## Algorithms

- djb2 Hashing
- Binary File Addressing
- B-Tree Search
- B-Tree Insertion
- B-Tree Deletion
- B-Tree Split
- B-Tree Key Promotion
- B-Tree Redistribution
- B-Tree Merge
- `qsort`
- Nested Loop Join
- Indexed Single Loop Join
- Sort-Merge Join

## Systems Concepts

- Binary persistence
- File offsets
- RRN addressing
- Logical deletion
- Free-space management
- Disk-oriented indexing
- Manual memory management
- Persistent data structures
- Query processing

---

# What This Project Demonstrates

The main objective was not simply to implement a collection of CRUD operations.

The project demonstrates how the same data can be processed through fundamentally different strategies:

```text
                   DATA
                    │
        ┌───────────┼────────────┐
        │           │            │
        ▼           ▼            ▼
    Hash Table    B-Tree       Sorting
        │           │            │
        ▼           ▼            ▼
    O(1) avg.     O(log N)     O(N log N)
        │           │            │
        └───────────┼────────────┘
                    ▼
              Query Processing
                    │
        ┌───────────┼────────────┐
        ▼           ▼            ▼
   Nested Loop   Single Loop   Sort-Merge
      O(NM)       O(N log M)   O(NlogN + MlogM)
```

The resulting system provides a practical study of how **data structures, persistent storage and algorithm selection directly affect the performance of data-processing systems**.

---

# Performance Analysis

The project provides a natural experimental framework for comparing different approaches.

For a dataset containing `N` records, the theoretical behavior is:

```text
Sequential Search
        │
        ▼
       O(N)

B-Tree Search
        │
        ▼
     O(log N)

Hash Lookup
        │
        ▼
     O(1) average
```

For joins:

```text
Nested Loop
     │
     ▼
   O(NM)

Single Loop + B-Tree
     │
     ▼
 O(N log M)

Sort-Merge
     │
     ▼
O(N log N + M log M)
```

This makes it possible to experimentally evaluate the difference between:

- No index
- Persistent index
- Pre-sorted data
- Hash-based lookup
- Sequential processing

---

# Benchmarking

A natural extension of the project is to benchmark the implemented strategies with different dataset sizes:

```text
Dataset
├── 1,000 records
├── 10,000 records
├── 100,000 records
└── 1,000,000 records
```

The following strategies can be compared:

```text
Nested Loop Join
       vs
Single Loop + B-Tree
       vs
Sort-Merge Join
```

Useful metrics include:

- Execution time
- Number of disk reads
- Number of disk writes
- Memory consumption
- Number of B-Tree operations
- Number of hash collisions
- Number of records processed
- Index construction time

This would provide an empirical complement to the theoretical complexity analysis.

---

# Future Improvements

- [ ] External merge sort for datasets larger than RAM
- [ ] B-Tree range queries
- [ ] B-Tree duplicate-key support
- [ ] Improved buffer management
- [ ] Page caching
- [ ] I/O operation counters
- [ ] Automated benchmarking
- [ ] Runtime comparison between join strategies
- [ ] Hash table resizing based on load factor
- [ ] Improved error propagation
- [ ] Automated unit tests
- [ ] AddressSanitizer integration
- [ ] Valgrind memory analysis
- [ ] More robust crash recovery
- [ ] Transaction-like write semantics

---

# Academic Context

This project was developed as an implementation exercise focused on **file organization, indexing, data structures and query processing**.

It connects theoretical concepts from algorithms and data structures with practical systems programming:

```text
Theory
  │
  ├── Complexity
  ├── Trees
  ├── Hashing
  └── Sorting
        │
        ▼
Implementation
        │
  ├── Binary Files
  ├── B-Tree
  ├── Hash Tables
  ├── Free Lists
  └── Join Algorithms
        │
        ▼
Performance
```

The project demonstrates how abstract algorithmic concepts translate into concrete storage and query-processing mechanisms.

---

# Authors

**Luiz Felipe Manzoli Franceschini**

**Enzo Trulenque Evangelista**

Developed in **C**.
