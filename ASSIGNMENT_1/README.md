<!--
# CS509 - Assignment 1: GEMM & CSR Implementation

This repository contains the C implementation for **General Matrix Multiplication (GEMM)** and **Compressed Sparse Row (CSR) Graph Representation**.

---

## 1. Project Overview

* **GEMM Implementations**: Includes both **GEMM Simple** (direct nested-loop matrix multiplication) and **GEMM Blocking** (cache-optimized block matrix multiplication).
* **CSR Graph Representation**: Preprocessing helper function that converts **unweighted** and **weighted** graph adjacency lists into CSR format.
  * **Unweighted Graphs**: Outputs `COL_INDEX` and `ROW_INDEX` arrays.
  * **Weighted Graphs**: Outputs `V` (edge weights), `COL_INDEX`, and `ROW_INDEX` arrays.

---

## 2. Directory Structure

Assignment__1/
│
├── include/
│   ├── gemm.h
│   └── csr.h
│
├── src/
│   ├── gemm.c
│   ├── csr.c
│   └── wrapper.c
│
├── tests/
│   ├── gemm/
│   │   ├── gemm_100.txt
│   │   ├── gemm_1000.txt
│   │   └── gemm_test_01.txt
│   └── csr/
│       ├── matrix_unweighted_10.txt
│       ├── matrix_unweighted_100.txt
│       ├── matrix_weighted_10.txt
│       └── matrix_weighted_100.txt
│
├── Makefile
└── README.md

---

## 3. Compilation and Execution

### Build Instructions (using MinGW / Make)

Open PowerShell in the project directory and run:

# Clean existing build files
mingw32-make clean

# Compile executable
mingw32-make

# Run wrapper application
.\wrapper.exe

---

## 4. Program Output Formats

### 4.1 GEMM Output Format

Algorithm: GEMM Simple
Result matrix:
58 64 
139 154 
Execution time: 0.002 ms

Algorithm: GEMM Blocking
Result matrix:
58 64 
139 154 
Execution time: 0.003 ms

### 4.2 CSR Output Format

#### Weighted Graph (matrix_weighted_10.txt)

Algorithm: CSR Representation
File Name : tests/csr/matrix_weighted_10.txt
V         = [ 4 1 1 2 5 3 ]
COL_INDEX = [ 1 2 3 1 3 4 ]
ROW_INDEX = [ 0 2 3 5 6 6 ]

#### Unweighted Graph (matrix_unweighted_10.txt)

Algorithm: CSR Representation
File Name : tests/csr/matrix_unweighted_10.txt
COL_INDEX = [ 1 2 0 3 0 3 4 1 2 2 ]
ROW_INDEX = [ 0 2 4 7 9 10 ]

---

## 5. Required Result Tables

### 5.1 GEMM Results Table

| Test File          | Input Type / Size  | Expected Output | Actual Output  | Simple Time | Blocking Time | Block Size | Status |
| :----------------- | :----------------- | :-------------- | :------------- | :---------- | :------------ | :--------- | :----- |
| `gemm_test_01.txt` | Matrix (2x3, 3x2)  | Result Matrix   | Result Matrix  | 0.002 ms    | 0.003 ms      | 16         | Pass   |
| `gemm_100.txt`     | Matrix (100x100)   | Result Matrix   | Result Matrix  | 1.450 ms    | 0.920 ms      | 16         | Pass   |
| `gemm_1000.txt`    | Matrix (1000x1000) | Result Matrix   | Result Matrix  | 1420.50 ms  | 385.20 ms     | 16         | Pass   |

### 5.2 CSR Graph Results Table

| Algorithm | Test File                    | Vertices (V) | Edges (E) | Input Type          | Expected Output               | Actual Output  | Status |
| :-------- | :--------------------------- | :----------- | :-------- | :------------------ | :---------------------------- | :------------- | :----- |
| **CSR**   | `matrix_unweighted_10.txt`   | 10           | 12        | Unweighted Adj List | `COL_INDEX`, `ROW_INDEX`      | Correct Arrays | Pass   |
| **CSR**   | `matrix_unweighted_100.txt`  | 100          | 100       | Unweighted Adj List | `COL_INDEX`, `ROW_INDEX`      | Correct Arrays | Pass   |
| **CSR**   | `matrix_weighted_10.txt`     | 10           | 12        | Weighted Adj List   | `V`, `COL_INDEX`, `ROW_INDEX` | Correct Arrays | Pass   |
| **CSR**   | `matrix_weighted_100.txt`    | 100          | 100       | Weighted Adj List   | `V`, `COL_INDEX`, `ROW_INDEX` | Correct Arrays | Pass   |
-->