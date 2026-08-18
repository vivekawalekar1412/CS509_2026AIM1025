# CS509 Assignments - Master Project Repository

This repository contains implementation deliverables and test suites for **CS509: Algorithm Analysis and Design** assignments.

---

## Directory Structure

```text
CS509_ASSIGNMENTS/
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
├── ASSIGNMENT_2/
│   ├── include/
│   │   ├── bellman_ford.h      # Bellman-Ford algorithm interface
│   │   └── floyd_warshall.h    # Floyd-Warshall algorithm interface
│   ├── src/
│   │   ├── bellman_ford.c      # Bellman-Ford implementation
│   │   ├── floyd_warshall.c    # Floyd-Warshall implementation
│   │   └── driver_a2.c         # Assignment 2 driver program
│   ├── tests/
│   │   ├── bellman_ford/       # Weighted adjacency list input files
│   │   └── floyd_warshall/     # Dense V x V matrix input files
│   └── driver.exe              # Assignment 2 executable
│
└── ASSIGNMENT_3/
    ├── include/
    │   └── mst.h               # Minimum Spanning Tree interface
    ├── src/
    │   ├── kruskal.c           # Kruskal's MST implementation
    │   ├── prim.c              # Prim's MST implementation
    │   └── driver_a3.c         # Assignment 3 driver program
    ├── tests/
    │   └── mst/                # Weighted undirected CSR benchmarks
    ├── Makefile                # Assignment 3 compilation script
    └── driver.exe              # Assignment 3 executable
```

---

## Compilation Commands

### Compile Individual Assignment Drivers

* **Assignment 1 Driver**:
```powershell
gcc -O3 -Wall -I ASSIGNMENT_1/include ASSIGNMENT_1/src/csr.c ASSIGNMENT_1/src/gemm.c ASSIGNMENT_1/src/driver.c -o ASSIGNMENT_1/driver.exe
```

* **Assignment 2 Driver**:
```powershell
gcc -O3 -Wall -I ASSIGNMENT_2/include -I ASSIGNMENT_1/include ASSIGNMENT_1/src/csr.c ASSIGNMENT_2/src/bellman_ford.c ASSIGNMENT_2/src/floyd_warshall.c ASSIGNMENT_2/src/driver_a2.c -o ASSIGNMENT_2/driver.exe
```

* **Assignment 3 Driver**:
```powershell
gcc -O3 -Wall -I ASSIGNMENT_3/include -I ASSIGNMENT_1/include ASSIGNMENT_1/src/csr.c ASSIGNMENT_3/src/kruskal.c ASSIGNMENT_3/src/prim.c ASSIGNMENT_3/src/driver_a3.c -o ASSIGNMENT_3/driver.exe
```

---

## Master Wrapper Execution

```powershell
# 1. Terminate running wrapper instance
Stop-Process -Name "wrapper" -Force -ErrorAction SilentlyContinue

# 2. Re-compile the wrapper
gcc wrapper.c -o wrapper.exe

# 3. Launch Master Wrapper
.\wrapper.exe
```

---

## Standalone Direct Execution Examples

### Assignment 3: Minimum Spanning Tree (MST)[cite: 1]

* **Run Kruskal's Algorithm**:
```powershell
.\ASSIGNMENT_3\driver.exe kruskal ASSIGNMENT_3/tests/mst/mst_10.txt
```

* **Run Prim's Algorithm**:
```powershell
.\ASSIGNMENT_3\driver.exe prim ASSIGNMENT_3/tests/mst/mst_10.txt
```

* **Run & Compare Both**:
```powershell
.\ASSIGNMENT_3\driver.exe both ASSIGNMENT_3/tests/mst/mst_10.txt
```