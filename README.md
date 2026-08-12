# CS509 Assignments - Master Project Repository

This repository contains implementation deliverables and test suites for **CS509: Algorithm Analysis and Design** assignments.

---

## Directory Structure

```text
CS509_ASSIGNMENTS/
├── Makefile                    # Root Makefile for building all targets
├── wrapper.c                   # Master interactive terminal wrapper
├── wrapper.exe                 # Compiled master interactive executable
├── README.md                   # Project documentation
│
├── ASSIGNMENT_1/
│   ├── include/
│   │   ├── csr.h               # CSR graph representation interface
│   │   └── gemm.h              # GEMM matrix multiplication interface
│   ├── src/
│   │   ├── csr.c               # CSR conversion implementation
│   │   ├── gemm.c              # GEMM algorithms (simple & blocked)
│   │   └── driver.c            # Assignment 1 driver program
│   ├── tests/
│   │   ├── csr/                # Test input matrices for CSR
│   │   └── gemm/               # Test matrices for GEMM
│   └── driver.exe              # Assignment 1 executable
│
└── ASSIGNMENT_2/
    ├── include/
    │   ├── bellman_ford.h      # Bellman-Ford algorithm interface
    │   └── floyd_warshall.h    # Floyd-Warshall algorithm interface
    ├── src/
    │   ├── bellman_ford.c      # Bellman-Ford implementation
    │   ├── floyd_warshall.c    # Floyd-Warshall implementation
    │   └── driver_a2.c         # Assignment 2 driver program
    ├── tests/
    │   ├── bellman_ford/       # Weighted adjacency list input files
    │   └── floyd_warshall/     # Dense V x V matrix input files
    └── driver.exe              # Assignment 2 executable





  ##  COMMANDS TO RUN ASSIGNMENTS

  # 1. Terminate running wrapper instance
Stop-Process -Name "wrapper" -Force -ErrorAction SilentlyContinue

# 2. Re-compile the wrapper
gcc wrapper.c -o wrapper.exe

# 3. Launch Master Wrapper
.\wrapper.exe